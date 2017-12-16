#include <Sparki.h> // include the sparki library
#define COMMAND_INIT 0
#define LINE_FOLLOWING 1
#define STANDBY 2
#define serial Serial1
const char TERMINATOR = (char)23;  
const char* SPARKI_MYRO_VERSION = "1.1.3r1"; 
int action = COMMAND_INIT;
unsigned long startOfLoop; // Time since start of program, calculated at each loop beginning
const float pi = 3.1415926;

const float speedMotor = 0.3 / (10773.0 / 1000.0); // m / s
const float lengthAxle = 0.084; // meters

float posX = 0.0;
float posY = 0.0;
float theta = 0; // Initially facing left ("West" or 180 degrees)

int threshold = 500;

int lineLeft;
int lineCenter;
int lineRight;

void sendSerial(int i) {
  serial.print(i); 
  serial.print(TERMINATOR); 
}

void sendSerial(char* message) {
  serial.print(message); 
  serial.print(TERMINATOR); 
}

int getSerialBytes(char* buf, int size) {
  char inByte = -1;
  int maxChars = size; 
  int count = 0;
  
  // zero out the buffer
  for( int i = 0; i < maxChars; i++ ) {
    buf[i] = '\0';
  }

  while ((inByte != TERMINATOR) && (count < maxChars)) {
    if(serial.available()) {
      inByte = serial.read();
   
      if ((inByte != TERMINATOR) && (inByte >= 0)) {
        buf[count++] = (char)inByte;
      }
    }
  }
    while ((inByte != TERMINATOR) && (serial.available())) {
      inByte = serial.read();
  }

  return count;
}

char getSerialChar() {
  int size = 5;
  char buf[size];
  int result = getSerialBytes(buf, size);
  return buf[0];
}

int getSerialInt() {
  int size = 20;
  char buf[size];
  int result = getSerialBytes(buf, size);
  return atoi( buf );
}

void initSparki() {
  sparki.clearLCD();
//  sparki.println("Connected");
  sparki.updateLCD();
  sendSerial( (char*)SPARKI_MYRO_VERSION );
} 

void setup() 
{
}
 
void loop() {
  startOfLoop = millis();
  
  switch (action) {
    case COMMAND_INIT:                // no args; returns a char
      if (serial.available()) {
        char inByte = getSerialChar();
      }
      if(inByte == 'z')
        initSparki();                   // sendSerial is done in the function
      break;
    case LINE_FOLLOWING:
      lineLeft   = sparki.lineLeft();   // measure the left IR sensor
      lineCenter = sparki.lineCenter(); // measure the center IR sensor
      lineRight  = sparki.lineRight();  // measure the right IR sensor
      if ( lineCenter > threshold && lineLeft > threshold && lineRight > threshold){
        sparki.moveRight(180);
        theta = theta - pi;
        sparki.moveStop();
        action = STANBY;
      }
      
      if ( lineCenter < threshold ) // if line is below left line sensor
      {  
        sparki.moveForward(); // move forward
        posX += cos(theta) * (speedMotor * 0.1);
        posY += sin(theta) * (speedMotor * 0.1);
      }
      else{
        if ( lineLeft < threshold ) // if line is below left line sensor
        {  
          sparki.moveLeft(); // turn left
          theta += 2.0 * (speedMotor * 0.1) / lengthAxle;
        }
      
        if ( lineRight < threshold ) // if line is below right line sensor
        {  
          sparki.moveRight(); // turn right
          theta -= 2.0 * (speedMotor * 0.1) / lengthAxle;
        }
      }
    
      sparki.clearLCD(); // wipe the screen
      
      sparki.print("X-position: "); // show left line sensor on screen
      sparki.println(posX);
      
      sparki.print("Y-position: "); // show center line sensor on screen
      sparki.println(posY);
      
      sparki.print("Theta: "); // show right line sensor on screen
      sparki.println((theta / pi) * 180.0);

      
      sparki.updateLCD(); // display all of the information written to the screen
      
      while (millis() < startOfLoop + 100){
        // Wait and do nothing, this is used to ensure Sparki was moving for 100 msec
      }
      break;
    case STANDBY:
      sendSerial(1);
      int g = getSerialInt();
      action = LINE_FOLLOWING;
      
      
      




}
