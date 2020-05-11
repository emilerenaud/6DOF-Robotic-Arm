#ifndef COM_PROCESS_H
#define COM_PROCESS_H

#include <Communication_interface.h>
#include <configuration.h>

class ComProcess
{

private:
    

public:
ComClass _com = ComClass();
	bool _readyForNewData = 1;
	bool _sendFinish = 0;
	uint8_t _adress;
    uint8_t _homing;
	uint8_t _red;
	uint8_t _green;
	uint8_t _blue;
	uint8_t _endis;    
	uint8_t _gripper;
    uint16_t _position;
    uint8_t _fan;
    
    ComProcess();
    void DecodeData();
};
#endif