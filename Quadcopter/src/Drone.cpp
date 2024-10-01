#include "Drone.h"

void Drone::serialDebug(){
    double ax, ay, rgx, rgy, rgz, gx,gy;
    //int address;
    my_imu.getXYAngle(ax, ay, gx, gy);
    my_imu.getRawGyrXYZ(rgx, rgy, rgz);
    //Serial.print(String(gx) + "," + String(rgx) + "," + String(ax)/* + "," + String(0)*/);
    //Serial.print ("Channel[0]: " + (String)channel[0] + "\tChannel[1]: " + channel[1] + "\tChannel[2]: " + channel[2] + "\tChannel[3]: " + channel[3]);
    Serial.print(String(m1.getSpeed()) + "," + m2.getSpeed() + "," + m3.getSpeed() + "," + m4.getSpeed());
    Serial.println();
}
void Drone::adjustMotorValuesToBalance(){
    if(channel[0] > 1){
        double current_errorY;
        /// @brief 
        double current_errorX;
        /// @brief Rate of angle change for the x axis
        double gx;
        /// @brief Rate of angle change for the y axis
        double gy;
        //setting target angle
        target_angleX_ = 0.8*(channel[1] - 31);
        target_angleY_ = 0.8*(channel[2] - 31);
        my_imu.getXYAngle(current_errorX, current_errorY, gx, gy);
        //for tilting the drone
        current_errorX = current_errorX + target_angleX_;
        current_errorY = current_errorY - target_angleY_;
        //Your PI flight controler
        double motorX_adjust = (P * current_errorX)+ (D * gx);
        double motorY_adjust = (P * current_errorY)+ (D * gy);
        //set motor speed
        m2.setMotorSpeed(m2.getSpeed() + motorX_adjust);
        m4.setMotorSpeed(m4.getSpeed() - motorX_adjust);
        m1.setMotorSpeed(m1.getSpeed() - motorY_adjust);
        m3.setMotorSpeed(m3.getSpeed() + motorY_adjust);
        //Serial.print((String)m2.getSpeed() + ",");
        //Serial.print((String)m4.getSpeed() + ",");
        //Serial.print((String)gx + ",");
        //Serial.print(0);
        //Serial.println();
        //store the past error
        prev_errorX = current_errorX;
        prev_errorY = current_errorY;
    }
    return;
}
void Drone::setESCMotorRange(){
    m1.write(upper_motor_range_);
    m2.write(upper_motor_range_);
    m3.write(upper_motor_range_);
    m4.write(upper_motor_range_);
    delay(5500);
    m1.write(lower_motor_range_);
    m2.write(lower_motor_range_);
    m3.write(lower_motor_range_);
    m4.write(lower_motor_range_);
    delay(2000);
}
void Drone::setUP(){
    m1.attachMotor(upper_motor_range_, lower_motor_range_);
    m2.attachMotor(upper_motor_range_, lower_motor_range_);
    m3.attachMotor(upper_motor_range_, lower_motor_range_);
    m4.attachMotor(upper_motor_range_, lower_motor_range_);
    setESCMotorRange();
    my_imu.begin();
    hc.begin();
    //delay(1000);
    digitalWrite(13, LOW);
}
void Drone::getHC12Instruction(){
    int address;
    if(hc.available()){
        while(hc.available()){
            channel[address] = jb.readJByte(hc.read(), address);
        }
        hc.flush();
        hc.setTimeOfLastInstruction(millis());
        return;
    }
    if((millis() - hc.getTimeOfLastInstruction()) > 200){
        channel[0] = 0; channel[1] = 0; channel[2] = 0; channel[3] = 0;
    }
    return;
}
void Drone::applyMotorValues(){
    m1.setMotorSpeed(channel[0]);
    m2.setMotorSpeed(channel[0]);
    m3.setMotorSpeed(channel[0]);
    m4.setMotorSpeed(channel[0]);
}
void Drone::runMotors(){
    m1.write();
    m2.write();
    m3.write();
    m4.write();
    //Serial.println("==================================== " + (String)map(channel[0], 0, 60, 130, 240));
    //analogWrite(10, map(channel[0], 0, 60, 130, 240));
    //analogWrite(9, map(channel[0], 0, 60, 130, 240));
    //analogWrite(11, map(channel[0], 0, 60, 130, 240));
    //analogWrite(3, map(channel[0], 0, 60, 130, 240));
}