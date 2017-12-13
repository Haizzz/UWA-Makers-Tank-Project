/*
Read and translate pwm signals to motor values
*/
#ifndef PwmMotor_h
#define PwmMotor_h

#include "Arduino.h"
class PwmMotor {
    public:
        PwmMotor(bool debug_option, int neutral, int error_margin);
        int read_pwm_channel(byte pwm_pin);
        float translate_pwm_motor(int pwm_reading, int value_range[3], bool reverse);
    private:
        bool _debug;
        int _motor_neutral;
        int _error_margin;
};

#endif