#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "Arduino.h"
#include <configuration.h>
#include <RS485_driver.h>
#include <Timer_driver.h>

struct SEND_S
{
    uint16_t feedpos   : 9;
    uint8_t feedready : 1;
    uint8_t feedvalid : 1;
    uint8_t debug     : 8;
};

struct RECEIVE_S
{   
    //       L                                                                       M
    //       S                                                                       S
    //       B                                                                       B
    // Data: A,A,A,H ,R,G,B,E - G,G,G,G ,G,G,G,D - D,D,D,D ,D,D,D,D - F,F,F,F ,F,F,F,F
	
    // first Byte
	uint8_t adress      : 3;    //LSB
    uint8_t homing      : 1;
	uint8_t red         : 1;
	uint8_t green       : 1;
	uint8_t blue        : 1;
	uint8_t endis       : 1;    
	// Second Byte
	uint8_t gripper     : 7;
    uint8_t firstbit    : 1;
    // Third byte
    uint8_t position    : 8;    //8 + 
	// Fourth Byte
    uint8_t fan         : 8;
    // Fifth Byte
    uint8_t checksum    : 8;    //MSB
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
    uint8_t fifthByte;
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


//Class

class ComClass {   
  private:
    uint8_t _byteCounter = 0;
    RS485Class rs485 = RS485Class(19200);
  public:
    RECEIVE_U _receive;
    SEND_U _send;
    uint8_t buffer[10];
    bool _newDataIn = 0;
    bool _sendData = 0;
    ComClass();
    RECEIVE_U Read(void);
    void Write(SEND_U send);
    void processData(void);
    bool decodeChecksum(void);
};

#endif