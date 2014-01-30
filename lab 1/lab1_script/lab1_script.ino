/******************************************************************************
*
* Names:    Vincent Maliko
*           Yuanyuan Li     
*           Rémi Lacroix   7528357
*                

* Course Code:   SEG 4145
* Lab Number:    1
* File name:     lab1_script
* Date:          January 16, 2014
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

// macro in an header files



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


int left_value = 184.9;
int right_value = 14;

/* Macros of all possible directions of both motors
*
*  Directions : stop, forward, backward
*  Motors :     left, right
*/

#define MacroStopMotorLeft() analogWrite(motor_left_pin, 0)
#define MacroStopMotorRight() analogWrite(motor_right_pin, 0)

#define MacroForwardMotorLeft() analogWrite(motor_left_pin, left_value)
#define MacroForwardMotorRight() analogWrite(motor_right_pin, right_value)

#define MacroBackwardMotorLeft() analogWrite(motor_left_pin, right_value)
#define MacroBackwardMotorRight() analogWrite(motor_right_pin, left_value)



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
   
  int oneRound = 4400;
  
  /******************************************/
  // path 1
  lcdDisplay("path 1",5, "",1);
  delay(3000);

  
  moveForward(5*timer);  
  rotateClockwise(2*rotation_45);  // left
  moveForward(5*timer);  
  rotateCounterClockwise(2*rotation_45); // right
  moveForward(5*timer);  
  rotateCounterClockwise(2*rotation_45);     // right
  moveForward(5*timer);  
  rotateClockwise(2*rotation_45);     // left
  moveForward(5*timer);  
  stopped(4*rotation_45);
 
  
  /******************************************/
  // path 1 reverse
  delay(5000);
  
  lcdDisplay("path 1",5, "reverse",5);
  delay(3000);

  
  moveBackward(5*timer); 
  rotateCounterClockwise(2*rotation_45);      // right
  moveBackward(5*timer);  
  rotateClockwise(2*rotation_45);             // left
  moveBackward(5*timer);  
  rotateClockwise(2*rotation_45);             // left
  moveBackward(5*timer);  
  rotateCounterClockwise(2*rotation_45);      // right
  moveBackward(5*timer); 
  stopped(4*rotation_45); 
  
  /******************************************/
  // path 2
 /* lcdDisplay("path 2",5, "",1);
  delay(3000);
  
  moveForward(5*timer);  
  rotateCounterClockwise(2*rotation_45);      // right (90°)
  moveForward(5*timer);  
  rotateClockwise(3*rotation_45);             // left  (135°)
  moveForward(5*timer);  
  rotateCounterClockwise(3*rotation_45);     // right  (135°)
  moveForward(5*timer);  
  rotateClockwise(2*rotation_45);           // left  (90°)
  moveForward(5*timer);  
  stopped(5*timer); 
*/

  /******************************************/
  // path 2 reverse
  /*lcdDisplay("path 2",5, "reverse",5);
  delay(3000);
  
  moveBackward(5*timer);  
  rotateCounterClockwise(2*rotation_45);      // right (90°)
  moveBackward(5*timer);  
  rotateClockwise(3*rotation_45);             // left  (135°)
  moveBackward(5*timer);  
  rotateCounterClockwise(3*rotation_45);     // right  (135°)
  moveBackward(5*timer);  
  rotateClockwise(2*rotation_45);            // left  (90°)
  moveBackward(5*timer);  
  stopped(5*timer);   */
}




// The loop routine runs over and over again forever:
void loop(){ 
  // The instructions executed to perform the main
  // functionality of the program
  
   // Programmation Path 1
  //lcdPosition(1,6);
  //LCD.print("Path 1");
 
  
  
  /*
  LCD.write(0xFE); // Put the LCD screen in command mode.
  LCD.write(1 + 6*64 + 128); // Place the cursor in the position (1,6).
  LCD.write(0x01); // Clear the LCD screen
  delay(10);
  
  LCD.print("hello");
  *\
  /*
  // Diplay student number
  
  LCD.print("7528357");
  LCD.write(2 + 6*64 + 128); // Place the cursor in the position (1,6).
  LCD.print("7528357"); 
  
  //Loop for the led - total time 5000s
  for (int i = 0; i >= 4; i++) {
    // turn the LED on:
    digitalWrite(board_LED, HIGH);
    delay(timer);
    // turn the LED off:
    digitalWrite(board_LED, LOW);
  }

  // Programmation Path 1
  LCD.write(0x01); // Clear the LCD screen
  LCD.write(1 + 6*64 + 128); // Place the cursor in the position (1,6).
  LCD.print("Path 1");

  
  
  // Programmation Path 2
  LCD.write(0x01); // Clear the LCD screen
  LCD.write(1 + 6*64 + 128); // Place the cursor in the position (1,6).
  LCD.print("Path 2");
  
  */
  
  // rotation of the robot in one direction
  /*analogWrite(motor_left_pin, 10); 
  analogWrite(motor_right_pin, 191.5); 
  delay(10000);        // wait 30s before to stop
*/


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


