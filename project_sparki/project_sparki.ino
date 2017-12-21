
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
float maxspeed=0.0285;    // [m/s] speed of the robot that you measured
float alength=0.0851;     // [m] axle length  
float phildotr=0, phirdotr=0; // wheel speeds that you sent to the motors
float Xi=0, Yi=0, Thetai=0;
float Xrdot, Thetardot;
float Xg = 0.13;
float Yg = 0.11;
float rho;
int threshold = 700;


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
  int threshold = 800;
  
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  if ( lineCenter < threshold ) // if line is below left line sensor
  {  
    sparki.moveForward(); // move forward
    phildotr=maxspeed;
    phirdotr=maxspeed;
  }
  else{
    if ( lineLeft < threshold ) // if line is below left line sensor
    {  
      sparki.moveLeft(); // turn left
      phildotr=-maxspeed;
      phirdotr=maxspeed;
    }
  
    if ( lineRight < threshold ) // if line is below right line sensor
    {  
      sparki.moveRight(); // turn right
      phildotr=maxspeed;
      phirdotr=-maxspeed;
    }
      
  }


  sparki.clearLCD(); // wipe the screen
  
  sparki.print(Xi);
  sparki.print("/");
  sparki.print(Yi);
  sparki.print("/");
  sparki.print(Thetai);
  sparki.println();
  sparki.print("Left: ");
  sparki.println(lineLeft);
  sparki.print("Right: ");
  sparki.println(lineRight);
  sparki.print("Center: ");
  sparki.println(lineCenter);
  sparki.print("action: ");
  sparki.println(action);
  sparki.print("rho: ");
  sparki.println(rho);
  
    
  sparki.updateLCD(); // display all of the information written to the screen

  // perform odometry
  Xrdot=phildotr/2.0+phirdotr/2.0;
  Thetardot=phirdotr/alength-phildotr/alength;
  
  Xi=Xi+cos(Thetai)*Xrdot*0.1;
  Yi=Yi+sin(Thetai)*Xrdot*0.1;
  Thetai=Thetai+Thetardot*0.1;
  
}


 
void loop() {
  startOfLoop = millis();
  if (serial.available()) {
    action = getSerialChar();
  }
  //sparki.clearLCD();
  //sparki.print("action: ");
  //sparki.println(action);
  //sparki.updateLCD();
  switch (action) {  
    case COMMAND_INIT:                // no args; returns a char
      initSparki();
      action = COMMAND_STANDBY;   
      break;
    case COMMAND_LINE_FOLLOWING:
      line_following();
      action = COMMAND_LINE_FOLLOWING;
      rho = sqrt((Xi-Xg)*(Xi-Xg)+(Yi-Yg)*(Yi-Yg));
      if(rho < 0.02){
        sendSerial('f');
        Xg = 0;
        Yg = 0;
        sparki.moveRight(180);
        Thetai = Thetai - pi;
        action = COMMAND_STANDBY;
      }
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
  sendSync();
  while (millis() < startOfLoop + 100){
    // Wait and do nothing, this is used to ensure Sparki was moving for 100 msec
  }
}
