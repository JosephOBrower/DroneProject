#include <Arduino.h>

/**must Send a value between 0-99, and a address
 * JBytes can only have 4 different addresses
 * there will be a loss of data!
 * there will only be 60 ticks
*/
class JByte{
public:
    //compresses the num(0-99) and address(0-3) to a byte
    byte convertJByte(int num, int address);
    //returns the approximate int(0-99) and returns the address(0-3) through pass by reference
    int readJByte(byte b, int& address);

    void printByte(byte b);
};