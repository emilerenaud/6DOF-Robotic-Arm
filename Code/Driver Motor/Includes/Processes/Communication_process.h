#ifndef COM_PROCESS_H
#define COM_PROCESS_H

#include <Communication_interface.h>
#include <configuration.h>

class ComProcess
{

private:
    ComClass _com = ComClass();
public:
	bool _readyForNewData = 1;
	bool _sendFinish = 0;
	uint8_t _adress = 0;
    uint8_t _homing = 0;
	uint8_t _red = 1;
	uint8_t _green = 1;
	uint8_t _blue = 1;
	uint8_t _endis = 0;    
	uint8_t _gripper = 0;
    uint16_t _position = 0;
    uint8_t _fan = 0;
    
    ComProcess();
    void DecodeData();
};
#endif