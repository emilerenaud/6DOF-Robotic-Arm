#include "TMC2130_interface.h"

TMC2130Class::TMC2130Class()
{
}

tmc_read TMC2130Class::Write(tmc_add add, tmc_write dataOut)
{
    tmc_read _dataIn;

    _spi.enableDevice();
    _spi.writeByte((add.readWrite << 7) + (add.address & 0x7F));
    _dataIn.firstByte = _spi.readWritebyte(dataOut.fourthByte);
    _dataIn.secondByte = _spi.readWritebyte(dataOut.thirdByte);
    _dataIn.thirdByte = _spi.readWritebyte(dataOut.secondByte);
    _dataIn.fourthByte = _spi.readWritebyte(dataOut.firstByte);

    _spi.disableDevice();
    return _dataIn;
}