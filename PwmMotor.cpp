#include "Arduino.h"
#include "PwmMotor.h"
// vars
bool _debug;
int _motor_low;
int _motor_neutral;
int _motor_high;
int _error_margin;
// functions
PwmMotor::PwmMotor(bool debug_option, int low, int neutral, int high, int error_margin) {
  _debug = debug_option;
  _motor_low = low;
  _motor_neutral = neutral;
  _motor_high = high;
  _error_margin = error_margin;
}

int PwmMotor::read_pwm_channel(byte pwm_pin) {
  /*
   * Take in a byte pin number and return the pwm value read from that pin
   * Taken from
   * http://www.benripley.com/diy/arduino/three-ways-to-read-a-pwm-signal-with-arduino/
   *
   * @param pwn_pin   byte    the pin number to read pwm from
   * @return          int     the value of pwn from that pin
   */
  // set pin to input
  pinMode(pwm_pin, INPUT);
  // read the value
  // this can take up to 20ms, timeout in 1s
  int value_read = pulseIn(pwm_pin, HIGH);
  if (false) {
    // print the value for debug purposes
    Serial.println("pwm read on pin ");
    Serial.print(pwm_pin);
    Serial.print(" : ");
    Serial.println(value_read);
  }
  return value_read;
}

int enforce_range(float value) {
  /*
   * Make sure that a value stay within the motor range, otherwise cast it to int.
   * This is only a helper function and therefore isn't listed in the header file
   *
   * @param value       float       the value to enforce the range on
   * @return            int
   */
  if (value < _motor_low) {
    value = _motor_low;
  } else if (value > _motor_high) {
    value = _motor_high;
  } else {
    // turn to int
    value = static_cast<int>(value);
  }

  return value;
}

int PwmMotor::translate_pwm_motor(int pwm_reading, int value_range[4]) {
  /*
   * Translate a pwm reading into pwm value to control the motor.
   * Value can be from 0 - 255
   *
   * @param pwm_reading       int       pwm value reading
   * @param value_range       int[4]    pwm pin calibrations
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
  if (value_range[3]) {
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
  // translate it to range
  motor_value = _motor_high * percentage;
  // make sure value is inside the range
  motor_value = enforce_range(motor_value);
  if (_debug) {
    Serial.println("MOTOR VALUE: ");
    Serial.println(motor_value);
  }
  return motor_value;
}

void PwmMotor::move_tracks(float base, float turn, int left_pin, int right_pin) {
  /*
   * Calculate the speed of 2 tracks and write them to pin
   *
   * @param base      float     the base speed value of 2 tracks
   * @param turn      float     the value of turn to adjust by
   * @param left_pin  int       pin number for the left track
   * @param right_pin int       pin number for the right track
   * @return          none
   */
  float left_track = base;
  float right_track = base;
  unsigned int difference = base - _motor_neutral;

  if (base > _motor_neutral){
    // moving forward
    if (turn > _motor_neutral) {
      right_track = right_track - difference;
    } else if (turn < _motor_neutral) {
      left_track = left_track - difference;
    }
  } else if (base < _motor_neutral) {
    // backwards, reverse logic
    if (turn > _motor_neutral) {
      right_track = right_track + difference;
    } else if (turn < _motor_neutral) {
      left_track = left_track + difference;
    }
  } else if ((base == 128.00) && (turn != 128.00)) {
    // spot turn
    if (turn > _motor_neutral) {
      left_track = _motor_neutral + difference;
    } else {
      right_track = _motor_neutral + difference;
    }
  }

  // enforce range
  left_track = enforce_range(left_track);
  right_track = enforce_range(right_track);
  if (_debug) {
    Serial.println("TRACK VALUES (L - R):");
    Serial.print(left_track);
    Serial.println(" - ");
    Serial.println(right_track);
  }
  // write to motor
  analogWrite(left_pin, left_track);
  analogWrite(right_pin, right_track);
}
