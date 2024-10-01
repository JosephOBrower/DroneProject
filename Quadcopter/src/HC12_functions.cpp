#include "HC12.h"

hc12::hc12(int tx, int rx, int set) : SoftwareSerial(tx, rx){
    tx_ = tx;
    rx_ = rx;
    set_ = set;
    SoftwareSerial(tx, rx);//call the SoftwareSerial constructor
    SoftwareSerial::begin(9600);
    pinMode(set_, OUTPUT);
    digitalWrite(set_, HIGH);
    changeSettingStatus(0);
    return;
}
void hc12::changeSettings(){
    digitalWrite(set_, LOW);
    delay(200);
    changeSettingStatus(1);
    return;
}
void hc12::exitSettings(){
    delay(200);
    digitalWrite(set_, HIGH);
    changeSettingStatus(0);
    return;
}
void hc12::changeBaud(String num){//change the baud (transmition rate)
    changeSettings();
    SoftwareSerial::print("AT+B" + num);
    delay(200);
    printHC12Data();
    exitSettings();
    return;
}
void hc12::changeTPowerConsumption(String num){//change the transmittion power level (range)
    changeSettings();
    SoftwareSerial::print("AT+P" + num);
    delay(200);
    printHC12Data();
    exitSettings();
    return;
}
void hc12::changeChannel(String num){//num is 001-127
    changeSettings();
    SoftwareSerial::print("AT+C" + num);
    delay(200);
    printHC12Data();
    exitSettings();
    return;
}
void hc12::changeDefault(){//sets HC12 to default parameters
    changeSettings();
    SoftwareSerial::print("AT+DEFAULT");
    delay(200);
    printHC12Data();
    exitSettings();
    return;
}
void hc12::testHC12(){
    changeSettings();
    print("AT");//send this command
    delay(250);
    printHC12Data();
    exitSettings();
    return;
}
void hc12::begin(){
  //Serial.print("Testing HC12...\n\tHC12 says: ");
  testHC12();
  //Serial.print("\t");
  changeDefault();
  //Serial.print("\tChannel: ");
  changeChannel("005");
  //Serial.print("\tPower-level: ");
  changeTPowerConsumption("1");
}
void hc12::printHC12Data(){
    while (available()) { // If HC-12 has data
        Serial.write(read()); //read and write to the serial monitor
    }
    return;
}
void hc12::transmitByte(byte val){
    write(val);
}
void hc12::transmiteChar(char val){
    write(val);
}
