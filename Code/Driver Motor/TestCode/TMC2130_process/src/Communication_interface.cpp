#include "Communication_interface.h"

ComClass::ComClass(){
}

RECEIVE_U ComClass::Read(){
    RECEIVE_U receive;
    receive.receiveBytes.firstByte = rs485.Read();
    receive.receiveBytes.secondByte = rs485.Read();
    receive.receiveBytes.thirdByte = rs485.Read();
    receive.receiveBytes.fourthByte = rs485.Read();
    return receive;
}

void ComClass::Write(SEND_U send){
    rs485.Write(send.sendBytes.firstByte);
    rs485.Write(send.sendBytes.secondByte);
    rs485.Write(send.sendBytes.thirdByte);    
}