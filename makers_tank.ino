// imports
#include "PwmMotor.h"

// const
byte PWM_RIGHT_H = 1;  // channel 1
byte PWM_RIGHT_V = 2;  // channel 2
byte PWM_LEFT_V = 3;  // channel 3
byte PWM_LEFT_H = 4;  // channel 4
int LEFT_TRACK = 5;  // pin 5
int RIGHT_TRACK = 6; // pin 6
int MOTOR_HIGH = 255;
int MOTOR_LOW = 0;
int MOTOR_MID = 128;
int NUMBER_OF_CHANNELS = 4;
int THRESHOLD = 50;
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
PwmMotor signal_reader(true, MOTOR_MID, THRESHOLD);
bool debug = true;
// FUNCTION DEFINITIONS
void move_track(int track_values[2]) {
  /*
   * Control 2 tracks by values in array given
   * @param track_values      int[2]    values for the 2 tracks (ms) from pwm
   * @return none
   */
}
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
  int vertical_motor = signal_reader.translate_pwm_motor(pwm_values[2], value_range[2], true);  // channel 3
  int horizontal = signal_reader.translate_pwm_motor(pwm_values[3], value_range[3], false);  // channel 4
}
