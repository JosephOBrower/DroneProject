#include "Motor.h"

void Motor::attachMotor(int upper_range, int lower_range){//constructor
    pinMode(pin_, OUTPUT);
    upper_range_ = upper_range;
    lower_range_ = lower_range;
}

void Motor::write(){//write the speed to the motor
    analogWrite(pin_, map(motor_speed_, 0, 60, lower_range_, upper_range_));
}
void Motor::write(int val){//WARNING: must send a value between "lower_motor_range_" and "upper_motor_range_"
    analogWrite(pin_, val);
}
void Motor::setMotorSpeed(int val){//set the speed (send value between 0-60)
    if(val < 0 || val > 60){
        return;
    }
    motor_speed_ = val;
    return;
}
bool Motor::isZero(){//checks to see if the motor speed is 0
    if(motor_speed_ == 0){
        return true;
    }
    return false;
}
void Motor::motorStop(){
    motor_speed_ = 0;
    Motor::write();
}