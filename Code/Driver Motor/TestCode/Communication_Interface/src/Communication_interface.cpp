#include "Communication_interface.h"

ComClass::ComClass()
{
}


RECEIVE_U ComClass::Read(){
    // Clear the structure
    _receive.receiveBytes.firstByte = 0;
    _receive.receiveBytes.secondByte = 0;
    _receive.receiveBytes.thirdByte = 0;
    _receive.receiveBytes.fourthByte = 0;
    _receive.receiveBytes.fifthByte = 0;
    // Fill the structure w/ the new data
    _receive.receiveBytes.firstByte = rs485.Read();
    _receive.receiveBytes.secondByte = rs485.Read();
    _receive.receiveBytes.thirdByte = rs485.Read();
    _receive.receiveBytes.fourthByte = rs485.Read();
    _receive.receiveBytes.fifthByte = rs485.Read();
    return _receive;
}

void ComClass::Write(SEND_U send){
    rs485.Write(send.sendBytes.firstByte);
    rs485.Write(send.sendBytes.secondByte);
    rs485.Write(send.sendBytes.thirdByte);    
}

uint8_t ComClass::dataReceived()
{
    if(rs485.data_available())
    {
    
    }
    return 0;
}

void ComClass::checkData(void)
{
    if(rs485.data_available() >= 5)
    {
        Read();
        if(decodeChecksum())
            digitalWrite(LEDB,!digitalRead(LEDB));  // Debug
    }
}

bool ComClass::decodeChecksum()
{
    unsigned char total =   _receive.receiveBytes.firstByte +
                            _receive.receiveBytes.secondByte +
                            _receive.receiveBytes.thirdByte +
                            _receive.receiveBytes.fourthByte;
    if(_receive.receiveBytes.fifthByte == total)
        return 1;
    else
        return 0;
}