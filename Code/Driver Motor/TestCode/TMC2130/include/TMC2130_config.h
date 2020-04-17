#ifndef TMC2130_CONFIG_H
#define TMC2130_CONFIG_H

struct tmc_read
{
    uint8_t firstByte;
    uint8_t secondByte;
    uint8_t thirdByte;
    uint8_t fourthByte;
};

struct tmc_write
{
    uint8_t firstByte;
    uint8_t secondByte;
    uint8_t thirdByte;
    uint8_t fourthByte;
};

struct tmc_add
{
    uint8_t address : 7;
    uint8_t readWrite : 1;
};

//////////////////////////////////////

/*register addresses*/

struct GENCONFREG_S
{
    uint8_t GCONF			= 0x00;
    uint8_t GSTAT			= 0x01;
    uint8_t IOIN			= 0x04;
}; 

//////////////////////////////////////

struct VELCTRLREG_S
{
    uint8_t IHOLD_IRUN	    = 0x10;
    uint8_t TPOWERDOWN	    = 0x11;
    uint8_t TSTEP			= 0x12;
    uint8_t TPWMTHRS		= 0x13;
    uint8_t TCOOLTHRS		= 0x14;
    uint8_t THIGH			= 0x15;
};

//////////////////////////////////////

struct SPIMODEREG_S
{
    uint8_t XDIRECT		    = 0x2D;
}; 

//////////////////////////////////////

struct DCSTEPREG_S
{
    uint8_t VDCMIN		    = 0x33;
}; 

//////////////////////////////////////

struct MOTORREG_S
{
    uint8_t MSLUT0		    = 0x60;
    uint8_t MSLUT1		    = 0x61;
    uint8_t MSLUT2		    = 0x62;
    uint8_t MSLUT3		    = 0x63;
    uint8_t MSLUT4		    = 0x64;
    uint8_t MSLUT5		    = 0x65;
    uint8_t MSLUT6	    	= 0x66;
    uint8_t MSLUT7		    = 0x67;
    uint8_t MSLUTSEL		= 0x68;
    uint8_t MSLUTSTART	    = 0x69;
    uint8_t MSCNT			= 0x6A;
    uint8_t MSCURACT		= 0x6B;
    uint8_t CHOPCONF		= 0x6C;
    uint8_t COOLCONF		= 0x6D;
    uint8_t DCCTRL		    = 0x6E;
    uint8_t DRV_STATUS	    = 0x6F;
    uint8_t PWMCONF		    = 0x70;
    uint8_t PWM_SCALE		= 0x71;
    uint8_t ENCM_CTRL		= 0x72;
    uint8_t LOST_STEPS	    = 0x73;
}; 

/*struct of all registers addresses grouped*/

struct TMCADD_S
{
    GENCONFREG_S gen_conf;
    VELCTRLREG_S vel_ctrl;
    SPIMODEREG_S spi_mode;
    DCSTEPREG_S  dc_step;
    MOTORREG_S   motor;
};

/*struct of registers bit*/

//////////////////////////////////////

struct GCONF_S
{

        uint8_t I_SCALE_ANALOG      : 1;    //LSB
        uint8_t INT_RSENSE          : 1;
        uint8_t EN_PWM_MODE         : 1;
        uint8_t ENC_COMMUTATION     : 1;
        uint8_t SHAFT               : 1;
        uint8_t DIAG0_ERROR         : 1;
        uint8_t DIAG0_OTPW          : 1;
        uint8_t DIAG0_STALL         : 1;
        uint8_t DIAG1_STALL         : 1;
        uint8_t DIAG1_INDEX         : 1;
        uint8_t DIAG1_ONSTATE       : 1;
        uint8_t DIAG1_STEPS_SKIP    : 1;
        uint8_t DIAG0_INT_PUSHPULL  : 1;
        uint8_t DIAG1_PUSHPULL      : 1;
        uint8_t SMALL_HYSTERISIS    : 1;
        uint8_t STOP_ENABLE         : 1;
        uint8_t DIRECT_MODE         : 1;
        uint8_t TEST_MODE           : 1;    
        uint16_t RESERVED           : 14;   //MSB

};

union   GCONF_U
{ 
    GCONF_S   bits;
    tmc_write sendBytes;
    tmc_read  receiveBytes; 
}; 

//////////////////////////////////////

struct GSTAT_S
{   
    uint8_t RESET     : 1;
    uint8_t DRV_ERR   : 1;
    uint8_t UV_CP     : 1;
    uint32_t RESERVED : 29;
};

union GSTAT_U
{
    GSTAT_S   bits;
    tmc_read  receiveBytes;
}; 

//////////////////////////////////////

struct IOIN_S
{    
    uint8_t STEP_REG     : 1;
    uint8_t DIR_REG      : 1;
    uint8_t DCEN_CFG4    : 1;
    uint8_t DCIN_CFG5    : 1;
    uint8_t DRV_ENN_CFG6 : 1;
    uint8_t DCO_REG      : 1;
    uint8_t RESERVED0    : 1;
    uint8_t RESERVED1    : 1;
    uint16_t RESERVED2   : 16;
    uint8_t VERSION      : 8;
};

union IOIN_U
{
    IOIN_S    bits;
    tmc_read  receiveBytes;
}; 

//////////////////////////////////////

struct IHOLD_IRUN_S
{    
    uint8_t IHOLD      : 5;     // x x x x x x x x / x x 0 0  0 1 0 0 / 0 0 0 1  1 1 1 1 / 0 0 0 0  1 0 1 0 
    uint8_t RESERVED0  : 3;
    uint8_t IRUN       : 5;
    uint8_t RESERVED1  : 3;
    uint8_t IHOLDDELAY : 4;     //Check in datasheet for bit index. (p.27)
    uint16_t RESERVED2 : 12;
};

union IHOLD_IRUN_U
{
    IHOLD_IRUN_S bits;
    tmc_write    sendBytes;
}; 

//////////////////////////////////////

struct TPOWERDOWN_S 
{  
    uint8_t TPOWERDOWN : 8;
    uint32_t RESERVED : 24;
};

union TPOWERDOWN_U
{
    TPOWERDOWN_S bits;
    tmc_write    sendBytes;
}; 

//////////////////////////////////////

struct TSTEP_S 
{   
    uint32_t TSTEP :    20; 
    uint16_t RESERVED : 12;
};

union TSTEP_U
{
    TSTEP_S   bits;
    tmc_read  receiveBytes;
}; 

//////////////////////////////////////

struct TPWMTHRS_S 
{  
    uint32_t TPWMTHRS : 20; 
    uint16_t RESERVED : 12;
};

union TPWMTHRS_U
{
    TPWMTHRS_S bits;
    tmc_write  sendBytes;
}; 

//////////////////////////////////////

struct TCOOLTHRS_S 
{   
    uint32_t TCOOLTHRS : 20; 
    uint16_t RESERVED  : 12; 
};

union TCOOLTHRS_U
{
    TCOOLTHRS_S bits;
    tmc_write  sendBytes;
}; 

//////////////////////////////////////

struct THIGH_S 
{
    uint32_t THIGH : 20;  
    uint16_t RESERVED : 12;
};

union THIGH_U
{
    THIGH_S   bits;
    tmc_write sendBytes;
}; 

//////////////////////////////////////

struct XDIRECT_S
{  
    uint16_t COIL_A_CUR : 9;    //VERIFY (p.29)
    uint8_t  RESERVED   : 7;
    uint16_t COIL_B_CUR : 9;
};

union XDIRECT_U
{
    XDIRECT_S bits;
    tmc_write sendBytes;
    tmc_read  receiveBytes;
};


//////////////////////////////////////

struct VDCMIN_S 
{  
    uint32_t VDCMIN : 23;  
    uint16_t RESERVED : 9;
};

union VDCMIN_U
{
    VDCMIN_S  bits;
    tmc_read  receiveBytes;
}; 

//////////////////////////////////////

struct MSLUT_S              //**************************
{
        uint32_t MSLUT7;
        uint32_t MSLUT6;
        uint32_t MSLUT5;
        uint32_t MSLUT4;
        uint32_t MSLUT3;
        uint32_t MSLUT2;
        uint32_t MSLUT1;
        uint32_t MSLUT0;
};

//////////////////////////////////////

struct MSLUTSEL_S
{
    uint8_t W0 : 2;
    uint8_t W1 : 2;
    uint8_t W2 : 2;
    uint8_t W3 : 2;
    uint8_t X1 : 8;
    uint8_t X2 : 8;
    uint8_t X3 : 8;
};

union MSLUTSEL_U
{
    MSLUTSEL_S bits;
    tmc_write  sendBytes;
}; 

//////////////////////////////////////

struct MSLUTSTART_S
{
    uint8_t START_SIN   : 8;
    uint8_t RESERVED0   : 8;
    uint8_t START_SIN90 : 8;
    uint8_t RESERVED1   : 8;
};

union MSLUTSTART_U
{
    MSLUTSTART_S bits;
    tmc_write    sendBytes;
}; 

//////////////////////////////////////

struct MSCNT_S 
{ 
    uint16_t MSCNT    : 10; 
    uint32_t RESERVED : 22;
};

union MSCNT_U
{
    MSCNT_S  bits;
    tmc_read receiveBytes;
}; 

//////////////////////////////////////

struct MSCURACT_S
{ 
    uint16_t CUR_A    : 9;
    uint8_t RESERVED0 : 7;
    uint16_t CUR_B    : 9;
    uint8_t RESERVED1 : 7;
};

union MSCURACT_U
{
    MSCURACT_S bits;
    tmc_read  receiveBytes;
}; 

//////////////////////////////////////

struct CHOPCONF_S
{
    uint8_t TOFF0    : 1;
    uint8_t TOFF1    : 1;
    uint8_t TOFF2    : 1;
    uint8_t TOFF3    : 1;
    uint8_t HTSRT0   : 1;
    uint8_t HSTRT1   : 1;
    uint8_t HSTRT2   : 1;
    uint8_t HEND0    : 1;
    uint8_t HEND1    : 1;
    uint8_t HEND2    : 1;
    uint8_t HEND3    : 1;
    uint8_t FD3      : 1;
    uint8_t DISFDCC  : 1;
    uint8_t RNDTF    : 1;
    uint8_t CHM      : 1;
    uint8_t TBL0     : 1;
    uint8_t TBL1     : 1;
    uint8_t VSENSE   : 1;
    uint8_t VHIGHFS  : 1;
    uint8_t VHIGHCHM : 1;
    uint8_t SYNC0    : 1;
    uint8_t SYNC1    : 1;   
    uint8_t SYNC2    : 1;
    uint8_t SYNC3    : 1;
    uint8_t MRES0    : 1;
    uint8_t MRES1    : 1;
    uint8_t MRES2    : 1;
    uint8_t MRES3    : 1;
    uint8_t INTPOL   : 1;//R
    uint8_t DEDGE    : 1;//R
    uint8_t DISS2G   : 1;
    uint8_t RESERVED : 1;
};

union CHOPCONF_U
{
    CHOPCONF_S bits;
    tmc_write  sendBytes;
    tmc_read   receiveBytes;
}; 

//////////////////////////////////////

struct COOLCONF_S
{
    uint8_t SEMIN0    : 1;
    uint8_t SEMIN1    : 1;
    uint8_t SEMIN2    : 1;
    uint8_t SEMIN3    : 1; 
    uint8_t RESERVED0 : 1;
    uint8_t SEUP0     : 1;
    uint8_t SEUP1     : 1;
    uint8_t RESERVED1 : 1;
    uint8_t SEMAX0    : 1;
    uint8_t SEMAX1    : 1;
    uint8_t SEMAX2    : 1;
    uint8_t SEMAX3    : 1;
    uint8_t RESERVED2 : 1;
    uint8_t SEDN0     : 1;
    uint8_t SEDN1     : 1;
    uint8_t SEIMIN    : 1;
    uint8_t SGT0      : 1;   
    uint8_t SGT1      : 1;
    uint8_t SGT2      : 1;
    uint8_t SGT3      : 1;
    uint8_t SGT4      : 1;
    uint8_t SGT5      : 1;
    uint8_t SGT6      : 1;
    uint8_t RESERVED3 : 1;
    uint8_t SFILT     : 1;
    uint8_t RESERVED4 : 7;  
};

union COOLCONF_U
{
    COOLCONF_S bits;
    tmc_write  sendBytes;
}; 

//////////////////////////////////////

struct DCCTRL_S
{        
    uint16_t DC_TIME  : 10;
    uint8_t RESERVED0 : 6;
    uint8_t DC_SG     : 8; 
    uint8_t RESERVED1 : 8;     
};

union DCCTRL_U
{
    DCCTRL_S  bits;
    tmc_write sendBytes;
}; 

//////////////////////////////////////

struct DRVSTATUS_S
{
    uint16_t SG_RESULT  : 10;  
    uint8_t RESERVED0  : 5;
    uint8_t FSACTIVE   : 1;
    uint8_t CSACTUAL   : 5;
    uint8_t RESERVED1  : 3;
    uint8_t STALLGUARD : 1;
    uint8_t OT         : 1;
    uint8_t OTPW       : 1;
    uint8_t S2GA       : 1;
    uint8_t S2GB       : 1;
    uint8_t OLA        : 1;
    uint8_t OLB        : 1;
    uint8_t STST       : 1; 
};

union DRVSTATUS_U
{
    DRVSTATUS_S bits;
    tmc_read  receiveBytes;
}; 

//////////////////////////////////////

struct PWMCONF_S
{
    uint8_t PWM_AMPL   : 8; 
    uint8_t PWM_GRAD   : 8;
    uint8_t PWM_FREQ0  : 1;
    uint8_t PWM_FREQ1  : 1;
    uint8_t PWM_AUTO    : 1;
    uint8_t PWM_SYMM   : 1;
    uint8_t FREEWHEEL0 : 1;
    uint8_t FREEWHEEL1 : 1;
    uint16_t RESERVED  : 10;   
};

union PWMCONF_U
{
    PWMCONF_S bits;
    tmc_write sendBytes;
}; 

//////////////////////////////////////

struct PWM_SCALE_S 
{  
    uint8_t PWM_SCALE : 8;
    uint32_t RESERVED : 24;
};

union PWM_SCALE_U
{
    PWM_SCALE_S bits;
    tmc_read    receiveBytes;
}; 

//////////////////////////////////////

struct ENCM_CTRL_S 
{ 
    uint8_t  INV      : 1; 
    uint8_t  MAXSPEED : 1;
    uint32_t RESERVED : 30;
};

union ENCM_CTRL_U 
{
    ENCM_CTRL_S bits;
    tmc_write   sendBytes;
}; 

//////////////////////////////////////

struct LOST_STEPS_S 
{ 
    uint16_t STEPS      : 10; 
    uint32_t RESERVED   : 22; 
};

union LOST_STEPS_U
{
    LOST_STEPS_S bits;
    tmc_read     receiveBytes;
}; 

//////////////////////////////////////

struct TMC
{
    GCONF_U      g_conf;
    GSTAT_U      g_stat;
    IOIN_U       ioin;
    IHOLD_IRUN_U ihold_irun;
    TPOWERDOWN_U t_powerdown;
    TSTEP_U      t_step;
    TPWMTHRS_U   t_pwm_thresh;
    TCOOLTHRS_U  t_cool_thresh;
    THIGH_U      t_high;
    XDIRECT_U    xdirect;
    VDCMIN_U     vdc_min;
    MSLUT_S      ms_lut;
    MSLUTSEL_U   ms_lut_sel;
    MSLUTSTART_U ms_lut_start;
    MSCNT_U      ms_cnt;
    MSCURACT_U   ms_cur_act;
    CHOPCONF_U   chop_conf;
    COOLCONF_U   cool_conf;
    DCCTRL_U     dc_ctrl;
    DRVSTATUS_U  drv_status;
    PWMCONF_U    pwm_conf;
    PWM_SCALE_U  pwm_scale;
    ENCM_CTRL_U  encm_ctrl;
    LOST_STEPS_U lost_steps;
};

#endif