#include "BNO055.h"
//Sets up the IMU and starts the timer
void BNO055::begin(){
    imu_ = Adafruit_BNO055();
    if(!imu_.begin()){
        Serial.println("No BNO055 detected");
    }
    delay(0);//give the BNO055 time to start up
    imu_.setExtCrystalUse(true);
    ms_old_ = millis();//start the timer
}
//This will get the raw accel readings
void BNO055::getRawAccXYZ(double &x, double &y, double &z){
    imu::Vector<3> acc = getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    x = acc.x(); y = acc.y(); z = acc.z();
}
//This will get the raw gyro readings
void BNO055::getRawGyrXYZ(double &x, double &y, double &z){
    imu::Vector<3> gyr = getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    x = gyr.x(); y = gyr.y(); z = gyr.z();
}
//This will return the angle x and y accel readings
void BNO055::getAccXYAngle(double &ax, double &ay){
    double x,y,z;
    getRawAccXYZ(x,y,z);
    ax = atan2(y/9.8, z/9.8) * 180/PI;
    ay = -1*atan2(x/9.8, z/9.8) * 180/PI;
}
void BNO055::getXYAngle(double &ax, double &ay){
    unsigned long dt = (millis() - ms_old_) / 1000.;
    ms_old_ = millis();
    double gx, gy, gz, angle_x, angle_y;
    getRawGyrXYZ(gx, gy, gz);
    getAccXYAngle(angle_x, angle_y);
    //complemenrty + lowpass filter
    /*angle_x_past_ = (angle_x_past_ + ((angle_x_past_ + gx * dt) * ratio_gyro_ + (angle_x) * ratio_acc_)) / 2;
    ax = angle_x_past_;
    angle_y_past_ = (angle_y_past_ + ((angle_y_past_ + gy * dt) * ratio_gyro_ + (angle_y) * ratio_acc_)) / 2;
    ay = angle_y_past_;*/
    //complementry filter
    angle_x_past_ = ((angle_x_past_ + gx * dt) * ratio_gyro_ + (angle_x) * ratio_acc_);
    ax = angle_x_past_;
    angle_y_past_ = ((angle_y_past_ + gy * dt) * ratio_gyro_ + (angle_y) * ratio_acc_);
    ay = angle_y_past_;
}
/// @brief This will retreve the current angle and the rate of change for the x and y axis
/// @param ax Angle on the x axis
/// @param ay Angle on the y axis
/// @param gx Rate of change for the x axis
/// @param gy Rate of change for the y axis
void BNO055::getXYAngle(double &ax, double &ay, double &gx, double &gy){
    double dt = (double)(millis() - ms_old_) / 1000.;
    ms_old_ = millis();
    double gz, angle_x, angle_y;
    getRawGyrXYZ(gx, gy, gz);
    getAccXYAngle(angle_x, angle_y);
    //complemenrty + lowpass filter
    /*angle_x_past_ = (angle_x_past_ + ((angle_x_past_ + gx * dt) * ratio_gyro_ + (angle_x) * ratio_acc_)) / 2;
    ax = angle_x_past_;
    angle_y_past_ = (angle_y_past_ + ((angle_y_past_ + gy * dt) * ratio_gyro_ + (angle_y) * ratio_acc_)) / 2;
    ay = angle_y_past_;*/
    //complementry filter
    angle_x_past_ = ((angle_x_past_ + gx * dt) * ratio_gyro_ + (angle_x) * ratio_acc_);
    ax = angle_x_past_;
    angle_y_past_ = ((angle_y_past_ + gy * dt) * ratio_gyro_ + (angle_y) * ratio_acc_);
    ay = angle_y_past_;
    
    gx = 2*gx * dt;
    gy = 2*gy * dt;

    //Serial.print((String)(angle_x_past_ + gx * dt) + ",");
    //Serial.print((String)angle_x + ",");
    //Serial.print((String)gx + ",");
}