// imports
#include "PwmMotor.h"
#include "Settings.h"
#include <Servo.h>
#include "I2C.h"

// vars
Settings settings = c1_configs;  // see Settings.cpp
int pwm_values[4] = {0, 0, 0, 0};
int modfied_motor_high = settings.MOTOR_HIGH * settings.MOTOR_MODIFIER;
int modfied_motor_low = settings.MOTOR_LOW / settings.MOTOR_MODIFIER;
int bounce_count = 0;
int pins[4] = {settings.PWM_RIGHT_H,
               settings.PWM_RIGHT_V,
               settings.PWM_LEFT_V,
               settings.PWM_LEFT_H};

PwmMotor pwm_manager(settings.DEBUG,
                     modfied_motor_low,
                     settings.MOTOR_MID,
                     modfied_motor_high,
                     settings.THRESHOLD,
                     settings.DEBOUNCE_RATE);
I2C i2c(settings.DEBUG, settings.I2C_ARDUINO);
Servo left_track;
Servo right_track;
// MAIN LOOPS
void setup() {
  // put your setup code here, to run once:
  if (settings.DEBUG) {
    Serial.begin(115200);
  }
  i2c.connect();
  // attach motors to pin
  left_track.attach(settings.LEFT_TRACK);
  right_track.attach(settings.RIGHT_TRACK);
}

void loop() {
  // put your main code here, to run repeatedly:
  // check input priority, analog controller has priority over all
  int vertical = 0;
  int horizontal = 0;
  int signal_value = pwm_manager.read_pwm_channel(settings.ANALOG_SIGNAL_PIN);
  if (signal_value > settings.VALUE_RANGE[4][1]) {
    // read pwm values and plug it into the array
    int c_count;
    for (c_count=0; c_count < settings.NUMBER_OF_CHANNELS; c_count++) {
      pwm_values[c_count] = pwm_manager.read_pwm_channel(pins[c_count]);
    }
    vertical = pwm_manager.translate_pwm_motor(pwm_values[2],
                                               settings.VALUE_RANGE[2]);
    horizontal = pwm_manager.translate_pwm_motor(pwm_values[3],
                                                 settings.VALUE_RANGE[3]);
    bounce_count = bounce_count + 1;
    Serial.println(bounce_count);
    if (bounce_count == settings.DEBOUNCE_RATE) {
      // debouncer
      bounce_count = 0;
      pwm_manager.move_tracks(vertical, horizontal,
                              left_track, right_track);
    }
  } else{
    // use raspberry pi to control
  }
  String movement = horizontal + " " + vertical;
  i2c.sendData(settings.I2C_RASPBERRY_PI, "motor control", movement);
}
