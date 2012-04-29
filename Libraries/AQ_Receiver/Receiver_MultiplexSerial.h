/*
  AeroQuad v3.0.1 - February 2012
  www.AeroQuad.com
  Copyright (c) 2012 Ted Carancho.  All rights reserved.
  An Open Source Arduino based multicopter.
  
  Multiplex Receiver Serial 
  Copyright (c) 2012 Mattias Welponer <mattias@welponer.net>.  All rights reserved.
 
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

#ifndef _AEROQUAD_RECEIVER_MULTIPLEX_SERIAL_H_
#define _AEROQUAD_RECEIVER_MULTIPLEX_SERIAL_H_

#include "Receiver.h"

#ifndef RECEIVER_MULTIPLEX_SERIAL
  #error RECEIVER_MULTIPLEX_SERIAL NOT DEFINED
  //#define RECEIVER_MULTIPLEX_SERIAL Serial1
#endif

#define RECEIVER_MULTIPLEX_SERIAL Serial1

unsigned short inByte;        
unsigned short count;             
unsigned short checksum;
char data[24];  
bool checksumOK;
unsigned short crc_ccitt;
static unsigned short   crc16_ccitt_tab[256];
static bool              crc16_ccitt_tab_init       = false;
static void             init_crcccitt_tab( void );
unsigned short update_crc_ccitt( unsigned short crc, char c );


#define                 CRC16_CCITT_POLY     0x1021



void initializeReceiver(int nbChannel) {
  initializeReceiverParam(nbChannel);
  init_crcccitt_tab();
  RECEIVER_MULTIPLEX_SERIAL.begin(115200);
  checksumOK = false;
}

int getRawChannelValue(byte channel) {
 if (checksumOK) {
    //SerialUSB.println(((data[channel] << 8) + data[channel+1]), HEX);
    receiverCommand[channel] = ((data[channel*2] << 8) + data[channel*2+1]);           
  }
  return receiverCommand[channel];
}
  
void setChannelValue(byte channel,int value) {
  receiverCommand[channel] = value;
}

void readSerialReceiver(void) {
  if (RECEIVER_MULTIPLEX_SERIAL.available()) {        
    inByte = RECEIVER_MULTIPLEX_SERIAL.read();

    if ((inByte == 0xA1) && (count >= 24+2)) {
      count = 0;
      crc_ccitt = update_crc_ccitt(0x0000, 0xA1);   // start byte also part of the CRC 
    } else if (count <= 23) {
        data[count] = inByte;
        crc_ccitt = update_crc_ccitt(crc_ccitt, inByte);
        count++;
    } else if (count == 24) {
        checksum = inByte; 
        count++;
    } else if (count == 25) {
        checksum = ((checksum << 8) + inByte);  
        if (checksum == crc_ccitt) checksumOK = true; else checksumOK = false;
        count++;
    }
  }    
}



/*

void printHex(int num, int precision) {
	char tmp[16];
	char format[128];
	sprintf(format, "0x%%.%dX", precision);
	sprintf(tmp, format, num);
	SerialUSB.print(tmp);
}
*/

unsigned short update_crc_ccitt( unsigned short crc, char c ) {
  unsigned short tmp, short_c;
  short_c  = 0x00ff & (unsigned short) c;
  if ( !crc16_ccitt_tab_init ) 
    init_crcccitt_tab();
  tmp = (crc >> 8) ^ short_c;
  crc = (crc << 8) ^ crc16_ccitt_tab[tmp];
  return crc;
} 

static void init_crcccitt_tab( void ) {
  int i, j;
  unsigned short crc, c;
  for (i=0; i<256; i++) {
    crc = 0;
    c   = ((unsigned short) i) << 8;
    for (j=0; j<8; j++) {
      if ( (crc ^ c) & 0x8000 ) crc = ( crc << 1 ) ^ CRC16_CCITT_POLY;
      else  crc =   crc << 1;
      c = c << 1;
    }
    crc16_ccitt_tab[i] = crc;
  }
  crc16_ccitt_tab_init = true;
} 





#endif



