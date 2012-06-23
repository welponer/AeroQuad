/*
  AeroQuad v3.0.1 - February 2012
  www.AeroQuad.com
  Copyright (c) 2012 Ted Carancho.  All rights reserved.
  An Open Source Arduino based multicopter.
 
  This program is free software: you can redistribute it and/or modify 
  it under the terms of the GNU General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or 
  (at your option) any later version. 

  This program is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
  GNU General Public License for more details. 

  You should have received a copy of the GNU General Public License 
  along with this program. If not, see <http://www.gnu.org/licenses/>. 
*/

// I2C functions
#include "Device_I2C.h"

void sendByteI2C(int deviceAddress, byte dataValue) {

  Wire.beginTransmission(deviceAddress);
#if defined(ARDUINO) && ARDUINO >= 100
  Wire.write(dataValue);
#else
  Wire.send(dataValue);
#endif
  Wire.endTransmission();
}

byte readByteI2C() {
#if defined(ARDUINO) && ARDUINO >= 100
  return Wire.read();
#else
  return Wire.receive();
#endif
}

byte readByteI2C(int deviceAddress) {

  Wire.requestFrom(deviceAddress, 1);
#if defined(ARDUINO) && ARDUINO >= 100
        return Wire.read();
#else
        return Wire.receive();
#endif
}

int readWordI2C(int deviceAddress) {

  Wire.requestFrom(deviceAddress, 2);
#if defined(ARDUINO) && ARDUINO >= 100
    return (Wire.read() << 8) | Wire.read();
#else
    return (Wire.receive() << 8) | Wire.receive();
#endif
}

int readWordI2C() {

#if defined(ARDUINO) && ARDUINO >= 100
    return (Wire.read() << 8) | Wire.read();
#else
    return (Wire.receive() << 8) | Wire.receive();
#endif
}

int readShortI2C(int deviceAddress) {

 Wire.requestFrom(deviceAddress, 2);
 return readShortI2C();
}

int readShortI2C() {

  return (signed short)readWordI2C();
}

int readReverseShortI2C() {
#if defined(ARDUINO) && ARDUINO >= 100
  return (signed short)( Wire.read() | (Wire.read() << 8));
#else
  return (signed short)( Wire.receive() | (Wire.receive() << 8));
#endif
}

/*
int readWordWaitI2C(int deviceAddress) {

  Wire.requestFrom(deviceAddress, 2); // request two bytes
  while(!Wire.available()); // wait until data available
  unsigned char msb = Wire.read();
  while(!Wire.available()); // wait until data available
  unsigned char lsb = Wire.read();
  return (((int)msb<<8) | ((int)lsb));
}
*/

int readReverseWordI2C(int deviceAddress) {

  Wire.requestFrom(deviceAddress, 2);
#if defined(ARDUINO) && ARDUINO >= 100
  byte lowerByte = Wire.read();
  return (Wire.read() << 8) | lowerByte;
#else
  byte lowerByte = Wire.receive();
  return (Wire.receive() << 8) | lowerByte;
#endif
  
}

byte readWhoI2C(int deviceAddress) {

  // read the ID of the I2C device
  Wire.beginTransmission(deviceAddress);
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write((byte)0);
    Wire.endTransmission();
    delay(100);
    Wire.requestFrom(deviceAddress, 1);
    return Wire.read();
#else
    Wire.send((byte)0);
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(deviceAddress, 1);
  return Wire.receive();
#endif
}

void updateRegisterI2C(int deviceAddress, byte dataAddress, byte dataValue) {

    Wire.beginTransmission(deviceAddress);
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write(dataAddress);
    Wire.write(dataValue);
#else
    Wire.send(dataAddress);
    Wire.send(dataValue);
#endif
  Wire.endTransmission();
}  



