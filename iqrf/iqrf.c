/**
 * Copyright IQRF Tech s.r.o.
 * Copyright 2020 Roman Ondráček <ondracek.roman@centrum.cz>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Default IQRF include (modify the path according to your setup)
#include "include/IQRF.h"

// Default DPA header (modify the path according to your setup)
#include "include/DPA.h"
// Default Custom DPA Handler header (modify the path according to your setup)
#include "include/DPAcustomHandler.h"
// IQRF standards header (modify the path according to your setup)
#include "include/IQRFstandard.h"
#include "include/IQRF_HWPID.h"

#if DPA_VERSION_MASTER < 0x0301
#error DPA version 3.01++ is required
#endif

// Custom bonding button. Change to the pin and an active level of your choice.
#define IsButton  (!PORTA.0)

// Number of implemented lights
#define LIGHTS_COUNT 0

// Number of implemented sensors
#define SENSORS_COUNT 4

// Variables to store sensor value at Get?_????() methods.
uns16 sensorValue @ param3;
uns16 sensorValueHighWord @ param4;

// Stores sensor value byte(s) to the FSR1[+1...], in case of PCMD_STD_SENSORS_READ_TYPES_AND_VALUES sensor type is stored before value byte(s)
void StoreValue(uns8 sensorType);

// FRC parameter
uns8  sensorIndexAndData;

// Reads sensor value to the sensorValue variable and to responseFRCvalue(2B,4B) variable(s) based on FRC command @ _PCMD
// Returns TRUE if the FRC is prepared
bit Get0_Temperature();
bit Get1_AdcVoltage();
bit Get2_InaVoltage();
bit Get3_InaCurrent();

// TX byte to UART
void TxUART(uns8 data);
// RX byte from UART; W = read byte, Carry = byte was read
bit RxUART();

// UART baud rate
#define UART_BAUD 115200

// Number of UART received bytes
uns8 RxDataLengthUART;

// Length of RX and TX buffers, must be power of 2
#define UART_BUFFER_LENGTH     16

#if 0 != (UART_BUFFER_LENGTH & (UART_BUFFER_LENGTH - 1))
#error UART_BUFFER_LENGTH is not power of 2
#endif

// Rx
// Circular RX UART buffer pointers
uns8 RxBufferPointerStartUART;
uns8 RxBufferPointerEndUART;
uns8 RxBufferUART[UART_BUFFER_LENGTH] /*@ PeripheralRam[0]*/;

// TX
// Circular TX UART buffer pointers
uns8 TxBufferPointerStartUART;
uns8 TxBufferPointerEndUART;
uns8 TxBufferUART[UART_BUFFER_LENGTH] /*@ PeripheralRam[UART_BUFFER_LENGTH]*/;
// TX data len
uns8 txDataLen;

// Division macro with rounding
#define DIV(Dividend,Divisor) (((Dividend+((Divisor)>>1))/(Divisor)))
// PIC baud register computation
#define UART_SPBRG_VALUE(Baud)  (DIV(F_OSC, (((uns24) 4) * (Baud))) - 1)

// Strings in internal EEPROM
#pragma cdata[__EESTART] = 'g', 'e', 't', 'A', 'd', 'c', 'V', 'o', 'l', 't', 'a', 'g', 'e', '\n'
#pragma cdata[__EESTART + 16] = 'g', 'e', 't', 'I', 'n', 'a', 'V', 'o', 'l', 't', 'a', 'g', 'e', '\n'
#pragma cdata[__EESTART + 32] = 'g', 'e', 't', 'C', 'u', 'r', 'r', 'e', 'n', 't', '\n'

// Must be the 1st defined function in the source code in order to be placed at the correct FLASH location!
bit CustomDpaHandler() {
    // This forces CC5X to wisely use MOVLB instructions (doc says:  The 'default' bank is used by the compiler for loops and labels when the algorithm gives up finding the optimal choice)
#pragma updateBank default = UserBank_01

    // Handler presence mark
    clrwdt();

    // TXIE state before sleep
    static bit wasTXIE;

    // Sleeping parameters, valid when Time != 0
    static TPerOSSleep_Request PerOSSleep_Request;

    // Detect DPA event to handle
    switch (GetDpaEvent()) {
        case DpaEvent_Interrupt:
            // Do an extra quick background interrupt work
            // ! The time spent handling this event is critical.If there is no interrupt to handle return immediately otherwise keep the code as fast as possible.
            // ! Make sure the event is the 1st case in the main switch statement at the handler routine.This ensures that the event is handled as the 1st one.
            // ! It is desirable that this event is handled with immediate return even if it is not used by the custom handler because the Interrupt event is raised on every MCU interrupt and the empty return handler ensures the shortest possible interrupt routine response time.
            // ! Only global variables or local ones marked by static keyword can be used to allow reentrancy.
            // ! Make sure race condition does not occur when accessing those variables at other places.
            // ! Make sure (inspect.lst file generated by C compiler ) compiler does not create any hidden temporary local variable (occurs when using division, multiplication or bit shifts ) at the event handler code.The name of such variable is usually Cnumbercnt.
            // ! Do not call any OS functions except setINDFx().
            // ! Do not use any OS variables especially for writing access.
            // ! All above rules apply also to any other function being called from the event handler code, although calling any function from Interrupt event is not recommended because of additional MCU stack usage.

            // UART Receive
            if (RCIF) {
                // We ignore FERR
                FSR1L = RCREG;
                // Put the received byte in circular buffer
                if (RxDataLengthUART < UART_BUFFER_LENGTH) {
                    // One more byte received
                    RxDataLengthUART++;
                    // Prepare pointer
                    FSR0 = RxBufferUART + RxBufferPointerEndUART;
                    // Recalculate tail pointer
                    // Optimization: Same as (UART_BUFFER_LENGTH is power of 2) : RxBufferPointerEndUART = (RxBufferPointerEndUART + 1) % UART_BUFFER_LENGTH;
                    RxBufferPointerEndUART++;
                    RxBufferPointerEndUART &= ~UART_BUFFER_LENGTH;
                    // Store byte
                    setINDF0(FSR1L);
                }
            }

            // Overrun recovery (we do it after receiving UART byte in order to receive it as soon as possible)
            if (OERR) {
                CREN = 0;
            }

            // Seems excess, but at the end it is shorted and faster than having this statement at else branch
            CREN = 1;

            // UART Transmit
            if (TXIF && TXIE) {
                // Send byte from circular buffer to the UART
                FSR0 = TxBufferUART + TxBufferPointerStartUART;
                TxBufferPointerStartUART = (TxBufferPointerStartUART + 1) % UART_BUFFER_LENGTH;
                // Buffer empty?
                if (TxBufferPointerStartUART == TxBufferPointerEndUART) {
                    TXIE = FALSE;
                }
                // TX the byte
                TXREG = *FSR0;
            }

            // Return value does not matter
            return Carry;
        case DpaEvent_BondingButton:
            // Called to allow a bonding button customization
            userReg1.0 = 0;
            if (IsButton) {
                userReg1.0 = 1;
            }
            return TRUE;
        case DpaEvent_DpaRequest:
            // Called to interpret DPA request for peripherals
            // Peripheral enumeration
            if(IsDpaEnumPeripheralsRequest()) {
                // We implement 1 standard peripheral
                _DpaMessage.EnumPeripheralsAnswer.UserPerNr = 2;
                FlagUserPer(_DpaMessage.EnumPeripheralsAnswer.UserPer, PNUM_STD_SENSORS);
                FlagUserPer(_DpaMessage.EnumPeripheralsAnswer.UserPer, PNUM_STD_LIGHT);
                _DpaMessage.EnumPeripheralsAnswer.HWPID = 0x123F;
                _DpaMessage.EnumPeripheralsAnswer.HWPIDver = 0x0001;
                return TRUE;
            }
            // Get information about peripheral
            if (IsDpaPeripheralInfoRequest()) {
                if (_PNUM == PNUM_STD_SENSORS) {
                    _DpaMessage.PeripheralInfoAnswer.PerT = PERIPHERAL_TYPE_STD_SENSORS;
                    _DpaMessage.PeripheralInfoAnswer.PerTE = PERIPHERAL_TYPE_EXTENDED_READ_WRITE;
                    // Set standard version
                    _DpaMessage.PeripheralInfoAnswer.Par1 = STD_SENSORS_VERSION;
                    return TRUE;
                }
                if (_PNUM == PNUM_STD_LIGHT) {
                    _DpaMessage.PeripheralInfoAnswer.PerT = PERIPHERAL_TYPE_STD_LIGHT;
                    _DpaMessage.PeripheralInfoAnswer.PerTE = PERIPHERAL_TYPE_EXTENDED_READ_WRITE;
                    // Set standard version
                    _DpaMessage.PeripheralInfoAnswer.Par1 = STD_LIGHT_VERSION;
                    return TRUE;
                }
                break;
            } else {
                // Handle peripheral command
                // Supported peripheral number?
                if (_PNUM == PNUM_STD_SENSORS) {
                    // Supported commands?
                    switch (_PCMD) {
                        default:
                            // Invalid command; Return error
                            DpaApiReturnPeripheralError(ERROR_PCMD);
                        case PCMD_STD_ENUMERATE:
                            // Sensor enumeration
                            if (_DpaDataLength != 0) {
                                DpaApiReturnPeripheralError(ERROR_DATA_LEN);
                                break;
                            }
                            _DpaMessage.Response.PData[0] = STD_SENSOR_TYPE_TEMPERATURE;
                            _DpaMessage.Response.PData[1] = STD_SENSOR_TYPE_EXTRA_LOW_VOLTAGE;
                            _DpaMessage.Response.PData[2] = STD_SENSOR_TYPE_EXTRA_LOW_VOLTAGE;
                            _DpaMessage.Response.PData[3] = STD_SENSOR_TYPE_CURRENT;
                            _DpaDataLength = SENSORS_COUNT;
                            return TRUE;
                        case PCMD_STD_SENSORS_READ_VALUES:
                        case PCMD_STD_SENSORS_READ_TYPES_AND_VALUES: {
                            // No sensor bitmap specified? W = _DpaDataLength. Note: W is used to avoid MOVLB at next if
                            W = _DpaDataLength;
                            // Note: must not modify W
                            if (W == 0) {
                                // Actually clears the bitmap
#if &_DpaMessage.Request.PData[0] != &bufferRF[0]
#error
#endif
                                clearBufferRF();
                                // Simulate 1st only sensor in the bitmap (states of the other unimplemented sensors do not care)
                                _DpaMessage.Request.PData[0].0 = 1;
                                // Bitmap is 32 bits long = 4
                                _DpaDataLength = W = sizeof(_DpaMessageIqrfStd.PerStdSensorRead_Request.Bitmap);
                            }
                            // Invalid bitmap (data) length (W = _DpaDataLength)?
                            if (W != sizeof(_DpaMessageIqrfStd.PerStdSensorRead_Request.Bitmap)) {
                                // Return error
                                DpaApiReturnPeripheralError(ERROR_DATA_LEN);
                            }

                            // Now read the sensors

                            // Prepare pointer (minus 1, see below) to store sensor (types and) values to
                            FSR1 = &_DpaMessage.Response.PData[-1];

                            // Store bitmap of sensors to get values from
                            uns8 sensorsBitmap = FSR1[1];

                            // 1st sensor (index 0) selected?
                            if (sensorsBitmap.0) {
                                Get0_Temperature();
                                StoreValue(STD_SENSOR_TYPE_TEMPERATURE);
                            }
                            // 2nd sensor (index 1) selected?
                            if (sensorsBitmap.1) {
                                Get1_AdcVoltage();
                                StoreValue(STD_SENSOR_TYPE_EXTRA_LOW_VOLTAGE);
                            }
                            // 3rd sensor (index 2) selected?
                            if (sensorsBitmap.2) {
                                Get2_InaVoltage();
                                StoreValue(STD_SENSOR_TYPE_EXTRA_LOW_VOLTAGE);
                            }
                            // 4th sensor (index 3) selected?
                            if (sensorsBitmap.3) {
                                Get3_InaCurrent();
                                StoreValue(STD_SENSOR_TYPE_CURRENT);
                            }
                            // Compute returned data bytes count
                            W = FSR1L - ((uns16) &_DpaMessage.Response.PData[0] & 0xFF) + 1;
                            _DpaDataLength = W;
                            return TRUE;
                        }
                    }
                } else if (_PNUM == PNUM_STD_LIGHT) {
                    // Supported commands?
                    switch (_PCMD) {
                        default:
                            // Invalid command; Return error
                            DpaApiReturnPeripheralError(ERROR_PCMD);
                        case PCMD_STD_ENUMERATE:
                            // Light enumeration
                            if (_DpaDataLength != 0) {
                                DpaApiReturnPeripheralError(ERROR_DATA_LEN);
                                break;
                            }
                            // Return just count of lights
                            // Optimization = 1 (_DpaDataLength was zero for sure)
                            _DpaDataLength |= 1;
                            _DpaMessage.Request.PData[0] = LIGHTS_COUNT;
                            return TRUE;

                            // Supported commands.
                        case PCMD_STD_LIGHT_SET:
                        case PCMD_STD_LIGHT_INC:
                        case PCMD_STD_LIGHT_DEC: {
                            DpaApiReturnPeripheralError(ERROR_PCMD);
                            return TRUE;
                        }
                    }
                }
                break;
            }

        case DpaEvent_Init:
            // Do a one time initialization before main loop starts
            moduleInfo();
            if (!bufferINFO[5].7) {
                // Set them as inputs
                TRISC.5 = 1;
                TRISA.5 = 1;
                TRISB.4 = 1;
            }

            // RX input
            TRISC.7 = 1;
            // TX output
            TRISC.6 = 0;

            // Set baud rate
            SPBRGL = UART_SPBRG_VALUE(UART_BAUD) & 0xff;
            SPBRGH = UART_SPBRG_VALUE(UART_BAUD) >> 8;
            // baud rate control setup: BRG16 = 1
            BAUDCON = 0b0000.1.000;

            // CSRC TX9 TXEN SYNC SENDB BRGH TRMT TX9D
            // TXEN = 1
            // BRGH = 1
            // async UART, high speed, 8 bit, TX enabled
            TXSTA = 0b0010.0100;

            // SPEN RX9 SREN CREN ADDEN FERR OERR RX9D
            // SPEN = 1
            // CREN = 1
            // Continuous receive, enable port, 8 bit
            RCSTA = 0b1001.0000;
            // Enable UART RX interrupt
            RCIE = TRUE;
            txDataLen = 0;
            break;
        case DpaEvent_AfterSleep:
            // Called after woken up after sleep
            TXIE = wasTXIE;
            RCIE = TRUE;
            break;
        case DpaEvent_BeforeSleep:
            // Called before going to sleep
        case DpaEvent_DisableInterrupts:
            // Called when device needs all hardware interrupts to be disabled (before Reset, Restart, LoadCode, Remove bond, and Run RFPGM)
            wasTXIE = TXIE;
            TXIE = FALSE;
            RCIE = FALSE;
            break;
        case DpaEvent_FrcValue:
            // Called to get FRC value

            // FSR1 for optimization purposes (avoid MOVLB) will be used to point to DataOutBeforeResponseFRC[0...]
            FSR1 = &DataOutBeforeResponseFRC[0];

            // Check for correct FRC user data
            if (*FSR1++ == PNUM_STD_LIGHT) {
                // Check for the correct light index and prepare pointer to the power array
                uns8 index = DataOutBeforeResponseFRC[1] & 0x1F;
                if (index < LIGHTS_COUNT) {
                    // Check for FRC command
                    switch (_PCMD) {
                        case FRC_STD_LIGHT_ONOFF:
                            responseFRCvalue.1 = 1;
                            // Is the light off?
                            if (FSR0[0] == 0) {
                                responseFRCvalue.0 = 0;
                            }
                            break;

                        case FRC_STD_LIGHT_ALARM:
                            // !EXAMPLE! in this example return alarm if the light power is 100 %
                            responseFRCvalue.1 = 1;
                            if (FSR0[0] != 100) {
                                responseFRCvalue.0 = 0;
                            }
                            break;
                    }
                }
            }
            if (*FSR1 == PNUM_STD_SENSORS) {
                // Data and index
                sensorIndexAndData = FSR1[1];
                // Actually used sensor index
                uns8 sensorIndex = FSR1[1] & 0x1f;
                // Test sensor type
                switch (*FSR1++) {
                    default:
                        return FALSE;
                        // No type specified, use specified index value
                    case 0x00:
                        goto _KeepSensorIndex;
                        // For other types make the index value based on the requested index value and sensor type
                    case STD_SENSOR_TYPE_TEMPERATURE:
                        if (sensorIndex > 0) {
                            return FALSE;
                        }
                        W = 0;
                        break;
                }
                // New sensor index based on type and requested index
                sensorIndex = W;
                _KeepSensorIndex:
                // Test for supported FRC commands
                switch (_PCMD) {
                    default:
                        return FALSE;
                    case FRC_STD_SENSORS_BIT:
                    case FRC_STD_SENSORS_1B:
                    case FRC_STD_SENSORS_2B:
                    case FRC_STD_SENSORS_4B:
                        switch (sensorIndex) {
                            default:
                                return FALSE;
                            case 0:
                                Carry = Get0_Temperature();
                                break;
                        }
                        // This type of FRC is not valid for the specified sensor
                        if (!Carry) {
                            return FALSE;
                        }
                        break;
                }

                // Some sensor was measured by FRC, check if there is a sleep request
                FSR1++;
                // Note: same as DataOutBeforeResponseFRC[3].0
                if (INDF1.0) {
                    // Remember sleep parameters to go to sleep at the Idle event later
                    PerOSSleep_Request.Time.low8 = FSR1[4 - 3]; // Note: same as DataOutBeforeResponseFRC[4];
                    PerOSSleep_Request.Time.high8 = FSR1[5 - 3]; // Note: same as DataOutBeforeResponseFRC[5];
                    PerOSSleep_Request.Control = FSR1[6 - 3]; // Note: same as DataOutBeforeResponseFRC[6];
                }
            }
            return FALSE;

        case DpaEvent_FrcResponseTime:
            // Called to get FRC response time

            // In this example the FRC commands are fast
            switch (DataOutBeforeResponseFRC[0]) {
                case FRC_STD_SENSORS_BIT:
                case FRC_STD_SENSORS_1B:
                case FRC_STD_SENSORS_2B:
                case FRC_STD_SENSORS_4B:
                    //case FRC_STD_LIGHT_ONOFF:
                case FRC_STD_LIGHT_ALARM:
                    responseFRCvalue = _FRC_RESPONSE_TIME_40_MS;
                    break;
            }
            break;

    }
    return FALSE;
}

/**
 * Increases FSR1 and then stores the byte
 */
void setPlusPlusINDF1(uns8 data @ W) {
    FSR1++; // Note: must not modify W
    setINDF1(data);
}

/**
 * Stores measured sensor value byte(s) and optionally sensor type to the FSR[+1...]
 */
void StoreValue(uns8 sensorType) {
    // Is the sensor type to be stored too?
    if (_PCMD == PCMD_STD_SENSORS_READ_TYPES_AND_VALUES) {
        setPlusPlusINDF1(sensorType);
    }
    // Store lower value byte (or length in case of multiple bytes)
    setPlusPlusINDF1(sensorValue.low8);
    // 2 bytes?
    if (sensorType.7 == 0) {
        // Store higher value byte
        setPlusPlusINDF1(sensorValue.high8);
        return;
    }
    // 4 bytes?
    if ((sensorType & 0b1110.0000) == 0b1010.0000) {
        setPlusPlusINDF1(sensorValue.high8);
        setPlusPlusINDF1(sensorValueHighWord.low8);
        setPlusPlusINDF1(sensorValueHighWord.high8);
        return;
    }
    // Multiple bytes?
    if ((sensorType & 0b1100.0000) == 0b1100.0000) {
        // Data is expected at bufferINFO, length at sensorValue.low8
        setFSR0(_FSR_INFO);
        do {
            // Store all data
            setPlusPlusINDF1(*FSR0++);
        } while (--sensorValue.low8 != 0);
        return;
    }
}

bit setFRCerror() {
#ifndef __CC5XFREE__
    responseFRCvalue4B = FRC_STD_FRC_ERROR_VALUE;
#else
    responseFRCvalue4B.low16 = FRC_STD_FRC_ERROR_VALUE;
    responseFRCvalue4B.high16 = 0;
#endif
    return TRUE;
}

/**
 * Sensor index 0: measure temperature using the TR sensor
 */
bit Get0_Temperature() {
    // Make sure FSR1 is not modified
    // Measure temperature using TR sensor
    bit sensorError = FALSE;
    // When error, then adjust the standard error values
    if (getTemperature() == -128) {
        sensorError = TRUE;
        STD_SENSOR_TYPE_TEMPERATURE_SET_ERROR(param3);
    }
    // Return sensor value
    sensorValue = param3;
    // Test for supported FRC commands
    switch (_PCMD) {
        default:
            return FALSE;
        case FRC_STD_SENSORS_1B:
            // Return sensor FRC value 1B
            // Check for out of limits
            if (sensorError || (int16) sensorValue > (int16) (105.5 * 16) || (int16) sensorValue < ((int16) -20 * 16)) {
                return setFRCerror();
            }

            // Convert to the "F = (T + 22) * 2" from 1/16 resolution
            responseFRCvalue2B = sensorValue + 4; // Note: do rounding when /8
            responseFRCvalue2B /= 8;
            responseFRCvalue += 44;
            break;
        case FRC_STD_SENSORS_2B:
            // Return sensor FRC value 2B
            if (sensorError) {
                return setFRCerror();
            }
            responseFRCvalue2B = sensorValue ^ 0x8000;
            break;
    }
    return TRUE;
}

/**
 * Sensor index 1: input voltage measured by ADC
 */
bit Get1_AdcVoltage() {
    while(txDataLen);
    txDataLen = 14;
    uns16 fsr1Backup = FSR1;
    eeReadData(0, txDataLen);
    setFSR1(_FSR_INFO);
    do {
        TxUART(*FSR1++);
    } while (--txDataLen != 0);
    RxUART();
    sensorValue.high8 = W;
    RxUART();
    sensorValue.low8 = W;
    FSR1 = fsr1Backup;
    switch (_PCMD) {
        default:
            return FALSE;
        case FRC_STD_SENSORS_1B:
            // Return sensor FRC value 1B
            // Check for out of limits
            if (sensorValue > 4095) {
                return setFRCerror();
            }
            responseFRCvalue = sensorValue / 256;
            break;
        case FRC_STD_SENSORS_2B:
            responseFRCvalue2B = sensorValue;
            break;
    }
    return TRUE;
}

/**
 * Sensor index 2: input voltage measured by INA219
 */
bit Get2_InaVoltage() {
    while(txDataLen);
    txDataLen = 14;
    uns16 fsr1Backup = FSR1;
    eeReadData(16, txDataLen);
    setFSR1(_FSR_INFO);
    do {
        TxUART(*FSR1++);
    } while (--txDataLen != 0);
    RxUART();
    sensorValue.high8 = W;
    RxUART();
    sensorValue.low8 = W;
    FSR1 = fsr1Backup;
    switch (_PCMD) {
        default:
            return FALSE;
        case FRC_STD_SENSORS_1B:
            // Return sensor FRC value 1B
            // Check for out of limits
            if (sensorValue > 4095) {
                return setFRCerror();
            }
            responseFRCvalue = sensorValue / 256;
            break;
        case FRC_STD_SENSORS_2B:
            responseFRCvalue2B = sensorValue;
            break;
    }
    return TRUE;
}

/**
 * Sensor index 3: current measured by INA219
 */
bit Get3_InaCurrent() {
    while(txDataLen);
    txDataLen = 11;
    uns16 fsr1Backup = FSR1;
    eeReadData(32, txDataLen);
    setFSR1(_FSR_INFO);
    do {
        TxUART(*FSR1++);
    } while (--txDataLen != 0);
    RxUART();
    sensorValue.high8 = W;
    RxUART();
    sensorValue.low8 = W;
    FSR1 = fsr1Backup;
    switch (_PCMD) {
        default:
            return FALSE;
        case FRC_STD_SENSORS_1B:
            // Return sensor FRC value 1B
            // Check for out of limits
            if (sensorValue > 4095) {
                return setFRCerror();
            }
            responseFRCvalue = sensorValue / 256;
            break;
        case FRC_STD_SENSORS_2B:
            responseFRCvalue2B = sensorValue;
            break;
    }
    return TRUE;
}

// Note: make sure the parameter does not overlap another variable as the function is ready to be called from (timer) interrupt too
static uns8 _data;
void TxUART(uns8 data @ _data) {
    // Wait for a space in the buffer
    while (TXIE && TxBufferPointerStartUART == TxBufferPointerEndUART);

    // Disable TX interrupt
    TXIE = FALSE;
    // Compute pointer
    FSR0 = TxBufferUART + TxBufferPointerEndUART;
    // Optimization: TxBufferPointerEndUART = (TxBufferPointerEndUART + 1) % UART_BUFFER_LENGTH;
    TxBufferPointerEndUART++;
    TxBufferPointerEndUART &= ~UART_BUFFER_LENGTH;
    // Store byte
    setINDF0(_data);
    // Start transmitting
    TXIE = TRUE;
}

// W = read byte, Carry = result
bit RxUART() {
    // Buffer empty?
    if (RxDataLengthUART == 0) {
        return FALSE;
    }
    // Disable RX interrupt
    RCIE = FALSE;
    // Get byte from the circular buffer
    FSR0 = RxBufferUART + RxBufferPointerStartUART;
    // Optimization: RxBufferPointerStartUART = (RxBufferPointerStartUART + 1) % UART_BUFFER_LENGTH;
    RxBufferPointerStartUART++;
    RxBufferPointerStartUART &= ~UART_BUFFER_LENGTH;
    // One byte less
    RxDataLengthUART--;
    // Returned byte
    W = *FSR0;
    // Enable RX interrupt
    RCIE = TRUE;
    // TRUE => byte was read
    return TRUE;
}

// Default Custom DPA Handler header; 2nd include to implement Code bumper to detect too long code of the Custom DPA Handler (modify the path according to your setup)
#include "include/DPAcustomHandler.h"