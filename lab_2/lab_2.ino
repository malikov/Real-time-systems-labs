/******************************************************************************
*
* Names:    Vincent Maliko 4225528
*           Yuanyuan Li     
*           Rémi Lacroix   7528357
*                

* Course Code:   SEG 4145
* Lab Number:    2
* File name:     lab2
* Date:          January 30, 2014
*
*
* Description
* *************
* This current file is the file template of the lab #1:
* Introduction to the Arduino IDE and the Robotic Platform
* 
*
******************************************************************************
*/

// header files
#include <SoftwareSerial.h> 
#include <Servo.h>


// Global variables
int timer = 1000;    // definition of a time unit 1000s
int factor = 3;      // defintion  of a multiplicator factor

int motor_left_pin = 2;
int motor_right_pin = 4;

Servo leftWheelServo;
Servo rightWheelServo;

/*****************************************************/
// Rotating
//int fullRotation = 3650;   // time en ms for a full robot's rotation      

/*
  We need to use the sensor in order to assess the angles and time for rotating at a 90 degre angle, see last part of lab 2 manual.
*/

// Straight line
int pulse_left_forward = 180;
int pulse_right_forward = 0;

int pulse_left_backward = 0;
int pulse_right_backward = 180;

int stopVal;

/*****************************************************/  
// global variables (suite)
int board_LED = 13;
int LCD_display = 18;

SoftwareSerial LCD = SoftwareSerial(0, LCD_display);

String topLine= "";
String bottomLine= "";

//int rotation_45 = fullRotation/8;    // unit of rotation


/*****************************************************/  
/* Macros of all possible directions of both motors
 *
 *  Directions : stop, forward, backward
 *  Motors :     left, right
 */

#define MacroStopMotorLeft() leftWheelServo.detach()
#define MacroStopMotorRight()  rightWheelServo.detach()

#define MacroStartMotorLeft() leftWheelServo.attach(motor_left_pin)
#define MacroStartMotorRight()  rightWheelServo.attach(motor_right_pin)

#define MacroForwardMotorLeft() leftWheelServo.write(pulse_left_forward)
#define MacroForwardMotorRight() rightWheelServo.write(pulse_right_forward)

#define MacroBackwardMotorLeft() leftWheelServo.write(pulse_left_backward)
#define MacroBackwardMotorRight() rightWheelServo.write(pulse_right_backward)


// The setup routine runs once when you press reset:
// This function is called before the loop() function
void setup(){
  
  stopVal = 0;
  
  // Open the serial port at 9600 bps
  Serial.begin(9600);
  
  // Open the serial port to write data at 9600 bps
  LCD.begin(9600); 
  
  lcdDisplay("Setup", "...");
}


// The loop routine runs over and over again forever:
void loop(){ 
  lcdDisplay("7499879", "7528357");
  
  // flashing of the led each 'timer' for 5 times
  ledFlashing(timer, 5);
  
  // Clear the lCD screen
  lcdClear();
  
  // Wait few second (5s) 
  delay(5000);
  
  path();
  
  stopped(5000);
  
  Serial.println("\n -----------------------------------\n");
}





/* Functions
*
* 
*/

void path(){
  
  Serial.println("\n -----------------------------------\n");
  moveForward(5000);
  virtualStop(); //required in order to transition to the next state otherwhise the robot keeps moving straight
  
  Serial.println("left wheel value after moveforward :");
  Serial.println(leftWheelServo.read());
  Serial.println("right wheel value after moveforward :");
  Serial.println(rightWheelServo.read());
  
  // rotating to the right
  rotateClockwise(1000);// 1000 should be assess using the sensors  NOT DONE YET
  virtualStop();
  
  Serial.println("left wheel value after spin :");
  Serial.println(leftWheelServo.read());
  Serial.println("right wheel value after spin :");
  Serial.println(rightWheelServo.read());
  
  moveForward(5000);
  virtualStop();
  
  rotateClockwise(1000); // same comment as above for the value 1000
  virtualStop();
  
  moveForward(7500);
  virtualStop();
  
  rotateClockwise(1000);
  virtualStop();
  
  moveForward(7500);
  virtualStop();
  
  rotateClockwise(1000);
  virtualStop();
  
  moveForward(5000);
  virtualStop();
  
  rotateCounterClockwise(500);
  virtualStop();
  
  moveForward(1000);
  virtualStop();
  
  rotateCounterClockwise(1500);
  virtualStop();
  
  moveForward(10000);
  virtualStop();
  
  rotateCounterClockwise(1000);
  virtualStop();
  
  moveForward(5000);
  virtualStop();
}

 /*  Name : stopped                    function which stops the robot for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void stopped(int delay_t){
  MacroStopMotorLeft();
  MacroStopMotorRight();
  
  stopVal = 0;
  delay(delay_t);
}

 /*  Name : moveForward                function which allow to move the robot forward for a delay given in parameter
  *  Param In : delay_t, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void moveForward(int delay_t){
  lcdDisplay("moving", "forward");
  
  startMotor();
  
  MacroForwardMotorLeft();
  MacroForwardMotorRight();
  
  stopVal = 1;
  delay(delay_t);
}




 /*  Name : moveBackward              function which allow to move the robot backward for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void moveBackward(int t_delay){
  lcdDisplay("moving", "backward");
  
  startMotor();
  
  MacroForwardMotorLeft();
  MacroForwardMotorRight();
  
  stopVal = 1;
  delay(t_delay);
}

 /*  Name : rotateCounterClockwise    function which allow to rotate the robot counter clockwise for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void rotateCounterClockwise(int t_delay){    // rotate to the left
  
  // we need to use the sensor to assess the time required for the rotation
  
  lcdDisplay("rotating", "left");
  startMotor();
  
  leftWheelServo.write(pulse_left_backward);
  rightWheelServo.write(pulse_right_forward);
  
  stopVal = 1;
  delay(t_delay);
}

 /*  Name : rotateClockwise    function which allow to rotate the robot clockwise for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void rotateClockwise(int t_delay){          // rotate to the right
  
  // we need to use the sensor to assess the time required for the rotation
  
  lcdDisplay("rotating", "right");
  startMotor();
  
  leftWheelServo.write(pulse_left_forward);
  rightWheelServo.write(pulse_right_backward);
  
  stopVal = 1;
  delay(t_delay);
}

/*
  Utility functions
*/

/*  Name : startMotor                function which allow for attaching the servo
  *  Param In : 
  *  Param Out :
  *  Return :
  */
void startMotor(){
  if(stopVal == 1)
    return;
    
  MacroStartMotorLeft();
  MacroStartMotorRight();
}

/*  Name : virtualStop                this is required in order to transition from one state to the other.
  *  Param In : 
  *  Param Out :
  *  Return :
  */
void virtualStop(){
  /*
    35 microseconds is the length of a tick, this value could be differrent for the next lab ??
  */
  stopped(35);
}

/****************************************************************/
/*  LCD functions
 *
 *  ledFlashing(int t_delay, int n_flash)
 *  lcdDisplay(String topLine, String bottomLine)
 *  lcdPosition(int row, int col)
 *  lcdClear()
 *  backlightOn()
 */


 /*  Name : ledFlashing    function which allow to flash the led for a certain number of times and during  
  *  Param In : t_delay , int variable , time between to flash of the led
  *             n_flash , int variable , number of flash of the led
  *  Param Out :
  *  Return :
  */
  void ledFlashing(int t_delay, int n_flash){
    //Loop for the led - total time n_flash x t_delay
    for (int i = 0; i < 5; i++) {
    
      digitalWrite(board_LED, HIGH);      // turn the LED on
      delay(timer);
    
      digitalWrite(board_LED, LOW);      // turn the LED off
      delay(timer);
    }
  }
  
 /*  Name : lcdDisplay    function which allow to display text on the LCD screen
  *  Param In : topLine    , String variable , text displayed on the top line of the LCD screen
  *             bottomLine , string variable , text displayed on the bottom line of the LCD screen
  *  Param Out :
  *  Return :
  */
void lcdDisplay(String topLine, String bottomLine){
  
  // Calculation of the line offset for both line of the LCD screen
  int topLineOffset = int((16-topLine.length())/2);
  int bottomLineOffset = int((16-topLine.length())/2);

  // Clear the LCD screen
  backlightOn();
  //displayOn();
  lcdClear();
  
  // Print the top line text
  if(topLine.length() > 0){
    lcdPosition(0, topLineOffset);
    LCD.print(topLine);              // or try with write()    !!!
  }
  
  // Print the bottom line text
  if(bottomLine.length() > 0){
    lcdPosition(1, bottomLineOffset);
    LCD.print(bottomLine);
  }
}


 /*  Name : lcdPosition    function which allow to place the cursor on a specific position (row, col)
  *  Param In : row , int variable , row=0 : top line / row=1 : bottom line
  *             col , int variable , position on the line / range 0-15
  *  Param Out :
  *  Return :
  */
void lcdPosition(int row, int col){
  LCD.write(0xFE);                     // put LCD in command mode
  LCD.write((col + row*64 + 128));     // place the cursor in the desired position
  delay(10);
}


 /*  Name : lcdClear    function which allow to clear the LCD screen
  *  Param In :
  *  Param Out :
  *  Return :
  */
void lcdClear(){
  LCD.write(0xFE);    // put LCD in command mode
  LCD.write(0x01);    // clear the LCD screen
  delay(10);
}


 /*  Name : backlightOn    function which allow to turn on the back light
  *  Param In :
  *  Param Out :
  *  Return :
  */
void backlightOn(){
  LCD.write(0x7C);   // command flag for backlight stuff
  LCD.write(0x9D);   // turn on back light
  delay(10);
}



/****************************************************************/
void displayOn(){ 
  LCD.write(0xFE);    // Put LCD in command mode
  LCD.write(0x0C);    // Turn on the display
}

void displayOff(){ 
  LCD.write(0xFE);    // Put LCD in command mode
  LCD.write(0x08);    // Turn off the display
}

void backlightOff(){
    LCD.write(0x7C);  // Command flag for backlight stuff
    LCD.write(0x80);  // Turn off back light
   delay(10);
}



