/*
Settings struct
*/
#ifndef Settings_h
#define Settings_h

#include "Arduino.h"
struct Settings {
    int PWM_RIGHT_H;
    int PWM_RIGHT_V;
    int PWM_LEFT_V;
    int PWM_LEFT_H;
    int LEFT_TRACK;
    int RIGHT_TRACK;
    int MOTOR_HIGH;
    int MOTOR_LOW;
    int MOTOR_MID;
    int NUMBER_OF_CHANNELS;
    int THRESHOLD;
    float MOTOR_MODIFIER;
    int VALUE_RANGE[4][4];
    bool DEBUG;
};

extern Settings c1_configs;

#endif