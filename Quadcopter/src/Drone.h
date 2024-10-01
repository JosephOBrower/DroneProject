
/*This will combine all the classes; BNO055, JByte, Motor, and HC12*/
#include "Motor.h"
#include "BNO055.h"
#include "JByte.h"
#include "HC12.h"

class Drone {
private:
//objects
    BNO055 my_imu;
    JByte jb;
    hc12 hc;
    Motor m1, m2, m3, m4;
//variables
double prev_errorX = 0, prev_errorY = 0;
double P = 0.1;//as P increases, power per angle increases 0.1
double D = 8;//as D increases, slowing down force decreases 8
double target_angleX_ = 0, target_angleY_ = 0;
double elapsed_time_ = millis(), prev_elapsed_time_ = 0;
//arrays
int channel[4] = {0,0,0,0};
//methods
void channel1();//throttle
void channel2();//left/right pich
void channel3();//x pan left/right
void channel4();//y pan forword/backword
void setESCMotorRange();//This will set the throttle range on the ESC -- call once!
public:
const int lower_motor_range_ = 130;
const int upper_motor_range_ = 240;
/*m1-m4 is the motor pins, tx/rx and set are the pins for the HC12
This also calls the constructors for all the classes*/
Drone(int m1_pin, int m2_pin, int m3_pin, int m4_pin, int tx, int rx, int set) :
 m1(m1_pin), m2(m2_pin), m3(m3_pin), m4(m4_pin), my_imu(), jb(), hc(tx, rx, set) {}
/*This will 'set up' everything. Only call this once.*/
void setUP();
/*For debuging*/
void serialDebug();
/*This will receive the latest remotecontroler instructions and store it in channel array.
If the HC12 does not receve instruction, in a given time, it will set all the channels to 0.*/
void getHC12Instruction();
/*This will adjust the motor values to balance the drone and follow the users instructions*/
void applyMotorValues();
/*This will output the set motor speeds to the motor*/
void runMotors();
/*This will adjust the motor power levels to stay balanced*/
void adjustMotorValuesToBalance();

};