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


// global variables
int i = 1;
int timer = 1000;    // unit 1000s
int rotation_45 = 550;
int pin = 1;
int motor_left_pin = 2;
int motor_right_pin = 4;
int board_LED = 13;
int LCD_display = 18;
SoftwareSerial LCD = SoftwareSerial(0, 18);

//Using servo for the motion of the wheels
Servo leftWheelServo; 
Servo rightWheelServo;

/* Macros of all possible directions of both motors
*
*  Directions : stop, forward, backward
*  Motors :     left, right
*/

#define MacroStopMotorLeft() analogWrite(motor_left_pin, 0)
#define MacroStopMotorRight() analogWrite(motor_right_pin, 0)

#define MacroForwardMotorLeft() leftWheelServo.write(180)
#define MacroForwardMotorRight() rightWheelServo.write(0)

#define MacroBackwardMotorLeft() leftWheelServo.write(0)
#define MacroBackwardMotorRight() rightWheelServo.write(180)



// The setup routine runs once when you press reset:
// This function is called before the loop() function
void setup(){
  // Initialization instructions
  
  // Sets the digital pin as output
  pinMode(motor_left_pin, OUTPUT);
  pinMode(motor_right_pin, OUTPUT);      
  pinMode(board_LED,OUTPUT);
  pinMode(LCD_display, OUTPUT);
  
 
  
  // Open the serial port at 9600 bps
  Serial.begin(9600);
  
  // Open the serial port to write data at 9600 bps
  LCD.begin(9600);
 
 
  //Loop for the led - total time 5000s
  for (int i = 0; i < 5; i++) {
    // turn the LED on:
    digitalWrite(board_LED, HIGH);
    delay(timer);
    // turn the LED off:
    digitalWrite(board_LED, LOW);
    delay(timer);
  }
  
  
  lcdDisplay("7528357",4, "7528357",4);
  delay(5000);
   
  int bottomToTopRound = 4*timer;
  
  /******************************************/
  // Path
  lcdDisplay("Path ",5, "",1);
  delay(3000);

  
  //moveForward(2*timer);  
  /*rotateClockwise(2*rotation_45);  // left
  moveForward(5*timer);  
  rotateCounterClockwise(2*rotation_45); // right
  moveForward(5*timer);  
  rotateCounterClockwise(2*rotation_45);     // right
  moveForward(5*timer);  
  rotateClockwise(2*rotation_45);     // left
  moveForward(5*timer);  
  stopped(4*rotation_45);
 */
  
}




// The loop routine runs over and over again forever:
void loop(){ 
  moveForward(5*timer);  
  stopped(4*timer);
}





/* Functions
*
* 
*/

 /*  Name : stopped                    function which stops the robot for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void stopped(int t_delay){
  lcdDisplay("stopped",5, "",1);
  MacroStopMotorLeft();
  MacroStopMotorRight();
  delay(t_delay);
}

 /*  Name : moveForward                function which allow to move the robot forward for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void moveForward(int t_delay){
  lcdDisplay("moving",4, "forward",4);
  MacroForwardMotorLeft();
  MacroForwardMotorRight();
  delay(t_delay);
}

 /*  Name : moveBackward              function which allow to move the robot backward for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void moveBackward(int t_delay){
  lcdDisplay("moving",4, "backward",4);
  MacroBackwardMotorLeft();
  MacroBackwardMotorRight();
  delay(t_delay);
}

 /*  Name : rotateCounterClockwise    function which allow to rotate the robot counter clockwise for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void rotateCounterClockwise(int t_delay){    // rotate to the right
  lcdDisplay("rotating",3, "right",5);
  analogWrite(motor_left_pin, 191.5); 
  analogWrite(motor_right_pin, 191.5); 
  delay(t_delay);
}

 /*  Name : rotateClockwise    function which allow to rotate the robot clockwise for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void rotateClockwise(int t_delay){          // rotate to the left
  lcdDisplay("rotating",3, "left",5);
  analogWrite(motor_left_pin, 10); 
  analogWrite(motor_right_pin, 10); 
  delay(t_delay);
}



// LCD functions

 /*  Name : rotateClockwise    function which allow to rotate the robot clockwise for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void lcdDisplay(String topLine, int topLineOffset, String bottomLine, int bottomLineOffset) {
  // Clear the LCD screen
  backlightOn();
  clearLCD();
  // Print the top line
  if(topLine.length() > 0) {
    lcdPosition(0,topLineOffset);
    LCD.print(topLine);
  }
  // Print the bottom line text
  if(bottomLine.length() > 0) {
    lcdPosition(1,bottomLineOffset);
    LCD.print(bottomLine);
  }
}

void lcdPosition(int row, int col) {
  LCD.write(0x01); // Clear the LCD screen
  LCD.write(0xFE); //Put LCD in command mode
  LCD.write((col + row*64 + 128)); //Place the cursor
  delay(10);
}

void clearLCD(){
  LCD.write(0xFE); //Put LCD in command mode
  LCD.write(0x01); //clear command.
  delay(10);
}

void backlightOn() { //turns on the backlight
  LCD.write(0x7C); //command flag for backlight stuff
  LCD.write(157); //light level.
  delay(10);
}



/******************************************************************************
*
* Name
**************
* functionName
*
*
* Description
* *************
* The description goes here
*
*
* Parameters
* *************
* Name        Type       In/Out          Description
* ----------- ---------- --------------- ---------------
* x           int        In              Description of x variable
* y           char       In              Description of y variable
* z           double     In              Description of z variable
*
*
* Returns
* *************
* Name        Type       Description
* ----------- ---------- ---------------
* a           int        Description of a
*
*
******************************************************************************
*/


