#include "TMC2130_interface.h"

/*Might need mask for sendBytes and receiveBytes to forbid unnecessary reading/writing*/

TMC2130Class::TMC2130Class()
{
}

void TMC2130Class::Write(tmc_add add, tmc_write dataOut)
{
    add.readWrite = WRITE;
    
    _spi.enableDevice();
    _spi.writeByte((add.readWrite << 7) + (add.address & 0x7F));
    _spi.writeByte(dataOut.fourthByte);
    _spi.writeByte(dataOut.thirdByte);
    _spi.writeByte(dataOut.secondByte);
    _spi.writeByte(dataOut.firstByte);
    _spi.disableDevice();
}


tmc_read TMC2130Class::Read(tmc_add add)
{
    tmc_read _dataIn;

    add.readWrite = READ;

    _spi.enableDevice();
    _spi.writeByte((add.readWrite << 7) + (add.address & 0x7F));
    _dataIn.firstByte = _spi.readByte();
    _dataIn.secondByte = _spi.readByte();
    _dataIn.thirdByte = _spi.readByte();
    _dataIn.fourthByte = _spi.readByte();
    _spi.disableDevice();
    return _dataIn;
}


void TMC2130Class::GeneralConfig()
{
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.gen_conf.GCONF;

    dataOut.g_conf.bits.I_SCALE_ANALOG = LOW;
    dataOut.g_conf.bits.INT_RSENSE = LOW;
    dataOut.g_conf.bits.DIAG0_INT_PUSHPULL = LOW;
    dataOut.g_conf.bits.DIAG1_PUSHPULL = LOW;
    dataOut.g_conf.bits.SMALL_HYSTERISIS = HIGH;
    dataOut.g_conf.bits.STOP_ENABLE = LOW;
    dataOut.g_conf.bits.DIRECT_MODE = LOW;
    dataOut.g_conf.bits.TEST_MODE = LOW;

    TMC2130Class::Write(add, dataOut.g_conf.sendBytes);
}

void TMC2130Class::SPIModeConfig()
{
    /*Need to verify register. see tmc2130_config file.*/
    //TODO

    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.spi_mode.XDIRECT;

    TMC2130Class::Write(add, dataOut.xdirect.sendBytes); 
}

void TMC2130Class::ChopConfig()
{
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.motor.CHOPCONF;

    dataOut.chop_conf.bits.DISS2G = LOW;    //?? not sure.

    dataOut.chop_conf.bits.MRES3  = LOW; 
    dataOut.chop_conf.bits.MRES2  = LOW;    //MRES(0..3) = 0 for 256 microstep.
    dataOut.chop_conf.bits.MRES1  = LOW;
    dataOut.chop_conf.bits.MRES0  = LOW;

    dataOut.chop_conf.bits.SYNC3  = LOW;    //SYNC(0..3) PWM synchronization clock
    dataOut.chop_conf.bits.SYNC2  = LOW;
    dataOut.chop_conf.bits.SYNC1  = HIGH;
    dataOut.chop_conf.bits.SYNC0  = HIGH;

    dataOut.chop_conf.bits.VHIGHCHM = HIGH; //High velocity chopper mode.
    dataOut.chop_conf.bits.VHIGHFS  = HIGH; //High velocity fullstep selection.
    dataOut.chop_conf.bits.VSENSE   = HIGH; //Sense resistor voltage based current scaling.

    dataOut.chop_conf.bits.TBL1 = LOW;      //TBL(0..1) set comparator blank time to 16, 24, 36 or 54 clocks
    dataOut.chop_conf.bits.TBL0 = HIGH;

    dataOut.chop_conf.bits.CHM  = HIGH;
    dataOut.chop_conf.bits.RNDTF = LOW;

    dataOut.chop_conf.bits.DISFDCC = HIGH;  //disables current comparator usage for termination of the fast decay cycle

    dataOut.chop_conf.bits.FD3 = LOW;       //?? not sure.

    dataOut.chop_conf.bits.HEND3 = LOW;
    dataOut.chop_conf.bits.HEND2 = LOW;
    dataOut.chop_conf.bits.HEND1 = HIGH;
    dataOut.chop_conf.bits.HEND0 = HIGH;
    dataOut.chop_conf.bits.HSTRT2 = LOW;
    dataOut.chop_conf.bits.HSTRT1 = LOW;
    dataOut.chop_conf.bits.HTSRT0 = HIGH;

    dataOut.chop_conf.bits.TOFF3  = LOW;    //TOFF off time and driver enable
    dataOut.chop_conf.bits.TOFF2  = HIGH;
    dataOut.chop_conf.bits.TOFF1  = HIGH;
    dataOut.chop_conf.bits.TOFF0  = HIGH;

    TMC2130Class::Write(add, dataOut.chop_conf.sendBytes); 
}

void TMC2130Class::CoolConfig(){
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.motor.COOLCONF;

    dataOut.cool_conf.bits.RESERVED4 = LOW;
    dataOut.cool_conf.bits.SFILT = HIGH;    //stallguard2 filter enable.
    dataOut.cool_conf.bits.RESERVED3 = LOW;
    dataOut.cool_conf.bits.SGT6 = LOW;      //SGT(0..6) adjust value for stallguard2.
    dataOut.cool_conf.bits.SGT5 = LOW; 
    dataOut.cool_conf.bits.SGT4 = LOW;
    dataOut.cool_conf.bits.SGT3 = LOW;
    dataOut.cool_conf.bits.SGT2 = LOW;
    dataOut.cool_conf.bits.SGT1 = LOW;
    dataOut.cool_conf.bits.SGT0 = LOW;
    dataOut.cool_conf.bits.SEIMIN = HIGH;   //Smart current control HIGH = 1/4 of IRUN and LOW = 1/2 of IRUN.
    dataOut.cool_conf.bits.SEDN1  = HIGH;   //SEDN(0..1) current down step speed.
    dataOut.cool_conf.bits.SEDN0  = LOW;
    dataOut.cool_conf.bits.RESERVED2 = LOW;
    dataOut.cool_conf.bits.SEMAX3 = LOW;    //SEMAX(0..3) stallguard2 hysterisis for current control. (0 to 15).
    dataOut.cool_conf.bits.SEMAX2 = LOW;
    dataOut.cool_conf.bits.SEMAX1 = HIGH;
    dataOut.cool_conf.bits.SEMAX0 = HIGH;
    dataOut.cool_conf.bits.RESERVED1 = LOW;
    dataOut.cool_conf.bits.SEUP1 = LOW;     //SEUP(0..1) Current increment steps per measured stallGuard2 value %00 … %11: 1, 2, 4, 8.
    dataOut.cool_conf.bits.SEUP0 = HIGH;
    dataOut.cool_conf.bits.RESERVED0 = LOW;
    dataOut.cool_conf.bits.SEMIN3 = LOW;    //SEMIN(0..3) minimum stallGuard2 value for smart current 
    dataOut.cool_conf.bits.SEMIN2 = LOW;    //control and smart current enable (1 to 15 and 0 to disable).
    dataOut.cool_conf.bits.SEMIN1 = HIGH;
    dataOut.cool_conf.bits.SEMIN0 = HIGH;
    TMC2130Class::Write(add, dataOut.cool_conf.sendBytes); 
}

void TMC2130Class::MicroSteppingConfig(){

    //TODO
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;
}

void TMC2130Class::PWMConfig(){
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.motor.PWMCONF;

    dataOut.pwm_conf.bits.RESERVED  = LOW;
    dataOut.pwm_conf.bits.FREEWHEEL1 = LOW;
    dataOut.pwm_conf.bits.FREEWHEEL0 = LOW;
    dataOut.pwm_conf.bits.PWM_SYMM  = LOW;
    dataOut.pwm_conf.bits.PWM_AUTO  = HIGH;
    dataOut.pwm_conf.bits.PWM_FREQ1 = LOW;
    dataOut.pwm_conf.bits.PWM_FREQ0 = LOW;
    dataOut.pwm_conf.bits.PWM_GRAD  = 128;    //?? not sure.
    dataOut.pwm_conf.bits.PWM_AMPL  = 128;    //?? not sure.       

    TMC2130Class::Write(add, dataOut.pwm_conf.sendBytes); 
}


void TMC2130Class::ReadRegisters()
{
    TMCADD_S reg;
    tmc_add add;
    TMC dataIn; 

    add.address = reg.gen_conf.GCONF;                          //Might need a mask.
    dataIn.g_conf.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.gen_conf.GSTAT;
    dataIn.g_stat.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.gen_conf.IOIN;
    dataIn.ioin.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.vel_ctrl.TSTEP;
    dataIn.t_step.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.spi_mode.XDIRECT;                        //Might need a mask.
    dataIn.xdirect.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.motor.MSCNT;
    dataIn.ms_cnt.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.motor.MSCURACT;
    dataIn.ms_cur_act.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.motor.CHOPCONF;                           //Might need a mask.
    dataIn.chop_conf.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.motor.DRV_STATUS;
    dataIn.drv_status.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.motor.PWM_SCALE;
    dataIn.pwm_scale.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.motor.LOST_STEPS;
    dataIn.lost_steps.receiveBytes = TMC2130Class::Read(add);
}