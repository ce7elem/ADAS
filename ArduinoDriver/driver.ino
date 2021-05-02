#include <Servo.h>
#define VITESSE_MAX 1660
#define ACCELERATION 5
#define STRAIGHT straight
#define ght SPEED_UP speedup
#define TURN_RIGHT_UP turn_right_up
#define SPEED_CST speed_cst
#define TURN_RIGHT_DOWN turn_right_down
#define TURN_LEFT_UP turn_left_up
#define TURN_LEFT_DOWN turn_left_down
#define SPEED_DOWN speed_down

String msg;

Servo myservo;
Servo DCmotor;
// create servo object to control a servo
// twelve servo objects can be created on most boards

int speed_value = 0;
int turn_value = 0;
int time_value = 0;


void setup() {
  myservo.attach(2);  // attaches the servo on pin 2 to the servo object
  DCmotor.attach(7);
  Serial.begin(9600);
  delay(1000);
  DCmotor.write(1500);
  myservo.write(0);
  
}

void loop() {

//  readSerialPort();

 /* if (msg != "") {
    
    Serial.print("pong");

    handleInput();
  }*/

  //straight();
  //speedUp();
  delay(1000); // init delay
  speedUp();
  //delay(1000);
  //turnLeftUp();
  //delay(1000);
  //turnLeftDown();
  delay(1000);
  speedDown();
  //delay(1000);
  //turnRightUp();
  //delay(1000);
  //turnRightDown();
  //delay(3000);
  
  //speedDown();
 
  
}



/*void handleInput(char * message){
  switch (message){
    case STRAIGHT:
      straight();
      break;
    case SPEED_UP:
      speedUp();
      break;
    case TURN_RIGHT_UP:
      turnRightUp();
      break;
    case SPEED_CST:
      speedCst();
      break;
    case TURN_RIGHT_DOWN:
      turnRightDown();
      break;
    case TURN_LEFT_UP:
      turnLeftUp();
      break;
    case TURN_LEFT_DOWN:
      turnLetDown();
      break;
    case SPEED_DOWN:
      speedDown();
      break;
  }
}*/

void readSerialPort() {
  msg = "";
  if (Serial.available()) {
    delay(5);
    while (Serial.available() > 0) {
      msg += (char)Serial.read();
    }
    Serial.flush();
  }
}

////////////////////////////////////////////////////

void speedUp() {
  /*Speed Up*/
  speed_value = 1600;
  delay(10);
  for(speed_value;speed_value<1650;speed_value+=1)// 3e speed value = acceleration
  //                          (vitesse max)
  {
    DCmotor.writeMicroseconds(speed_value);
    delay(250); // 3e speed value = acceleration
    Serial.println(speed_value);
  }
}

void speedDown() {
  /*Speed Down*/
  speed_value = 1650; 
  for(speed_value;speed_value>1550;speed_value-=1)// 3e speed value = acceleration
  //                (vitesse max)
  {
    DCmotor.writeMicroseconds(speed_value);
    delay(250); // 3e speed value = acceleration
        Serial.println(speed_value);
  }
}

void speedCst() {
  /*Speed Down*/
  speed_value = 1650;
  time_value = 0; 
  while(time_value>1000)
  {
    DCmotor.writeMicroseconds(speed_value);
    delay(500);
    time_value++;
  }
}

void turnRightUp() {
  /*Speed Up*/
  turn_value = 90; 
  delay(15);
  for(turn_value;turn_value>60;turn_value--)
  {
    myservo.write(turn_value);
    delay(20);
    Serial.println(turn_value);
  }
}

void turnRightDown() {
  /*Speed Up*/
  turn_value = 60; 
  delay(15);
  for(turn_value;turn_value<=90;turn_value+=1)
  {
    myservo.write(turn_value);
    delay(20);
    Serial.println(turn_value);
  }
}

void turnLeftUp() {
  /*Speed Up*/
  turn_value = 90; 
  delay(15);
  for(turn_value;turn_value<=120;turn_value+=1)
  {
    myservo.write(turn_value);
    delay(20);
    Serial.println(turn_value);
  }
  delay(20);
  myservo.write(90);
}

void turnLeftDown() {
  /*Speed Up*/
  turn_value = 120; 
  delay(15);
  for(turn_value;turn_value>90;turn_value--)
  {
    myservo.write(turn_value);
    delay(20);
    Serial.println(turn_value);
  }
  
}

void straight() {
  /*Speed Up*/
  myservo.write(90);
}

void stopCst() {
  /*Speed Up*/
  speed_value = 0;
  delay(200);
  DCmotor.writeMicroseconds(speed_value);
  delay(200);
}

/*void servodirection(int correction, int objectif)
{
  // angles must be betwteen 60 & 120
  
  correction = servo.read(2) - objectif;
  if(correction < 0)
  {
    turn_value = servo.read(2) - ;
    for(turn_value;turn_value<=120;turn_value+=1)
    {
       myservo.write(turn_value);
       delay(20);
       Serial.println(turn_value);
    }
      delay(20);
      myservo.write(90);
  }
  
}*/
