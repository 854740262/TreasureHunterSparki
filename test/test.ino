
#include <Sparki.h> // include the sparki library

void setup() 
{
  sparki.clearLCD();
  sparki.servo(SERVO_CENTER); 
  //serial.begin(9600);
}

void loop() {
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  sparki.clearLCD();
  sparki.print("Left: ");
  sparki.println(lineLeft);

  sparki.print("Right: ");
  sparki.println(lineRight);

  sparki.print("Center: ");
  sparki.println(lineCenter);
  sparki.updateLCD(); // display all of the information written to the screen
  
}
