/*
Connection between arduino and raspberry pi through i2c
*/
#ifndef I2C_h
#define I2C_h

#include "Arduino.h"
#include "Wire.h"
class I2C {
    public:
        I2C(bool debugMode, int id);
        void connect();
        void sendData(int destination, String header, String msg);
};

#endif