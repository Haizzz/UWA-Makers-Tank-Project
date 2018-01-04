/*
Connection between arduino and raspberry pi through i2c
*/
#ifndef I2C
#define I2C

#include "Wire.h"
#include "Arduino.h"
class I2C {
    public:
        Connection(bool debugMode, int id);
};

#endif