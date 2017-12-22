// imports
#include "PwmMotor.h"

// const
byte PWM_RIGHT_H = 3;  // channel 1
byte PWM_RIGHT_V = 5;  // channel 2
byte PWM_LEFT_V = 6;  // channel 3
byte PWM_LEFT_H = 9;  // channel 4
int LEFT_TRACK = 10;
int RIGHT_TRACK = 11;
int MOTOR_HIGH = 255;
int MOTOR_LOW = 0;
int MOTOR_MID = 128;
int NUMBER_OF_CHANNELS = 4;
int THRESHOLD = 100;
// options
float MOTOR_MODIFIER = 1.0;  // modify power of motor
// vars
int pins[4] = {PWM_RIGHT_H,
               PWM_RIGHT_V,
               PWM_LEFT_V,
               PWM_LEFT_H};
int pwm_values[4] = {0, 0, 0, 0};
int value_range[4][3] = {  // min, mid, max
  {},
  {},
  {1128, 1500, 1885},  // high is down, low is up
  {1060, 1450, 1795},  // high is right, low is left
};
PwmMotor signal_reader(true, MOTOR_LOW, MOTOR_MID, MOTOR_HIGH, THRESHOLD);
bool debug = true;
// MAIN LOOPS
void setup() {
  // put your setup code here, to run once:
  if (debug) {
    Serial.begin(115200);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // read pwm values and plug it into the array
  int c_count;
  for (c_count=0; c_count < NUMBER_OF_CHANNELS; c_count++) {
    pwm_values[c_count] = signal_reader.read_pwm_channel(pins[c_count]);
  }
  int vertical = signal_reader.translate_pwm_motor(pwm_values[2],
                                                   value_range[2],
                                                   false);
  int horizontal = signal_reader.translate_pwm_motor(pwm_values[3],
                                                     value_range[3],
                                                     false);
  signal_reader.move_tracks(vertical, horizontal, LEFT_TRACK, RIGHT_TRACK);
}
