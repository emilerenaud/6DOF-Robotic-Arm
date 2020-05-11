#include "Communication_interface.h"

// Class
ComClass::ComClass()
{
}


RECEIVE_U ComClass::Read(){
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

void ComClass::processData(void)
{       
    if(rs485.data_available() >= 5)
    {
        Read();
        if(decodeChecksum())
        {
            _newDataIn = 1;
            //digitalToggle(LEDB);  // Debug
            delay(10);
            rs485.Write(0xAA); // ok feedback.
        }
    }
    if(_sendData == 1)
    {
        // Send data
    }
}

bool ComClass::decodeChecksum()
{
    unsigned char total =   _receive.receiveBytes.firstByte +
                            _receive.receiveBytes.secondByte +
                            _receive.receiveBytes.thirdByte +
                            _receive.receiveBytes.fourthByte;
    if(_receive.receiveBytes.fifthByte == total)
        return 1;   // return 1 if checksum is good.
    else
        return 0;
}