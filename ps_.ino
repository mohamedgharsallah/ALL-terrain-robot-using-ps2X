#include <PS2X_lib.h>

// These are used to set the direction of the bridge driver.

#define PS2_DAT        12      
#define PS2_CMD        11  
#define PS2_SEL        10  
#define PS2_CLK        13

#define speedm 3
int speedvalue=120;

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){

 // Configure output pins
 pinMode(2, OUTPUT);
 pinMode(A5, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(speedm, OUTPUT);

 // Start serial communication
 Serial.begin(9600);
  
 error = ps2x.config_gamepad(10,12,11,13, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

 // Check for error
 if(error == 0){
  Serial.println("Found Controller, configured successful");
 }
   
 else if(error == 1)
  Serial.println("No controller found, check wiring or reset the Arduino");
   
 else if(error == 2)
  Serial.println("Controller found but not accepting commands");
  
 else if(error == 3)
  Serial.println("Controller refusing to enter Pressures mode, may not support it.");
   
 // Check for the type of controller
 type = ps2x.readType();
 switch(type) {
  case 0:
    Serial.println("Unknown Controller type");
    break;
  case 1:
    Serial.println("DualShock Controller Found");
    break;
  case 2:
    Serial.println("GuitarHero Controller Found");
    break;
  }
   digitalWrite(2,HIGH);
        digitalWrite(A5,HIGH);
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(8,HIGH);
        digitalWrite(9,HIGH);
               
delay(1000);
}

// Main loop
void loop(){
   
 if(error == 1) //skip loop if no controller found
  return; 
  
 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate); // disable vibration of the controller

     // Perform movements based on D-pad buttons
     
     // MOVE FORWARD
     if(ps2x.Button(PSB_PAD_UP)) {
        analogWrite(speedm,240);
        digitalWrite(2,LOW);
        digitalWrite(A5,HIGH);
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(8,LOW);
        digitalWrite(9,HIGH);
        Serial.println("Move forward");
      }
      // TURN RIGHT
      else if(ps2x.Button(PSB_PAD_RIGHT)){
        analogWrite(speedm,240);
        digitalWrite(2,HIGH);
        digitalWrite(A5,LOW);
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        digitalWrite(8,LOW);
        digitalWrite(9,HIGH);
        Serial.println("Turn right");
      }
      // TURN LEFT
      else if(ps2x.Button(PSB_PAD_LEFT)){
        analogWrite(speedm,240);
        digitalWrite(2,LOW);
        digitalWrite(A5,HIGH);
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(8,HIGH);
        digitalWrite(9,LOW);
        Serial.println("Turn left");
      }
      // MOVE BACK
      else if(ps2x.Button(PSB_PAD_DOWN)){
         analogWrite(speedm,240);
         digitalWrite(2,HIGH);
        digitalWrite(A5,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        digitalWrite(8,HIGH);
        digitalWrite(9,LOW);
        Serial.println("Move back");
      }  
      

      else if (ps2x.Button(PSB_BLUE)) 
      { analogWrite(speedm,speedvalue);
        digitalWrite(2,HIGH);
        digitalWrite(A5,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        digitalWrite(8,HIGH);
        digitalWrite(9,LOW);
        Serial.println("Move back");
      } 
      


      else if (ps2x.Button(PSB_GREEN)) 
      { analogWrite(speedm,speedvalue);
        digitalWrite(2,LOW);
        digitalWrite(A5,HIGH);
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(8,LOW);
        digitalWrite(9,HIGH);
        Serial.println("Move forward");
       
      } 

      else if (ps2x.Button(PSB_PINK)) 
      { analogWrite(speedm,speedvalue);
        digitalWrite(2,LOW);
        digitalWrite(A5,HIGH);
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(8,HIGH);
        digitalWrite(9,LOW);
        Serial.println("Turn left");
      } 
      


      else if (ps2x.Button(PSB_RED)) 
      { analogWrite(speedm,speedvalue);
        digitalWrite(2,HIGH);
        digitalWrite(A5,LOW);
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        digitalWrite(8,LOW);
        digitalWrite(9,HIGH);
        Serial.println("Turn right");
       
      } 
      //speed
      else if (ps2x.Button(PSB_L1)) 
      { 
        if(speedvalue<0) speedvalue=0;
        if(speedvalue>170) speedvalue=170;
       speedvalue+=15;
       analogWrite(speedm,speedvalue);
      } 
      
     else if (ps2x.Button(PSB_L2)) 
      { 
        if(speedvalue<0) speedvalue=0;
        if(speedvalue>170) speedvalue=170;
       speedvalue-=15;
       analogWrite(speedm,speedvalue);
      } 
      

      
      else
        { 
        digitalWrite(2,HIGH);
        digitalWrite(A5,HIGH);
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(8,HIGH);
        digitalWrite(9,HIGH);
          }
 }  
 delay(50);  
}
