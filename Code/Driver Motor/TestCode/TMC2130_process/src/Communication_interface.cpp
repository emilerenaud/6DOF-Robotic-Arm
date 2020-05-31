#include "Communication_interface.h"

// Class
ComClass::ComClass()
{
}


RECEIVE_U ComClass::Read(){
    int i = 0;
    for(int j=0; j<10; j++) // Reset buffer. Always
    {
        buffer[j] = 0;
    }
    i = 0; // just for breakpoint
    while(rs485.data_available() > 0)
    {
        buffer[i] = rs485.Read();
        i++;
    }
    _receive.receiveBytes.firstByte = buffer[0];
    _receive.receiveBytes.secondByte = buffer[1];
    _receive.receiveBytes.thirdByte = buffer[2];
    _receive.receiveBytes.fourthByte = buffer[3];
    _receive.receiveBytes.fifthByte = buffer[4];
    // rs485.Read();

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
            if(_receive.bits.adress == DRIVER)
            {
             digitalWrite(LEDB,LOW);
             delay(50);
             digitalWrite(LEDB,HIGH);
            }
        }
        else
        {
            _receive.receiveBytes.firstByte = 0;
            _receive.receiveBytes.secondByte = 0;
            _receive.receiveBytes.thirdByte = 0;
            _receive.receiveBytes.fourthByte = 0;
            _receive.receiveBytes.fifthByte = 0;
            // digitalWrite(LEDG,LOW); // Open green light if message checksum is not correct.
            while(rs485.data_available() > 0) // Clear buffer if checksum is not good.
            {
                rs485.Read();
            }
            delay(200);
            // digitalWrite(LEDG,HIGH);
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