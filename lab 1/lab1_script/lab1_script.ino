/******************************************************************************
*
* Names:    Vincent Maliko
*           Yuanyuan Li    7499879  
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


// Header files
#include <SoftwareSerial.h> 


// Global variables
int timer = 1000;    // definition of a time unit 1000s
int factor = 3;      // defintion  of a multiplicator factor

int motor_left_pin = 2;
int motor_right_pin = 4;

int pulse_left_rotation = 10;      // do not change these values
int pulse_right_rotation = 191.5;

/*****************************************************/
// Calibration values (change them according experimental results)

// Rotating
int oneRound = 3650;   //3800;    // time en ms for a robot's rotation      

// Straight line
int pulse_left_forward = 189;
int pulse_right_forward = 11;
int pulse_left_backward = 5;
int pulse_right_backward = 200;


/*****************************************************/  
// global variables (suite)
int board_LED = 13;
int LCD_display = 18;
SoftwareSerial LCD = SoftwareSerial(0, LCD_display);

String topLine= "";
String bottomLine= "";

int rotation_45 = oneRound/8;    // unit of rotation


/*****************************************************/  
/* Macros of all possible directions of both motors
 *
 *  Directions : stop, forward, backward
 *  Motors :     left, right
 */

#define MacroStopMotorLeft() analogWrite(motor_left_pin, 0)
#define MacroStopMotorRight() analogWrite(motor_right_pin, 0)

#define MacroForwardMotorLeft() analogWrite(motor_left_pin, pulse_left_forward)
#define MacroForwardMotorRight() analogWrite(motor_right_pin, pulse_right_forward)

#define MacroBackwardMotorLeft() analogWrite(motor_left_pin, pulse_left_backward)
#define MacroBackwardMotorRight() analogWrite(motor_right_pin, pulse_right_backward)


/*****************************************************/  
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

}



/*****************************************************/  
// The loop routine runs over and over again forever:
void loop(){ 
  // The instructions executed to perform the main
  // functionality of the program
 
  // display student number
  lcdDisplay("7499879", "7528357");
  
  // flashing of the led each 'timer' for 5 times
  ledFlashing(timer, 5);

 
  // Clear the lCD screen
  lcdClear();
  
  // Wait few second (5s) 
  delay(5000);
  
  
  /******************************************/  
  // path 1  
  
  lcdDisplay("path 1", "");
  delay(3000);

  // instructions
  moveForward(factor*timer);
  rotateCounterClockwise(2*rotation_45);           // turn left
  moveForward(factor*timer);  
  rotateClockwise(2*rotation_45);                  // turn right
  moveForward(factor*timer);  
  rotateClockwise(2*rotation_45);                  // turn right
  moveForward(factor*timer);  
  rotateCounterClockwise(2*rotation_45);           // turn left
  moveForward(factor*timer);  
  stopped(); 
  
  
  /******************************************/
  // path 1 reverse
 
  lcdDisplay("path 1", "reverse");
  delay(3000);

  // instructions  
  moveBackward(factor*timer); 
  rotateClockwise(2*rotation_45);                  // turn right
  moveBackward(factor*timer);  
  rotateCounterClockwise(2*rotation_45);           // turn left
  moveBackward(factor*timer);  
  rotateCounterClockwise(2*rotation_45);           // turn left
  moveBackward(factor*timer);  
  rotateClockwise(2*rotation_45);                  // turn right
  moveBackward(factor*timer); 
  stopped(); 
  
  
  /******************************************/
  // path 2
  lcdDisplay("path 2", "");
  delay(3000);
  
  // instructions
  moveForward(factor*timer);  
  rotateClockwise(2*rotation_45);                    // turn right  (90°)
  moveForward(factor*timer/2);  
  rotateCounterClockwise(3*rotation_45);             // turn left  (135°)
  moveForward(factor*timer);  
  rotateClockwise(3*rotation_45);                    // turn right (135°)
  moveForward(factor*timer);  
  rotateCounterClockwise(2*rotation_45);             // tunr left   (90°)
  moveForward(factor*timer);  
  stopped();


  /******************************************/
  // path 2 reverse

  lcdDisplay("path 2", "reverse");
  delay(3000);
  
  // instructions
  moveBackward(factor*timer);  
  rotateClockwise(2*rotation_45);                    // turn right  (90°)
  moveBackward(factor*timer);  
  rotateCounterClockwise(3*rotation_45);             // turn left  (135°)
  moveBackward(factor*timer);  
  rotateClockwise(7*rotation_45);                    // turn right (315°)
  moveBackward(factor*timer);  
  rotateCounterClockwise(2*rotation_45);             // turn left   (90°)
  moveBackward(factor*timer);  
  stopped();

  
}



 /****************************************************************/
 /*  Moving functions
  * 
  *  stopped(int t_delay)
  *  moveForward(int t_delay)
  *  moveBackward(int t_delay)
  *  rotateClockwise(int t_delay)
  *  rotateCounterClockwise(int t_delay)
  */


 /*  Name : stopped                    function which stops the robot all the time
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void stopped(){
  lcdDisplay("stopped", "");
  MacroStopMotorLeft();
  MacroStopMotorRight();
}

 /*  Name : moveForward                function which allow to move the robot forward for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void moveForward(int t_delay){
  lcdDisplay("moving", "forward");
  MacroForwardMotorLeft();
  MacroForwardMotorRight();
  delay(t_delay);
}

 /*  Name : moveBackward              function which allow to move the robot backward for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :.
  *  Return :
  */
void moveBackward(int t_delay){
  lcdDisplay("moving", "backward");
  MacroBackwardMotorLeft();
  MacroBackwardMotorRight();
  delay(t_delay);
}

 /*  Name : rotateClockwise    function which allow to rotate the robot clockwise for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  
  *  Return :
  */
void rotateClockwise(int t_delay){              // rotate to the right
  lcdDisplay("rotating", "right");
  analogWrite(motor_left_pin, pulse_right_rotation); 
  analogWrite(motor_right_pin, pulse_right_rotation); 
  delay(t_delay);
}

 /*  Name : rotateCounterClockwise    function which allow to rotate the robot counter clockwise for a delay given in parameter
  *  Param In : t_delay, int variable, time parameter
  *  Param Out :
  *  Return :
  */
void rotateCounterClockwise(int t_delay){        // rotate to the left
  lcdDisplay("rotating", "left");
  analogWrite(motor_left_pin, pulse_left_rotation); 
  analogWrite(motor_right_pin, pulse_left_rotation); 
  delay(t_delay);
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

