/*This is the configuration file. Here you can configure the motor driver PCB. Uncomment or comment
  to define or undefine configuration. Don't modify define values unless you know what you are doing.
  Defines follow Atlium design schematic found in the github repository. The pins names are defined
  from Arduino variant.h file.*/

#ifndef CONFIGURATION_H
    #define CONFIGURATION_H

    #define TMC2130
    #define SPI_EN
    #define HALL_SENSOR
    #define TEMP_SENSOR
    //#define SERVO_EN
    #define RS485
    #define DEBUG
    #define FAN_EN

    #ifdef TMC2130
        #define CS_TMC2130 PA0
        #define EN    PA2
        #define STEP  PA3
        #define DIR   PA4
        #define DIAG0 PB8
        #define DIAG1 PB9
        #define DCO   PB13
        #define DCEN  PB14
        #define DCIN  PB15
    #endif 

    #ifdef SPI_EN
        #define SCK  PA5
        #define MISO PA6
        #define MOSI PA7
    #endif

    #ifdef HALL_SENSOR
        #define HALL PA1
    #endif

    #ifdef TEMP_SENSOR
        #define TEMP PB0
    #endif

    #ifdef RS485
        #define TX PB10 
        #define RX PB11
        #define RXTX_EN PB12
        #define READ  LOW
        #define WRITE HIGH
    #endif

    #ifdef DEBUG
        #define LEDR PB5
        #define LEDB PB6
        #define LEDG PB7
    #endif

    #ifdef FAN_EN
        #define FAN PA12
    #endif

    #ifdef SERVO_EN
        #define SERVO PB0 
    #endif
	
	#define ENABLED HIGH
	#define DISABLED LOW

	#define READ LOW
	#define WRITE HIGH

	#define NEMA17 200
	#define TINCAN 48

    #define MOTOR NEMA17
	
    #define CW HIGH
    #define CCW LOW

    #define DONE 1
    #define NOT_DONE 0

    #define ACTIVE 1
    #define INACTIVE 0

    #define DEBUG 0
    #define SHOULDER 1
    #define BICEP 2
    #define FOREARM 3
    #define WRIST 4
    #define WRIST_R 5
    #define GRIPPER_R 6

    #define DRIVER SHOULDER

#endif