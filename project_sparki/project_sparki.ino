
#include <Sparki.h> // include the sparki library


/* ########### CONSTANTS ########### */
/* ***** VERSION NUMBER ***** */
const char* SPARKI_MYRO_VERSION = "1.1.3r1";   

/* ***** MESSAGE TERMINATOR ***** */
const char TERMINATOR = (char)23;  

/* ***** ACTION TERMINATOR ***** */
const char SYNC = (char)22;   

/* ***** COMMAND CHARACTER CODES ***** */
const char COMMAND_INIT = 'z';
const char COMMAND_LINE_FOLLOWING = 's';
const char COMMAND_STANDBY = 'b';

/* ***** SERIAL PORT FOR BLUETOOTH ***** */
#define serial Serial1

char action = COMMAND_STANDBY;

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

void sendSync() {
//  printDebug(".", DEBUG_DEBUG);
  serial.print(SYNC);
  serial.flush();
}

void setup() 
{
    sparki.clearLCD();
  sparki.servo(SERVO_CENTER); 
  serial.begin(9600);
}

void line_following(){
  lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  lineCenter = sparki.lineCenter(); // measure the center IR sensor
  lineRight  = sparki.lineRight();  // measure the right IR sensor
  if ( lineCenter > threshold && lineLeft > threshold && lineRight > threshold){
    sparki.moveRight(180);
    theta = theta - pi;
    sparki.moveStop();
    action = COMMAND_STANDBY;
    sendSerial('f');
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
}


 
void loop() {
  startOfLoop = millis();
  if (serial.available()) {
    char inByte = getSerialChar();
    if(!inByte) inByte = action;
    switch (inByte) {
      case COMMAND_INIT:                // no args; returns a char
        initSparki();
        action = COMMAND_STANDBY;   
        break;
      case COMMAND_LINE_FOLLOWING:
        line_following();
        action = COMMAND_LINE_FOLLOWING;
        break;
      case COMMAND_STANDBY:
        sparki.moveStop();
        action = COMMAND_STANDBY;
        break;
      default:
        sparki.print("Bad input");
        sparki.updateLCD();
        break;
    
    }
  }
  sendSync();
  while (millis() < startOfLoop + 100){
    // Wait and do nothing, this is used to ensure Sparki was moving for 100 msec
  }
}
