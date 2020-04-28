#include "Communication_interface.h"

ComClass::ComClass(){
}


RECEIVE_U ComClass::Read(){
    // Clear the structure
    _receive.receiveBytes.firstByte = 0;
    _receive.receiveBytes.secondByte = 0;
    _receive.receiveBytes.thirdByte = 0;
    _receive.receiveBytes.fourthByte = 0;
    // Fill the structure w/ the new data
    _receive.receiveBytes.firstByte = rs485.Read();
    _receive.receiveBytes.secondByte = rs485.Read();
    _receive.receiveBytes.thirdByte = rs485.Read();
    _receive.receiveBytes.fourthByte = rs485.Read();
    return _receive;
}

void ComClass::Write(SEND_U send){
    rs485.Write(send.sendBytes.firstByte);
    rs485.Write(send.sendBytes.secondByte);
    rs485.Write(send.sendBytes.thirdByte);    
}

uint8_t ComClass::dataReceived()
{
    return rs485.data_available();
}