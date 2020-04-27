#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "Arduino.h"
#include <configuration.h>
#include <RS485_driver.h>


struct SEND_S
{
    uint16_t feedpos   : 9;
    uint8_t feedready : 1;
    uint8_t feedvalid : 1;
    uint8_t debug     : 8;
};

struct RECEIVE_S
{
	// Data: A,A,A,H ,R,G,B,E - G,G,G,G ,G,G,G,D - D,D,D,D ,D,D,D,D - F,F,F,F ,F,F,F,F
	// first Byte
	uint8_t adress    : 3;
    uint8_t homing    : 1;
	uint8_t rgbmode   : 3;
	uint8_t endis     : 1;
	// Second Byte
	uint8_t gripper   : 7;
    // Third byte
    uint16_t direction : 9;
	// Fourth Byte
    uint8_t fan       : 8;
    
};

struct SENDBYTES_S
{
    uint8_t firstByte;
    uint8_t secondByte;
    uint8_t thirdByte;
};

struct RECEIVEBYTES_S
{
    uint8_t firstByte;
    uint8_t secondByte;
    uint8_t thirdByte;
    uint8_t fourthByte;
};


union SEND_U
{
    SEND_S bits;
    SENDBYTES_S sendBytes;
};

union RECEIVE_U
{
    RECEIVE_S bits;
    RECEIVEBYTES_S  receiveBytes;
};


class ComClass {   
  private:
    RS485Class rs485 = RS485Class(19200);
  public:
    ComClass();
    RECEIVE_U Read();
    void Write(SEND_U send);



};

#endif