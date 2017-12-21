
#include <Sparki.h> // include the sparki library



unsigned long startOfLoop; // Time since start of program, calculated at each loop beginning
const float pi = 3.1415926;

const float speedMotor = 0.3 / (10773.0 / 1000.0); // m / s
const float lengthAxle = 0.084; // meters

float posX = 0.0;
float posY = 0.0;
float theta = 0; // Initially facing left ("West" or 180 degrees)

int threshold = 950;

//int lineLeft;
//int lineCenter;
//int lineRight;


void setup() 
{
  sparki.clearLCD();
  sparki.servo(SERVO_CENTER); 
  serial.begin(9600);
}

void line_following(){
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  
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
    
    else{
        
      //sparki.moveRight(180);
      theta = theta - pi;
      sparki.moveStop();
      //action = COMMAND_STANDBY;
      //sendSerial('f');
  
    }
    
  }


  sparki.clearLCD(); // wipe the screen
  
  sparki.print("X-position: "); // show left line sensor on screen
  sparki.println(posX);
  
  sparki.print("Y-position: "); // show center line sensor on screen
  sparki.println(posY);
  
  sparki.print("Theta: "); // show right line sensor on screen
  sparki.println((theta / pi) * 180.0);

  sparki.print("Left: ");
  sparki.println(lineLeft);

  sparki.print("Right: ");
  sparki.println(lineRight);

  sparki.print("Center: ");
  sparki.println(lineCenter);

  
  sparki.updateLCD(); // display all of the information written to the screen
  
}


 
void loop() {
  //startOfLoop = millis();

  //if (serial.available()) {
    //char inByte = getSerialChar();
    //action = inByte;
  //}
  //sparki.clearLCD();
  //sparki.print("action: ");
  //sparki.println(action);
  //sparki.updateLCD();

      line_following();
      //action = COMMAND_LINE_FOLLOWING;
      

    
    
  
  //sendSync();
  //while (millis() < startOfLoop + 100){
    // Wait and do nothing, this is used to ensure Sparki was moving for 100 msec
  //}
}
