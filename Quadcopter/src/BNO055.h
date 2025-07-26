#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include "utility/imumaths.h"

//Pins A4 and A5 are dedicated I2C pins. Where A4 is the SDA and A5 is the SCL pin.

class BNO055 : public Adafruit_BNO055 {
public:
    
    BNO055(){};//constructor
    ~BNO055(){};
    void begin();
    void getRawAccXYZ(double &x, double &y, double &z);
    void getRawGyrXYZ(double &x, double &y, double &z);
    void getAccXYAngle(double &ax, double &ay);
    void getXYAngle(double &ax, double &ay);
    void getXYAngle(double &ax, double &ay, double &gx, double &gy);
    //class variables

private:
    Adafruit_BNO055 imu_;
    unsigned long ms_old_;
    double angle_x_past_;
    double angle_y_past_;
    const double ratio_gyro_ = 0.99;
    const double ratio_acc_ = 1 - ratio_gyro_;
};
