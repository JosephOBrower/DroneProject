#include "Arduino.h"
//#include <Servo.h>
/**
 * @brief This will control the motors using a pwm signal. 
 * Main.cpp controls the motor's speed by inputing values
 * from 0% and 100% (0-100)
 * @attention You must send an analogWrite signal between
 * 130-240 to run the motors
 */
class Motor{
public:
    Motor(int pin){pin_ = pin;};
    ~Motor(){};
    /* note you must write a value between 0-180*/
    void write();//write the speed to the motor (send a value between 0-60)
    //I use this to program the ESC motor ranges
    void write(int val);//writes a raw value to the motor. Must send a value between "lower_motor_range_" and "upper_motor_range_"
    void attachMotor(int upper_range, int lower_range);
    void setMotorSpeed(int val);//set the speed (send value between 0-100)
    bool isZero();//chesk to see if the motor speed is zero
    int getSpeed(){return motor_speed_;};//get the speed of the motor (0-100)
    void motorStop();//stops the motor
    void setESCMotorRange();
private:
    //variables
    int motor_speed_;
    int pin_;
    int upper_range_, lower_range_;
};