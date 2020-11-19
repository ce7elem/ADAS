#include <Servo.h>
#define VITESSE_MAX 1660
#define ACCELERATION 10

#define STRAIGHT "0"
#define SPEED_UP "2"
#define TURN_RIGHT_UP "E"
#define SPEED_CST "Z"
#define TURN_RIGHT_DOWN "C"
#define TURN_LEFT_UP "A"
#define TURN_LEFT_DOWN "W"
#define SPEED_DOWN "S"


String msg;

// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED


Servo myservo;
Servo DCmotor;
// create servo object to control a servo
// twelve servo objects can be created on most boards

int speed_value = 0;
int turn_value = 0;
int time_value = 0;

void handleInput(String message);

void setup() {
  pinMode(ledPin, OUTPUT);
  
  myservo.attach(2);  // attaches the servo on pin 2 to the servo object
  DCmotor.attach(7);
  Serial.begin(115002);
  delay(1000);
  DCmotor.write(1500);
  myservo.write(0);
  
}

String readSerialPort() {
  if (Serial.available() > 0){
    String data = Serial.readStringUntil('\n');
    Serial.print("Recived");

    ledState = HIGH;

    return data;
  }
}


void loop() {

  if (Serial.available() > 0){
    String data = Serial.readStringUntil('\n');
    Serial.print("Recived");

    ledState = HIGH;

    handleInput(data);   
  }

  //straight();
  //speedUp();
  /*
  delay(3000); // init delay
  speedUp();
  turnRightUp();
  turnRightDown();
  turnLeftUp();
  turnLeftDown();
  turnRightUp();
  turnRightDown();
  turnLeftUp();
  turnLeftDown();
  speedDown();
  */
}





////////////////////////////////////////////////////

void speedUp() {
  /*Speed Up*/
  speed_value = 1600;
  delay(10);
  for(speed_value;speed_value<1650;speed_value+=ACCELERATION)// 3e speed value = acceleration
  //                          (vitesse max)
  {
    DCmotor.writeMicroseconds(speed_value);
    delay(25); // 3e speed value = acceleration
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

void handleInput(String message){
  
  if (message == STRAIGHT)
      straight();
      
   if (message == SPEED_UP)
      speedUp();

   if( message == TURN_RIGHT_UP)
      turnRightUp();

    if( message == SPEED_CST)
      speedCst();

    if( message == TURN_RIGHT_DOWN)
      turnRightDown();

    if( message == TURN_LEFT_UP)
      turnLeftUp();

    if (message == TURN_LEFT_DOWN)
      turnLeftDown();

    if (message == SPEED_DOWN)
      speedDown();
}
