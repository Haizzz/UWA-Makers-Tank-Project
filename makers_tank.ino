// imports
#include "PwmMotor.h"
#include "Settings.h"

// vars
Settings settings = c1_configs;  // see Settings.cpp
int pwm_values[4] = {0, 0, 0, 0};
int modfied_motor_high = settings.MOTOR_HIGH * settings.MOTOR_MODIFIER;
int modfied_motor_low = settings.MOTOR_LOW / settings.MOTOR_MODIFIER;
int pins[4] = {settings.PWM_RIGHT_H,
               settings.PWM_RIGHT_V,
               settings.PWM_LEFT_V,
               settings.PWM_LEFT_H};
PwmMotor pwm_manager(settings.DEBUG,
                     modfied_motor_low,
                     settings.MOTOR_MID,
                     modfied_motor_high,
                     settings.THRESHOLD);
// MAIN LOOPS
void setup() {
  // put your setup code here, to run once:
  if (settings.DEBUG) {
    Serial.begin(115200);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // read pwm values and plug it into the array
  int c_count;
  for (c_count=0; c_count < settings.NUMBER_OF_CHANNELS; c_count++) {
    pwm_values[c_count] = pwm_manager.read_pwm_channel(pins[c_count]);
  }
  int vertical = pwm_manager.translate_pwm_motor(pwm_values[2],
                                                 settings.VALUE_RANGE[2]);
  int horizontal = pwm_manager.translate_pwm_motor(pwm_values[3],
                                                   settings.VALUE_RANGE[3]);
  pwm_manager.move_tracks(vertical, horizontal,
                          settings.LEFT_TRACK, settings.RIGHT_TRACK);
}
