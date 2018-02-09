/*
Read and translate pwm signals to motor values
*/
#ifndef PwmMotor_h
#define PwmMotor_h

#include "Arduino.h"
class PwmMotor {
    public:
        PwmMotor(bool debug_option, int low, int neutral, int high, int error_margin, int dr);
        int read_pwm_channel(byte pwm_pin);
        int translate_pwm_motor(int pwm_reading, int value_range[4]);
        void move_tracks(float base, float turn, int left_pin, int right_pin);
};

#endif