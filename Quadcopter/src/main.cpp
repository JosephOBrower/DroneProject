#include "Drone.h"
/*Notes: 
#1 For every serial.print call the loop iteration speed will decrease by 6ms!
#2 Make sure that your throttle position is at the 0 position BEFORE you turn on the drone ;D
#3 The red LED light must be off before you move the throttle
*/
//the motor pins should be 11, 10, 9, 3
Drone drone(3, 9, 10, 11, 5, 6, 4);
void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(14400);
  drone.setUP();
  
} 
void loop() {
  drone.getHC12Instruction();
  drone.applyMotorValues();
  drone.adjustMotorValuesToBalance();
  drone.runMotors();
  //drone.serialDebug();//This will add 15ms to each loop!
}
