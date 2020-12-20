// *********************************************************************
//                               IQRF OS macros                        *
// *********************************************************************
// Just for easier life (better mnemonic and compatibility with older
// versions only).
//
// Online IQRF OS Reference Guide: http://www.iqrf.org/IQRF-OS-Reference-guide/
//
// Copyright (c) IQRF Tech s.r.o.
//
// Intended for:
//   OS: v4.04D
//
// File:    IQRF-macros.h
// Version: v1.00                                   Revision: 19/05/2020
//
// Revision history:
//   v1.00: 19/05/2020  First release for OS 4.04D.
//
// *********************************************************************

#define TRUE            1
#define FALSE           0

#define F_OSC           16000000    // 16 MHz MCU clock

#define buttonPressed   (!PORTB.4)  // Button on DK-EVAL-04x
#define TX_POWER_MAX    7
#define EEE_BLOCK_SIZE  64          // External EEPROM data block size

#define setTXpower(level)   setRFpower(level)
#define prebondNode()       prebondNodeAtNode()

// --- setRFmode(mode) ---
#define _RX_STD         0x00        // RX mode STD
#define _RX_LP          0x01        // RX mode LP
#define _RX_XLP         0x02        // RX mode XLP
#define _RLPMAT         0x04        // LP/XLP RX asynchronous termination
#define _TX_STD         0x00        // TX mode STD
#define _TX_LP          0x10        // TX mode LP
#define _TX_XLP         0x20        // TX mode XLP
#define _WPE            0x40        // Wait Packet End
#define _STDL           0x80        // Prolongs preamble for STD TX mode

// --- Reset ---
#define reset()         softReset()

// --- Sleep with wake-up on pin change ---
// Remarks: FSR1 register is destroyed
#define sleepWOC()                          /* Wake-up on both rising and falling edge*/            \
    do {                                                                                            \
        GIE = 0;                            /* Global interrupt disabled*/                          \
        IOCBP.4 = 1;                        /* Positive edge enabled (clear if not required)*/      \
        FSR1 = &IOCBN;                                                                              \
        setINDF1(IOCBN | 0x10);             /* Negative edge enabled. This bit (IOCBN.4) can not*/  \
                                            /*   be accessed directly due to OS restriction*/       \
        IOCIE = 1;                          /* Interrupt on change enabled*/                        \
        GIE = 1;                            /* Global interrupt enabled*/                           \
        setWDToff();                        /* Watchdog disabled*/                                  \
        iqrfSleep();                        /* Sleep*/                                              \
        GIE = 0;                                                                                    \
        FSR1 = &IOCBN;                                                                              \
        setINDF1(IOCBN & ~0x10);            /* Negative edge disabled (IOCBN.4)*/                   \
        IOCBP.4 = 0;                        /* Positive edge disabled*/                             \
        GIE = 1;                                                                                    \
    } while (0)

// --- Watchdog Timer ---
#define setWDTon()        SWDTEN = 1            // WDT on
#define setWDToff()       SWDTEN = 0            // WDT off

#define WDTCON_1ms        0b00000.1             // WDT on, timeout 1 ms
#define WDTCON_2ms        0b00001.1             // WDT on, timeout 2 ms
#define WDTCON_4ms        0b00010.1             // WDT on, timeout 4 ms
#define WDTCON_8ms        0b00011.1             // WDT on, timeout 8 ms
#define WDTCON_16ms       0b00100.1             // WDT on, timeout 16 ms
#define WDTCON_32ms       0b00101.1             // WDT on, timeout 32 ms
#define WDTCON_64ms       0b00110.1             // WDT on, timeout 64 ms
#define WDTCON_128ms      0b00111.1             // WDT on, timeout 128 ms
#define WDTCON_256ms      0b01000.1             // WDT on, timeout 256 ms
#define WDTCON_512ms      0b01001.1             // WDT on, timeout 512 ms
#define WDTCON_1s         0b01010.1             // WDT on, timeout 1 s
#define WDTCON_2s         0b01011.1             // WDT on, timeout 2 s
#define WDTCON_4s         0b01100.1             // WDT on, timeout 4 s
#define WDTCON_8s         0b01101.1             // WDT on, timeout 8 s
#define WDTCON_16s        0b01110.1             // WDT on, timeout 16 s
#define WDTCON_32s        0b01111.1             // WDT on, timeout 32 s
#define WDTCON_64s        0b10000.1             // WDT on, timeout 64 s
#define WDTCON_128s       0b10001.1             // WDT on, timeout 128 s
#define WDTCON_256s       0b10010.1             // WDT on, timeout 256 s

#define setWDTon_1ms()    WDTCON = WDTCON_1ms   // WDT on, timeout 1 ms
#define setWDTon_2ms()    WDTCON = WDTCON_2ms   // WDT on, timeout 2 ms
#define setWDTon_4ms()    WDTCON = WDTCON_4ms   // WDT on, timeout 4 ms
#define setWDTon_8ms()    WDTCON = WDTCON_8ms   // WDT on, timeout 8 ms
#define setWDTon_16ms()   WDTCON = WDTCON_16ms  // WDT on, timeout 16 ms
#define setWDTon_32ms()   WDTCON = WDTCON_32ms  // WDT on, timeout 32 ms
#define setWDTon_64ms()   WDTCON = WDTCON_64ms  // WDT on, timeout 64 ms
#define setWDTon_128ms()  WDTCON = WDTCON_128ms // WDT on, timeout 128 ms
#define setWDTon_256ms()  WDTCON = WDTCON_256ms // WDT on, timeout 256 ms
#define setWDTon_512ms()  WDTCON = WDTCON_512ms // WDT on, timeout 512 ms
#define setWDTon_1s()     WDTCON = WDTCON_1s    // WDT on, timeout 1 s
#define setWDTon_2s()     WDTCON = WDTCON_2s    // WDT on, timeout 2 s
#define setWDTon_4s()     WDTCON = WDTCON_4s    // WDT on, timeout 4 s
#define setWDTon_8s()     WDTCON = WDTCON_8s    // WDT on, timeout 8 s
#define setWDTon_16s()    WDTCON = WDTCON_16s   // WDT on, timeout 16 s
#define setWDTon_32s()    WDTCON = WDTCON_32s   // WDT on, timeout 32 s
#define setWDTon_64s()    WDTCON = WDTCON_64s   // WDT on, timeout 64 s
#define setWDTon_128s()   WDTCON = WDTCON_128s  // WDT on, timeout 128 s
#define setWDTon_256s()   WDTCON = WDTCON_256s  // WDT on, timeout 256 s

// --- Debug with breakpoint number ---
// uns8 wValue: breakpoint number displayed in IQRF IDE
#define debugW(wValue)  \
    do {                \
        W = wValue;     \
        debug();        \
    } while (0)

#define breakpoint(wValue)  debugW(wValue)

// --- Brown-Out Reset ---
#define setBORon()      writeToRAM(&BORCON, 0x80)   // BOR on
#define setBORoff()     writeToRAM(&BORCON, 0x00)   // BOR off

// --- setupRFPGM(parameter) ---
#define _DUAL_CHANNEL       0x03        // RFPGM dual channel receiving
#define _LP_MODE            0x04        // RFPGM low power mode receiving
#define _ENABLE_ON_RESET    0x10        // RFPGM invoking by reset
#define _TIME_TERMINATE     0x40        // RFPGM auto termination after ~1 min
#define _PIN_TERMINATE      0x80        // RFPGM termination by MCU pins

// --- external EEPROM & temperature sensor power control ---
#define eEEPROM_TempSensorOn()  _PWRT = 1
#define eEEPROM_TempSensorOff() _PWRT = 0

// --- Interrupt on change flags control ---
#define clearIOCF()     IOCBF.4 = 0                         // Clear interrupt on change flag.
#define clearIOCBN()    writeToRAM(&IOCBN, IOCBN & ~0x10)   // Clear negative edge flag. This bit (IOCBN.4) can not be accessed directly due to OS restriction.
#define setIOCBN()      writeToRAM(&IOCBN, IOCBN | 0x10)    // Negative edge active.

// --- FRC Response time ---
#define _FRC_RESPONSE_TIME_40_MS        0b0.000.0000  // 40 ms
#define _FRC_RESPONSE_TIME_360_MS       0b0.001.0000  // 360 ms
#define _FRC_RESPONSE_TIME_680_MS       0b0.010.0000  // 680 ms
#define _FRC_RESPONSE_TIME_1320_MS      0b0.011.0000  // 1320 ms
#define _FRC_RESPONSE_TIME_2600_MS      0b0.100.0000  // 2600 ms
#define _FRC_RESPONSE_TIME_5160_MS      0b0.101.0000  // 5160 ms
#define _FRC_RESPONSE_TIME_10280_MS     0b0.110.0000  // 10280 ms
#define _FRC_RESPONSE_TIME_20520_MS     0b0.111.0000  // 20520 ms

// --- FRC offline mode to set before sendFRC() is called ---
#define _FRC_OFFLINE_MODE               0b0000.1.000

// Only value ORed from the predefined constants ( FRC_RESPONSE_TIME_??? and/or _FRC_OFFLINE_MODE ) above can be used as a parameter "params"
#define setFRCparams( params ) \
  do { \
    configFRC &= ~( _FRC_RESPONSE_TIME_20520_MS | _FRC_OFFLINE_MODE ); \
    configFRC |= ( ( params ) & ( _FRC_RESPONSE_TIME_20520_MS | _FRC_OFFLINE_MODE ) ); \
  } while (0)

#define getFRCparams()          ( configFRC & ( _FRC_RESPONSE_TIME_20520_MS | _FRC_OFFLINE_MODE ) )

// --- Copy Application data from EEPROM to bufferINFO ---
#define appInfo()               eeReadData((__EEAPPINFO - __EESTART), 32)

// --- Write one byte to specified location in RAM ---
#define writeToRAM(address, value)  \
    do {                            \
        FSR0=address;               \
        setINDF0(value);            \
    } while(0)

// --- Macros relating to setFSRs() function ---
#define setFSR01(fsr0, fsr1)    setFSRs( (fsr0) + ( ((uns8)(fsr1)) << 4 ) )
#define setFSR0(fsr0)           setFSR01( fsr0, _FSR_NONE )
#define setFSR1(fsr1)           setFSR01( _FSR_NONE, fsr1 )

#define _FSR_NONE               0x00    // Set FSR to no buffer
#define _FSR_NINFO              0x01    // Set FSR to networkInfo
#define _FSR_INFO               0x02    // Set FSR to bufferINFO
#define _FSR_COM                0x03    // Set FSR to bufferCOM
#define _FSR_AUX                0x04    // Set FSR to bufferAUX
#define _FSR_RF                 0x05    // Set FSR to bufferRF
#define _FSR_ntwADDR            0x07    // Set FSR to ntwADDR (bank 11)

// --- Service channels ---
#define SERVICE_CHANNELS_COUNT  3

// --- LED control ---
#define toggleLEDR() \
#warning Do not combine direct access to the LEDs with calling the IQRF OS LED functions. \
do { _LEDR ^= 1; } while ( 0 )

#define toggleLEDG() \
#warning Do not combine direct access to the LEDs with calling the IQRF OS LED functions. \
do { _LEDG ^= 1; } while ( 0 )

// *********************************************************************
