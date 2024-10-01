#include "JByte.h"

void JByte::printByte(byte b){
    Serial.print("\tJB");
    for (int i = 7; i >= 0; i--)
    {
        bool p = bitRead(b, i);
        Serial.print(p);
    }
}
byte JByte::convertJByte(int num, int address){
    byte temp = B00000000;
    num = ((63000/99) * num)/1000;//converts from range 0-99 to range 0-63
    //Serial.print("num: " + String(num));
    temp = byte(address) | temp;
        //Serial.print("Temp1:");
        //printByte(temp);
    temp = temp << 6;//shift bits 6 positions to the left
        //Serial.print("\tTemp2:");
        //printByte(temp);
    temp = byte(num) | temp;
    return temp;
}
int JByte::readJByte(byte b, int& address){
    //printByte(b);
    //Serial.println();
    address = int(b >> 6);
    return (b & B00111111);
}