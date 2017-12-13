#include "Arduino.h"
#include "PwmMotor.h"
// functions
PwmMotor::PwmMotor(bool debug_option, int neutral, int error_margin) {
  _debug = debug_option;
  _motor_neutral = neutral;
  _error_margin = error_margin;
}

int PwmMotor::read_pwm_channel(byte pwm_pin) {
  /*
   * Take in a byte pin number and return the pwm value read from that pin
   * Taken from http://www.benripley.com/diy/arduino/three-ways-to-read-a-pwm-signal-with-arduino/
   * @param pwn_pin   byte    the pin number to read pwm from
   * @return          int     the value of pwn from that pin
   */
  // set pin to input
  pinMode(pwm_pin, INPUT);
  // read the value
  // this can take up to 20ms, timeout in 1s
  int value_read = pulseIn(pwm_pin, HIGH);
  if (_debug) {
    // print the value for debug purposes
    Serial.println("pwm read on pin ");
    Serial.print(pwm_pin);
    Serial.print(" : ");
    Serial.println(value_read);
  }
  return value_read;
}

float PwmMotor::translate_pwm_motor(int pwm_reading, int value_range[3], bool reverse) {
  /*
   * Translate a pwm reading into pwm value to control the motor.
   * Value can be from 0 - 255
   *
   * @param pwm_reading       int       pwm value reading
   * @param value_range       int[2]    minimum and maximum pwm value
   * @param reverse           int       whether or not the values should be reversed
   * @return                  float     value for motor (0 - 255)
   */
  float motor_value = 0;
  float relative_value = pwm_reading;
  float range = value_range[2] - value_range[0];
  float percentage = 0.0;
  int upper_margin = value_range[1] + _error_margin;
  int lower_margin = value_range[1] - _error_margin;
  // if it's the middle value don't move at all
  if (relative_value <= upper_margin && relative_value >= lower_margin) {
    return _motor_neutral;
  }
  // see if it's positive or negative
  if (reverse) {
    int difference = relative_value - value_range[1];
    // |---o--|------|
    if (difference > 0) {
      // move backward not forward
      relative_value = value_range[1] - abs(difference);
    } else if (difference < 0) {
      // move forward
      relative_value = value_range[1] + abs(difference);
    }
  }
  percentage = abs((relative_value - value_range[0]) / range);
  // translate it into 0 - 255
  motor_value = 255 * percentage;

  if (_debug) {
    Serial.println("MOTOR VALUE FOR CHANNEL ");
    Serial.print(" : ");
    Serial.println(motor_value);
  }
  return motor_value;
}