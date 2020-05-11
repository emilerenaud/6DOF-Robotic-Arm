#include "TMC2130_interface.h"

/*Might need mask for sendBytes and receiveBytes to forbid unnecessary reading/writing*/

TMC2130Class::TMC2130Class()
{
    _en.Write(HIGH);
    _step.Write(LOW);
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

void TMC2130Class::Init()           /*Right now, TMC is initialized as the Getting Started ex. p.84*/
{
    TMC2130Class::ChopConfig();
    TMC2130Class::IHoldIrunConfig();
    TMC2130Class::TPowerDownConfig();
    TMC2130Class::GeneralConfig();
    TMC2130Class::PWMConfig();
    TMC2130Class::CoolConfig();
    TMC2130Class::TCoolThreshHold();
}

void TMC2130Class::checkDiag()
{
    if(_diag0.Read() == 0)
    {
        _debug.open_blue();
    }
    else
    {
        _debug.close_blue();
    }

    if(_diag1.Read() == 0)
    {
        _debug.open_red();
    }
    else
    {
        _debug.close_red();
    }
}

/*WORKING*/
int TMC2130Class::Rotation(float degree, float microstep, int direction)
{
    if(_calcStep)
    {
        // stepsToDo =  int(round(degree * stepsFor1degree));
        _stepsToDo = degree * (((NEMA17 * microstep * 38.4)/360)/2); // Divider by 2 cause the stepper move 2 micro-steps by clock pulse
        _calcStep = false;
    }

    _dir.Write(direction);
     _en.Write(LOW);

    if(_stepsToDo > 0)
    {
        _stepsToDo--;
        _step.Write(HIGH);
        delayMicroseconds(5);
        _step.Write(LOW);
        delayMicroseconds(5);
        return NOT_DONE;
    }

    _calcStep = true;
    _en.Write(HIGH);
    return DONE;
}

/*WORKING*/
void TMC2130Class::ChopConfig()
{
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.motor.CHOPCONF;

    dataOut.chop_conf.bits.RESERVED = LOW;
    dataOut.chop_conf.bits.DISS2G   = LOW;    //Based on chapter 22 init example.
    dataOut.chop_conf.bits.DEDGE    = HIGH;
    dataOut.chop_conf.bits.INTPOL   = LOW;
    dataOut.chop_conf.bits.MRES3    = LOW; 
    dataOut.chop_conf.bits.MRES2    = LOW;    //MRES(0..3) = 0 for 256 microstep.
    dataOut.chop_conf.bits.MRES1    = LOW;
    dataOut.chop_conf.bits.MRES0    = LOW;
    dataOut.chop_conf.bits.SYNC3    = LOW;    //SYNC(0..3) PWM synchronization clock
    dataOut.chop_conf.bits.SYNC2    = LOW;
    dataOut.chop_conf.bits.SYNC1    = LOW;
    dataOut.chop_conf.bits.SYNC0    = LOW;
    dataOut.chop_conf.bits.VHIGHCHM = LOW;   //High velocity chopper mode.
    dataOut.chop_conf.bits.VHIGHFS  = LOW;   //High velocity fullstep selection.
    dataOut.chop_conf.bits.VSENSE   = LOW;   //Sense resistor voltage based current scaling.
    dataOut.chop_conf.bits.TBL1     = HIGH;  //TBL(0..1) set comparator blank time to 16, 24, 36 or 54 clocks
    dataOut.chop_conf.bits.TBL0     = LOW;
    dataOut.chop_conf.bits.CHM      = LOW;
    dataOut.chop_conf.bits.RNDTF    = LOW;
    dataOut.chop_conf.bits.DISFDCC  = LOW;   //disables current comparator usage for termination of the fast decay cycle
    dataOut.chop_conf.bits.FD3      = LOW;   
    dataOut.chop_conf.bits.HEND3    = LOW;
    dataOut.chop_conf.bits.HEND2    = LOW;
    dataOut.chop_conf.bits.HEND1    = LOW;
    dataOut.chop_conf.bits.HEND0    = LOW;
    dataOut.chop_conf.bits.HSTRT2   = HIGH;
    dataOut.chop_conf.bits.HSTRT1   = LOW;
    dataOut.chop_conf.bits.HTSRT0   = LOW;
    dataOut.chop_conf.bits.TOFF3    = HIGH;   //TOFF off time and driver enable
    dataOut.chop_conf.bits.TOFF2    = LOW;
    dataOut.chop_conf.bits.TOFF1    = LOW;
    dataOut.chop_conf.bits.TOFF0    = LOW;

    TMC2130Class::Write(add, dataOut.chop_conf.sendBytes); 
}

/*WORKING*/
void TMC2130Class::IHoldIrunConfig(){
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.vel_ctrl.IHOLD_IRUN;
    dataOut.ihold_irun.bits.RESERVED2  = LOW;
    dataOut.ihold_irun.bits.IHOLDDELAY = 12;
    dataOut.ihold_irun.bits.RESERVED1  = LOW;
    dataOut.ihold_irun.bits.IRUN       = 15;
    dataOut.ihold_irun.bits.RESERVED0  = LOW;
    dataOut.ihold_irun.bits.IHOLD      = 5;
 
    TMC2130Class::Write(add, dataOut.ihold_irun.sendBytes); 
}

/*WORKING*/
void TMC2130Class::TPowerDownConfig(){
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.vel_ctrl.TPOWERDOWN;
    dataOut.t_powerdown.bits.RESERVED  = LOW;
    dataOut.t_powerdown.bits.TPOWERDOWN = 100; // was 10.
 
    TMC2130Class::Write(add, dataOut.t_powerdown.sendBytes); 
}

/*WORKING*/
void TMC2130Class::GeneralConfig()
{
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.gen_conf.GCONF;

    dataOut.g_conf.bits.I_SCALE_ANALOG     = LOW;
    dataOut.g_conf.bits.INT_RSENSE         = HIGH;
    dataOut.g_conf.bits.EN_PWM_MODE        = HIGH;
    dataOut.g_conf.bits.ENC_COMMUTATION    = LOW;
    dataOut.g_conf.bits.SHAFT              = LOW;
    dataOut.g_conf.bits.DIAG0_ERROR        = LOW;
    dataOut.g_conf.bits.DIAG0_OTPW         = LOW;
    dataOut.g_conf.bits.DIAG0_STALL        = LOW;
    dataOut.g_conf.bits.DIAG1_STALL        = LOW;
    dataOut.g_conf.bits.DIAG1_INDEX        = LOW;
    dataOut.g_conf.bits.DIAG1_ONSTATE      = LOW;
    dataOut.g_conf.bits.DIAG1_STEPS_SKIP   = HIGH;
    dataOut.g_conf.bits.DIAG0_INT_PUSHPULL = LOW;
    dataOut.g_conf.bits.DIAG1_PUSHPULL     = LOW;
    dataOut.g_conf.bits.SMALL_HYSTERISIS   = LOW;
    dataOut.g_conf.bits.STOP_ENABLE        = LOW;
    dataOut.g_conf.bits.DIRECT_MODE        = LOW;
    dataOut.g_conf.bits.TEST_MODE          = LOW;
    dataOut.g_conf.bits.RESERVED           = LOW;
         
    TMC2130Class::Write(add, dataOut.g_conf.sendBytes);
}

/*WORKING*/
void TMC2130Class::TPWMConfig()
{
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.vel_ctrl.TPWMTHRS;

    dataOut.t_pwm_thresh.bits.TPWMTHRS = 500;
    dataOut.t_pwm_thresh.bits.RESERVED = LOW;

    TMC2130Class::Write(add, dataOut.t_pwm_thresh.sendBytes);
}

/*WORKING*/
void TMC2130Class::PWMConfig(){
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.motor.PWMCONF;

    dataOut.pwm_conf.bits.RESERVED   = LOW;
    dataOut.pwm_conf.bits.FREEWHEEL1 = LOW;
    dataOut.pwm_conf.bits.FREEWHEEL0 = LOW;
    dataOut.pwm_conf.bits.PWM_SYMM   = LOW;
    dataOut.pwm_conf.bits.PWM_AUTO   = HIGH;
    dataOut.pwm_conf.bits.PWM_FREQ1  = LOW;
    dataOut.pwm_conf.bits.PWM_FREQ0  = HIGH;
    dataOut.pwm_conf.bits.PWM_GRAD   = 1;    
    dataOut.pwm_conf.bits.PWM_AMPL   = 255;          

    TMC2130Class::Write(add, dataOut.pwm_conf.sendBytes); 
}

/*TODO*/
void TMC2130Class::SPIModeConfig()
{
    /*Need to verify register. see tmc2130_config file.*/

    // TMCADD_S reg;
    // tmc_add add;
    // TMC dataOut;

    // add.address = reg.spi_mode.XDIRECT;
    // dataOut.xdirect.bits.COIL_A_CUR = ;
    // dataOut.xdirect.bits.COIL_B_CUR = ;

    // TMC2130Class::Write(add, dataOut.xdirect.sendBytes); 
}

/*VERIFY*/
void TMC2130Class::CoolConfig(){
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.motor.COOLCONF;

    dataOut.cool_conf.bits.RESERVED4 = LOW;
    dataOut.cool_conf.bits.SFILT     = HIGH;    //stallguard2 filter enable.
    dataOut.cool_conf.bits.RESERVED3 = LOW;
    dataOut.cool_conf.bits.SGT6      = LOW;      //SGT(0..6) adjust value for stallguard2.
    dataOut.cool_conf.bits.SGT5      = LOW; 
    dataOut.cool_conf.bits.SGT4      = LOW;
    dataOut.cool_conf.bits.SGT3      = LOW;
    dataOut.cool_conf.bits.SGT2      = HIGH;
    dataOut.cool_conf.bits.SGT1      = HIGH;
    dataOut.cool_conf.bits.SGT0      = HIGH;
    dataOut.cool_conf.bits.SEIMIN    = HIGH;   //Smart current control HIGH = 1/4 of IRUN and LOW = 1/2 of IRUN.
    dataOut.cool_conf.bits.SEDN1     = HIGH;   //SEDN(0..1) current down step speed.
    dataOut.cool_conf.bits.SEDN0     = LOW;
    dataOut.cool_conf.bits.RESERVED2 = LOW;
    dataOut.cool_conf.bits.SEMAX3    = HIGH;    //SEMAX(0..3) stallguard2 hysterisis for current control. (0 to 15).
    dataOut.cool_conf.bits.SEMAX2    = HIGH;
    dataOut.cool_conf.bits.SEMAX1    = HIGH;
    dataOut.cool_conf.bits.SEMAX0    = HIGH;
    dataOut.cool_conf.bits.RESERVED1 = LOW;
    dataOut.cool_conf.bits.SEUP1     = LOW;     //SEUP(0..1) Current increment steps per measured stallGuard2 value %00 … %11: 1, 2, 4, 8.
    dataOut.cool_conf.bits.SEUP0     = HIGH;
    dataOut.cool_conf.bits.RESERVED0 = LOW;
    dataOut.cool_conf.bits.SEMIN3    = LOW;    //SEMIN(0..3) minimum stallGuard2 value for smart current 
    dataOut.cool_conf.bits.SEMIN2    = LOW;    //control and smart current enable (1 to 15 and 0 to disable).
    dataOut.cool_conf.bits.SEMIN1    = LOW;
    dataOut.cool_conf.bits.SEMIN0    = HIGH;

    TMC2130Class::Write(add, dataOut.cool_conf.sendBytes); 
}

/*WORKING*/
void TMC2130Class::TCoolThreshHold(){
    TMCADD_S reg;
    tmc_add add;
    TMC dataOut;

    add.address = reg.vel_ctrl.TCOOLTHRS;
    dataOut.t_cool_thresh.bits.TCOOLTHRS = 1;

 
    TMC2130Class::Write(add, dataOut.t_cool_thresh.sendBytes); 
}

/*VERIFY*/
void TMC2130Class::ReadRegisters()
{
    TMCADD_S reg;
    tmc_add add;
    TMC dataIn; 

    add.address = reg.gen_conf.GCONF;                          //Might need a mask
    dataIn.g_conf.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.gen_conf.GSTAT;
    dataIn.g_stat.receiveBytes = TMC2130Class::Read(add);

    add.address = reg.gen_conf.IOIN;
    dataIn.ioin.receiveBytes = TMC2130Class::Read(add);

    // add.address = reg.vel_ctrl.TSTEP;                       //Unused right now.
    // dataIn.t_step.receiveBytes = TMC2130Class::Read(add);

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