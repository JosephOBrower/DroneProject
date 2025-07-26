/**
 *Putting the HC12 into changing settings mode (AT commands) requires that 
    the set pin is connected to ground. Here are some AT commands:
        "AT"    HC12 will return 'OK' indicating that it is in the settings mode
        "AT+Bxxxx"  Changes the baud rate. Increasing the baud rate decreases
            transmission time, but lowers the distance that it can transmit
        "AT+Cxxx" Changes the channel. 
        "AT+Px" Changes the transmission power. The higher the power the longer the
            distance.
        ""*/

#include <Arduino.h>
#include <SoftwareSerial.h>

class hc12 : public SoftwareSerial/**, public Stream, public Print**/{
public:
//constructors
hc12(int tx, int rx, int set);//TX-pin, RX-pin, set-pin
//settters
void setTimeOfLastInstruction(unsigned long int i){timeOfLastInstruction_ = i;}
/*void setTX(int num){tx_ = num;};
void setRX(int num){rx_ = num;};
void setSet(int num){set_ = num;};*/
//getters
unsigned long int getTimeOfLastInstruction(){return timeOfLastInstruction_;}
//other
void transmit(/*DATA*/);
void changeSettings();
void exitSettings();
void changeChannel(String num);//num 001-100
void changeBaud(String num);//Available baud rates: 1200 bps, 2400 bps, 4800 bps, 9600 bps, 19200 bps, 38400 bps, 57600 bps, and 115200 bps. Default: 9600 bps.
void changeTPowerConsumption(String num);//power of 1-8
void changeDefault();//resets hc12 to default parameters
void testHC12();//if prints "OK" everything is connected and working
void begin();
void printHC12Data();
void transmitByte(byte val);
void transmiteChar(char val);
private:
//setters
void changeSettingStatus(bool status){changeSettings_ = status;};
//getters
bool settingStatus(){return changeSettings_;};
//variables
int tx_;
int rx_;
int set_;
bool changeSettings_;//will be a 1 if you are changing the settings
unsigned long int timeOfLastInstruction_;
};
