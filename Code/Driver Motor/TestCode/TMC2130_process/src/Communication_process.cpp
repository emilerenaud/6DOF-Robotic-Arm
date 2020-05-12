#include <Communication_process.h>

ComProcess::ComProcess()
{
}

void ComProcess::DecodeData()
{
    _com.processData();
    if(_readyForNewData == 1)
    {
        if(_com._receive.bits.adress == DRIVER || _com._receive.bits.adress == DEBUG)
        {
            _position = (uint16_t(_com._receive.bits.position) << 1) + _com._receive.bits.firstbit;
            _adress = _com._receive.bits.adress;
            _homing = _com._receive.bits.homing;
            _red = !_com._receive.bits.red;
            _green = !_com._receive.bits.green;
            _blue = !_com._receive.bits.blue;
            _endis = _com._receive.bits.endis;    
            _gripper = _com._receive.bits.gripper;
            _position = _com._receive.bits.position;
            _fan = _com._receive.bits.fan;
        }
        
    }


    

}
