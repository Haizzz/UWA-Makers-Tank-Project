#include "Arduino.h"
#include "Wire.h"
#include "I2C.h"
// vars
int _id;
bool _i2cDebug;
// functions
void debug(String msg) {
  if (_i2cDebug) {
    String line = "[I2C]" + msg;
    Serial.println(line);
  }
}

I2C::I2C(bool debugMode, int id) {
  _i2cDebug = debugMode;
  _id = id;
}

void handleReceive(int byteCount) {
  debug(String("receiving: " + String(byteCount + "bytes")));
  String msg;
  while (Wire.available()) {
    char character = Wire.read();
    msg = String(msg + character);
  }
  debug(String("received: " + msg));
}

void I2C::connect() {
  debug("I2C: establishing connection");
  Wire.begin(_id);
  Wire.onReceive(handleReceive);
  debug(String("Joined I2C bus with id: " + _id));
}

void I2C::sendData(int destination, String header, String msg) {
  debug(String("sending: " + msg));
  char _header[header.length()];
  char _msg[msg.length()];
  header.toCharArray(_header, header.length());
  msg.toCharArray(_msg, msg.length());
  Wire.beginTransmission(destination);
  Wire.write(_header);
  Wire.write(":");
  Wire.write(_msg);
  Wire.endTransmission();
  debug("sent");
}