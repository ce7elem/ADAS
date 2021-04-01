#define ACC1 1200
#define ACC2 1300
#define ACC3 1400
#define ACC4 1500
#define DECC 1100
#define BRAKE 1600
#define REVERSE 1300
#define NEUTRAL 500
#include <Servo.h>

bool first = true;


Servo DCmotor;
int incomingByte; // for incoming serial data
int state;
String anglestr;
int angle;

char buf[20];

void setup() {
  DCmotor.attach(5);
  DCmotor.writeMicroseconds(BRAKE);
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  //Serial.println("Starting");
}

//--------------------------------------

bool catchFlags (char * token) {

  if ( strcmp(token, "ERREUR") == 0 || strcmp(token, "BREAK") == 0) {
    // ARRET
      DCmotor.writeMicroseconds(BRAKE);
      //Serial.println("Brk mode");
    return true;
  }

  if ( strcmp(token, "GEAR_1") == 0) {
      DCmotor.writeMicroseconds(ACC4);
      //Serial.println("ACC4");
    return true;
  }

  if ( strcmp(token, "GEAR_2") == 0) {
      DCmotor.writeMicroseconds(ACC3);
      //Serial.println("ACC3");
    return true;
  }

  if ( strcmp(token, "GEAR_3") == 0) {
      DCmotor.writeMicroseconds(ACC2);
      //Serial.println("ACC2");
    return true;
  }

  if ( strcmp(token, "GEAR_4") == 0) {
      DCmotor.writeMicroseconds(ACC1);
      //Serial.println("ACC1");
    return true;
  }

  if (first) {
    DCmotor.writeMicroseconds(ACC4);
    first = false;
  }

  return false;
}


void handleTurn (int angle){
  
}



#define SOP '<'
#define EOP '>'

char inData[80];
byte index;
bool started = false;
bool ended = false;

void loop() {

  while(Serial.available() > 0)
  {
    char inChar = Serial.read();
    if(inChar == SOP)
    {
       index = 0;
       inData[index] = '\0';

       started = true;
       ended = false;
    }
    else if(inChar == EOP)
    {
       ended = true;
       break;
    }
    else
    {
      if(index < 79)
      {
        inData[index] = inChar;
        index++;
        inData[index] = 0;
      }
    }
  }

  if(started && ended)
  {
    // cach control flags (ERROR, ...)
    if ( !catchFlags(inData) ) {

      // handle new direction
      angle = atoi(inData);
      if (angle != 0) {
        Serial.println(angle);
        angle = 0;
  
        handleTurn(angle);
      }

      // reset variables for next token
      started = false;
      ended = false;
      index = 0;
      inData[index] = 0;
    }
  }
  /*
    if(incomingByte == '1')
    {
      DCmotor.writeMicroseconds(ACC1);
      Serial.println("Ac mode");
      state = incomingByte;
      
    }

    else if(incomingByte == '0')
    {
      DCmotor.writeMicroseconds(BRAKE);
      Serial.println("Brk mode"); 
      state= incomingByte;
    }
    
    if(incomingByte == '2')
    {
      DCmotor.writeMicroseconds(ACC2);
      Serial.println("Ac mode");
      state = incomingByte;
      
    }

    if(incomingByte == '3')
    {
      DCmotor.writeMicroseconds(ACC3);
      Serial.println("Ac mode");
      state = incomingByte;
      
    }

    if(incomingByte == '4')
    {
      
      
    }

    else
    {
      incomingByte = state;
    }
    */
    
}
