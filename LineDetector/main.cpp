
#include <stdio.h>
#include <string.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <math.h>
#include "utils.h"

#include <fstream>

//#define USE_VIDEO 1
//#define _DEBUG 1
#define MONIT 1
//#define HOUGH_LINE 1

#undef MIN
#undef MAX
#define MAX(a,b) ((a)<(b)?(b):(a))
#define MIN(a,b) ((a)>(b)?(b):(a))

void crop(IplImage* src,  IplImage* dest, CvRect rect) {
    cvSetImageROI(src, rect); 
    cvCopy(src, dest); 
    cvResetImageROI(src); 
}

struct Lane {
	Lane(){}
	Lane(CvPoint a, CvPoint b, float angle, float kl, float bl): p0(a),p1(b),angle(angle),
		votes(0),visited(false),found(false),k(kl),b(bl) { }

	CvPoint p0, p1;
	int votes;
	bool visited, found;
	float angle, k, b;
};

struct Status {
	Status():reset(true),lost(0){}
	ExpMovingAverage k, b;
	bool reset;
	int lost;
};

#define GREEN CV_RGB(0,255,0)
#define RED CV_RGB(255,0,0)
#define BLUE CV_RGB(255,0,255)
#define PURPLE CV_RGB(255,0,255)

Status laneR, laneL;

enum{
    SCAN_STEP = 5,			  // in pixels
	LINE_REJECT_DEGREES = 10, // in degrees
    BW_TRESHOLD = 250,		  // edge response strength to recognize for 'WHITE'
    BORDERX = 10,			  // px, skip this much from left & right borders
	MAX_RESPONSE_DIST = 5,	  // px
	
	CANNY_MIN_TRESHOLD = 1,	  // edge detector minimum hysteresis threshold
	CANNY_MAX_TRESHOLD = 100, // edge detector maximum hysteresis threshold

	HOUGH_TRESHOLD = 50,		// line approval vote threshold
	HOUGH_MIN_LINE_LENGTH = 50,	// remove lines shorter than this treshold
	HOUGH_MAX_LINE_GAP = 100,   // join lines to one with smaller than this gaps

	CAR_DETECT_LINES = 4,    // minimum lines for a region to pass validation as a 'CAR'
	CAR_H_LINE_LENGTH = 10,  // minimum horizontal line length from car body in px

	
};

#define K_VARY_FACTOR 0.2f
#define B_VARY_FACTOR 20
#define MAX_LOST_FRAMES 30

void FindResponses(IplImage *img, int startX, int endX, int y, std::vector<int>& list)
{
    // scans for single response: /^\_

	const int row = y * img->width * img->nChannels;
	unsigned char* ptr = (unsigned char*)img->imageData;

    int step = (endX < startX) ? -1: 1;
    int range = (endX > startX) ? endX-startX+1 : startX-endX+1;

    for(int x = startX; range>0; x += step, range--)
    {
        if(ptr[row + x] <= BW_TRESHOLD) continue; // skip black: loop until white pixels show up

        // first response found
        int idx = x + step;

        // skip same response(white) pixels
        while(range > 0 && ptr[row+idx] > BW_TRESHOLD){
            idx += step;
            range--;
        }

		// reached black again
        if(ptr[row+idx] <= BW_TRESHOLD) {
            list.push_back(x);
        }

        x = idx; // begin from new pos
    }
}

unsigned char pixel(IplImage* img, int x, int y) {
	return (unsigned char)img->imageData[(y*img->width+x)*img->nChannels];
}

int findSymmetryAxisX(IplImage* half_frame, CvPoint bmin, CvPoint bmax) {
  
  float value = 0;
  int axisX = -1; // not found
  
  int xmin = bmin.x;
  int ymin = bmin.y;
  int xmax = bmax.x;
  int ymax = bmax.y;
  int half_width = half_frame->width/2;
  int maxi = 1;

  for(int x=xmin, j=0; x<xmax; x++, j++) {
	float HS = 0;
    for(int y=ymin; y<ymax; y++) {
		int row = y*half_frame->width*half_frame->nChannels;
        for(int step=1; step<half_width; step++) {
          int neg = x-step;
          int pos = x+step;
		  unsigned char Gneg = (neg < xmin) ? 0 : (unsigned char)half_frame->imageData[row+neg*half_frame->nChannels];
          unsigned char Gpos = (pos >= xmax) ? 0 : (unsigned char)half_frame->imageData[row+pos*half_frame->nChannels];
          HS += abs(Gneg-Gpos);
        }
    }

	if (axisX == -1 || value > HS) { // find minimum
		axisX = x;
		value = HS;
	}
  }

  return axisX;
}

bool hasVertResponse(IplImage* edges, int x, int y, int ymin, int ymax) {
	bool has = (pixel(edges, x, y) > BW_TRESHOLD);
	if (y-1 >= ymin) has &= (pixel(edges, x, y-1) < BW_TRESHOLD);
	if (y+1 < ymax) has &= (pixel(edges, x, y+1) < BW_TRESHOLD);
	return has;
}

int horizLine(IplImage* edges, int x, int y, CvPoint bmin, CvPoint bmax, int maxHorzGap) {

	// scan to right
	int right = 0;
	int gap = maxHorzGap;
	for (int xx=x; xx<bmax.x; xx++) {
		if (hasVertResponse(edges, xx, y, bmin.y, bmax.y)) {
			right++;
			gap = maxHorzGap; // reset
		} else {
			gap--;
			if (gap <= 0) {
				break;
			}
		}
	}

	int left = 0;
	gap = maxHorzGap;
	for (int xx=x-1; xx>=bmin.x; xx--) {
		if (hasVertResponse(edges, xx, y, bmin.y, bmax.y)) {
			left++;
			gap = maxHorzGap; // reset
		} else {
			gap--;
			if (gap <= 0) {
				break;
			}
		}
	}

	return left+right;
}

void processSide(std::vector<Lane> lanes, IplImage *edges, bool right) {

	Status* side = right ? &laneR : &laneL;

	// response search
	int w = edges->width;

	
	int h = edges->height;
	const int BEGINY = 0;
	const int ENDY = h-1;
	const int ENDX = right ? (w-BORDERX) : BORDERX;
	int midx = w/2;
	int midy = edges->height/2;
	unsigned char* ptr = (unsigned char*)edges->imageData;

	// show responses
	int* votes = new int[lanes.size()];
	for(int i=0; i<lanes.size(); i++) votes[i++] = 0;

	for(int y=ENDY; y>=BEGINY; y-=SCAN_STEP) {
		std::vector<int> rsp;
		FindResponses(edges, midx, ENDX, y, rsp);

		if (rsp.size() > 0) {
			int response_x = rsp[0]; // use first reponse (closest to screen center)

			float dmin = 9999999;
			float xmin = 9999999;
			int match = -1;
			for (int j=0; j<lanes.size(); j++) {
				// compute response point distance to current line
				float d = dist2line(
						cvPoint2D32f(lanes[j].p0.x, lanes[j].p0.y), 
						cvPoint2D32f(lanes[j].p1.x, lanes[j].p1.y), 
						cvPoint2D32f(response_x, y));

				// point on line at current y line
				int xline = (y - lanes[j].b) / lanes[j].k;
				int dist_mid = abs(midx - xline); // distance to midpoint

				// pick the best closest match to line & to screen center
				if (match == -1 || (d <= dmin && dist_mid < xmin)) {
					dmin = d;
					match = j;
					xmin = dist_mid;
					break;
				}
			}

			// vote for each line
			if (match != -1) {
				votes[match] += 1;
			}
		}
	}

	int bestMatch = -1;
	int mini = 9999999;
	for (int i=0; i<lanes.size(); i++) {
		int xline = (midy - lanes[i].b) / lanes[i].k;
		int dist = abs(midx - xline); // distance to midpoint

		if (bestMatch == -1 || (votes[i] > votes[bestMatch] && dist < mini)) {
			bestMatch = i;
			mini = dist;
		}
	}

	if (bestMatch != -1) {
		Lane* best = &lanes[bestMatch];
		float k_diff = fabs(best->k - side->k.get());
		float b_diff = fabs(best->b - side->b.get());

		bool update_ok = (k_diff <= K_VARY_FACTOR && b_diff <= B_VARY_FACTOR) || side->reset;

		printf("[LIGNE TROUVÉ] side: %s, k vary: %.4f, b vary: %.4f, lost: %s\n", (right?"RIGHT":"LEFT"), k_diff, b_diff, (update_ok?"no":"yes"));
		
		if (update_ok) {
			// update is in valid bounds
			side->k.add(best->k);
			side->b.add(best->b);
			side->reset = false;
			side->lost = 0;
		} else {
			// can't update, lanes flicker periodically, start counter for partial reset!
			side->lost++;
			if (side->lost >= MAX_LOST_FRAMES && !side->reset) {
				side->reset = true;
			}
		}

	} else {
		printf("[PAS DE LIGNE TROUVÉ] - lane tracking lost! counter increased\n");
		side->lost++;
		if (side->lost >= MAX_LOST_FRAMES && !side->reset) {
			// do full reset when lost for more than N frames
			side->reset = true;
			side->k.clear();
			side->b.clear();
		}
	}

	delete[] votes;
}

void processLanes(CvSeq* lines, IplImage* edges, IplImage* temp_frame) {

	// classify lines to left/right side
	std::vector<Lane> left, right;

	for(int i = 0; i < lines->total; i++ )
    {
        CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
		int dx = line[1].x - line[0].x;
		int dy = line[1].y - line[0].y;
		float angle = atan2f(dy, dx) * 180/CV_PI;

		if (fabs(angle) <= LINE_REJECT_DEGREES) { // reject near horizontal lines
			continue;
		}

		// assume that vanishing point is close to the image horizontal center
		// calculate line parameters: y = kx + b;
		dx = (dx == 0) ? 1 : dx; // prevent DIV/0!  
		float k = dy/(float)dx;
		float b = line[0].y - k*line[0].x;

		// assign lane's side based by its midpoint position 
		int midx = (line[0].x + line[1].x) / 2;
		if (midx < temp_frame->width/2) {
			left.push_back(Lane(line[0], line[1], angle, k, b));
		} else if (midx > temp_frame->width/2) {
			right.push_back(Lane(line[0], line[1], angle, k, b));
		}
    }

	#ifdef HOUGH_LINE
	// show Hough lines
	for	(int i=0; i<right.size(); i++) {
		cvLine(temp_frame, right[i].p0, right[i].p1, CV_RGB(0, 0, 255), 1);
	}

	for	(int i=0; i<left.size(); i++) {
		cvLine(temp_frame, left[i].p0, left[i].p1, CV_RGB(255, 0, 0), 1);
	}
	
	#endif

	processSide(left, edges, false);
	processSide(right, edges, true);

	// show computed lanes
	int x = temp_frame->width * 0.55f;
	int x2 = temp_frame->width;
	cvLine(temp_frame, cvPoint(x, laneR.k.get()*x + laneR.b.get()), cvPoint(x2, laneR.k.get() * x2 + laneR.b.get()), CV_RGB(255, 0, 255), 2);
	
	
	//CACUL DU MILEU DROITE
	int milieuY1 = temp_frame->height/2; //Milieu de la frame
	int milieuX1 = (milieuY1-laneR.b.get())/laneR.k.get();// (X = (Y-B)/A) Cacul x en fonction de y (centre de la fenetre)

	x = temp_frame->width * 0;
	x2 = temp_frame->width * 0.45f;
	cvLine(temp_frame, cvPoint(x, laneL.k.get()*x + laneL.b.get()), cvPoint(x2, laneL.k.get() * x2 + laneL.b.get()), CV_RGB(255, 0, 255), 2);
	
	
	//CACUL DU MILEU DROITE
	int milieuY2 = temp_frame->height/2; //Milieu de la frame
	int milieuX2 = (milieuY2-laneL.b.get())/laneL.k.get(); // (X = (Y-B)/A) Cacul x en fonction de y (centre de la fenetre)

	//CACUL DE LA DROITE 3 (en fonction du milieu des droite gauche et droite)
	int milieuX3 = (milieuX1+milieuX2)/2;
	int milieuY3 = (milieuY1+milieuY2)/2;

	/*
	//CALCUL DE L'ANGLE DU VIRAGE
	float dx = milieuX2-milieuX1;
	float dy = milieuY2-milieuY1;
	float a = -dy/dx;
	float b = milieuY1 - a*milieuX1;
	*/

	//CALCUL LA DISTANCE AVEC LE CENTRE DU MILIEU DE LA DROITE 3
	int offsetCenter = milieuX3 - temp_frame->width/2;
	int offsetFront = (temp_frame->width/4)*0.05; //offset ou la voiture va droit
	int maxOffset = temp_frame->width/4; //taille maximal du offset

	//normalisation du OFFSET en pourcentage
	int offsetCenterPercent = (100*offsetCenter)/(temp_frame->width/4);

	char string[10];
	std::ofstream outfile ("/tmp/flyeyes",std::ofstream::binary);
	//Si le offset est plus grand que le maximum, met le offset a 0 (TOUT DROITE)
	if (offsetCenter > maxOffset || offsetCenter < -maxOffset){
		sprintf(string,"%s\n","ERREUR");printf("%s","ERREUR");
		offsetCenter = 0;
	}else if (offsetCenter < offsetFront && offsetCenter > -offsetFront){
		sprintf(string,"%d\n",0); printf("%s","Front");
	}else if (offsetCenter > 0){
		sprintf(string,"%d\n",offsetCenterPercent);
		printf("%d%% %s",offsetCenterPercent,"RIGHT");
	}else{
		sprintf(string,"%d\n",offsetCenterPercent);
		printf("%d%% %s",offsetCenterPercent,"LEFT");
	}
	outfile.write (string, strlen(string));
	outfile.close();

	//trace le cercle
	cvCircle(temp_frame, cvPoint(milieuX3, milieuY3), 10,  CV_RGB(255, 0,0), 1);
	//trace la DROITE 3
	cvLine(temp_frame, cvPoint(milieuX1,milieuY1), cvPoint(milieuX2,milieuY2), CV_RGB(255, 125, 0), 1);
}



int main(void){
	#ifdef USE_VIDEO
		CvCapture *input_video = cvCreateFileCapture("road.mp4");
	#else
		CvCapture *input_video = cvCaptureFromCAM(0);
	#endif

	if (input_video == NULL) {
		fprintf(stderr, "Error: Can't open video\n");
		return -1;
	}

	CvFont font;
	cvInitFont( &font, CV_FONT_VECTOR0, 0.25f, 0.25f);

	CvSize video_size;
	video_size.height = (int) cvGetCaptureProperty(input_video, CV_CAP_PROP_FRAME_HEIGHT);
	video_size.width = (int) cvGetCaptureProperty(input_video, CV_CAP_PROP_FRAME_WIDTH);

	long current_frame = 0;
	int key_pressed = 0;

	IplImage *frame = NULL;

	CvSize frame_size = cvSize(video_size.width-1, video_size.height/2);
	IplImage *temp_frame = cvCreateImage(frame_size, IPL_DEPTH_8U, 3);
	IplImage *grey = cvCreateImage(frame_size, IPL_DEPTH_8U, 1);
	IplImage *edges = cvCreateImage(frame_size, IPL_DEPTH_8U, 1);
	IplImage *half_frame = cvCreateImage(cvSize(video_size.width/2, video_size.height/2), IPL_DEPTH_8U, 3);

	CvMemStorage* houghStorage = cvCreateMemStorage(0);

	while(key_pressed != 27){
		frame = cvQueryFrame(input_video);
		if (frame == NULL) {
			fprintf(stderr, "Error: null frame received\n");
			return -1;
		}

		cvPyrDown(frame, half_frame, CV_GAUSSIAN_5x5); // Reduce the image by 2	 
		cvCvtColor(temp_frame, grey, CV_BGR2GRAY); // convert to grayscale

		// we're interested only in road below horizont - so crop top image portion off
		crop(frame, temp_frame, cvRect(0,frame_size.height,frame_size.width,frame_size.height));
		cvCvtColor(temp_frame, grey, CV_BGR2GRAY); // convert to grayscale
		
		// Perform a Gaussian blur ( Convolving with 5 X 5 Gaussian) & detect edges
		cvSmooth(grey, grey, CV_GAUSSIAN, 5, 5);
		cvCanny(grey, edges, CANNY_MIN_TRESHOLD, CANNY_MAX_TRESHOLD);

		// do Hough transform to find lanes
		double rho = 1;
		double theta = CV_PI/180;
		CvSeq* lines = cvHoughLines2(edges, houghStorage, CV_HOUGH_PROBABILISTIC, 
			rho, theta, HOUGH_TRESHOLD, HOUGH_MIN_LINE_LENGTH, HOUGH_MAX_LINE_GAP);

		printf("%s\n","");
		processLanes(lines, edges, temp_frame);

		// compute middle line
		cvLine(temp_frame, cvPoint(frame_size.width/2,0), cvPoint(frame_size.width/2,frame_size.height), CV_RGB(255, 255, 0), 1);

		
		#ifdef MONIT
			//cvShowImage("Grey", grey);
			//cvShowImage("Edges", edges);
			cvShowImage("LINES FRAME", temp_frame);
			cvShowImage("FULL VIDEO", half_frame);
			cvMoveWindow("LINES FRAME", 0, frame_size.height+25);
			cvMoveWindow("FULL VIDEO", 0, 2*(frame_size.height+25)); 
		#endif

		key_pressed = cvWaitKey(5);

	}


	cvReleaseMemStorage(&houghStorage);

	cvReleaseImage(&grey);
	cvReleaseImage(&edges);
	cvReleaseImage(&temp_frame);
	cvReleaseImage(&half_frame);

	cvReleaseCapture(&input_video);
}
