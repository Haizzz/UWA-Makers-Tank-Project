#include "Wire.h"
#include "Arduino.h"
#include "I2C.h"
// vars
bool _debug;
int _id;
// functions
void debug(int msg) {
  if (_debug) {
    Serial.println(msg);
  }
}

I2C::Connection(bool debugMode, int id) {
  _debug = debugMode;
  _id = id;
  _onReq = onReq;
  _res = res;
  debug("I2C: establishing connection");
  Wire.begin(_id);
  debug("Joined I2C bus with id: ", _id);
}