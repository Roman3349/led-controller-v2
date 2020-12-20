// *********************************************************************
//   IQRF standards header file                                        *
// *********************************************************************
// Copyright (c) IQRF Tech s.r.o.
//
// File:    $RCSfile: IQRFstandard.h,v $
// Version: $Revision: 1.68 $
// Date:    $Date: 2020/09/03 15:37:13 $
//
// Revision history:
//   2020/09/03  Release for DPA 4.15
//   2020/04/03  Release for DPA 4.14
//   2020/02/27  Release for DPA 4.13
//   2020/01/09  Release for DPA 4.12
//   2019/12/11  Release for DPA 4.11
//   2019/10/09  Release for DPA 4.10
//   2019/06/12  Release for DPA 4.03
//   2019/06/03  Release for DPA 4.02
//   2019/03/07  Release for DPA 4.01
//   2019/01/20  Release for DPA 4.00
//   2018/10/25  Release for DPA 3.03
//   2017/11/16  Release for DPA 3.02
//   2017/08/14  Release for DPA 3.01
//
// *********************************************************************

// Online DPA documentation https://doc.iqrf.org/DpaTechGuide/
// IQRF Standards documentation https://www.iqrfalliance.org/iqrf-interoperability/

#ifndef _IQRFSTD_HEADER_
#define _IQRFSTD_HEADER_

//############################################################################################

// Enumerate command valid for standards, when applicable
#define	PCMD_STD_ENUMERATE						0x3E

#define	FRC_STD_FRC_NO_VALUE                    0
#define	FRC_STD_FRC_NOT_IMPLEMENTED_VALUE       1
#define	FRC_STD_FRC_ERROR_VALUE                 2

// -------------------------------------------------------------------------------------------
// IQRF Sensors standard
// -------------------------------------------------------------------------------------------
// IQRF Sensors standard peripheral
#define PNUM_STD_SENSORS						0x5E
// IQRF Sensors standard peripheral type
#define PERIPHERAL_TYPE_STD_SENSORS				0x5E
// Current version
#define STD_SENSORS_VERSION                     15

// IQRF Sensors standard peripheral - read sensor values command
#define PCMD_STD_SENSORS_READ_VALUES			0x00
// IQRF Sensors standard peripheral - read sensor types and values command
#define PCMD_STD_SENSORS_READ_TYPES_AND_VALUES	0x01

// Beaming sensor command
#define PCMD_STD_SENSORS_READ_TYPES_AND_FRC_VALUES  0x7B


// IQRF Sensors standard peripheral - sensor types
//  2 bytes
#define	STD_SENSOR_TYPE_TEMPERATURE				0x01
#define	STD_SENSOR_TYPE_CO2						0x02
#define	STD_SENSOR_TYPE_VOC						0x03
#define	STD_SENSOR_TYPE_EXTRA_LOW_VOLTAGE		0x04
#define	STD_SENSOR_TYPE_EARTHS_MAGNETIC_FIELD	0x05
#define	STD_SENSOR_TYPE_LOW_VOLTAGE				0x06
#define	STD_SENSOR_TYPE_CURRENT					0x07
#define	STD_SENSOR_TYPE_POWER					0x08
#define	STD_SENSOR_TYPE_MAINS_FREQUENCY			0x09
#define	STD_SENSOR_TYPE_TIMESPAN    			0x0A
#define	STD_SENSOR_TYPE_ILLUMINANCE	    		0x0B
#define	STD_SENSOR_TYPE_NO2         			0x0C
#define	STD_SENSOR_TYPE_SO2         			0x0D
#define	STD_SENSOR_TYPE_CO          			0x0E
#define	STD_SENSOR_TYPE_O3          			0x0F
#define	STD_SENSOR_TYPE_ATMOSPHERIC_PRESSURE	0x10
#define	STD_SENSOR_TYPE_COLOR_TEMPERATURE   	0x11
#define	STD_SENSOR_TYPE_PARTICULATES_PM25      	0x12
#define	STD_SENSOR_TYPE_SOUND_PRESSURE_LEVEL    0x13
#define	STD_SENSOR_TYPE_ALTITUDE                0x14
#define	STD_SENSOR_TYPE_ACCELERATION            0x15
#define	STD_SENSOR_TYPE_NH3                     0x16
#define	STD_SENSOR_TYPE_METHANE                 0x17
#define	STD_SENSOR_TYPE_SHORT_LENGTH            0x18
#define	STD_SENSOR_TYPE_PARTICULATES_PM1      	0x19
#define	STD_SENSOR_TYPE_PARTICULATES_PM4      	0x1A
#define	STD_SENSOR_TYPE_PARTICULATES_PM10      	0x1B

//  1 byte
#define	STD_SENSOR_TYPE_HUMIDITY				0x80
#define	STD_SENSOR_TYPE_BINARYDATA7				0x81
#define	STD_SENSOR_TYPE_POWER_FACTOR			0x82
#define	STD_SENSOR_TYPE_UV_INDEX                0x83
#define	STD_SENSOR_TYPE_PH                      0x84

//  4 bytes
#define	STD_SENSOR_TYPE_BINARYDATA30			0xA0
#define	STD_SENSOR_TYPE_CONSUMPTION				0xA1
#define	STD_SENSOR_TYPE_DATETIME				0xA2
#define	STD_SENSOR_TYPE_TIMESPAN_LONG  			0xA3
#define	STD_SENSOR_TYPE_LATITUDE      			0xA4
#define	STD_SENSOR_TYPE_LONGITUDE   			0xA5

// Computes constant (otherwise not optimal) quantity size
#define STD_SENSOR_TYPE_SIZE(q) ( ( ( (q) & 0x80 ) == 0x00 ) * 2 + ( ( (q) & 0xE0 ) == 0x80 ) * 1 + ( ( (q) & 0xE0 ) == 0xA0 ) * 4  + ( ( q & 0xC0 ) == 0xC0 || (q) == 0x00 ) * 0xFfFfFfFf /* hopefully causes overflow to signal error */ )

//  Multiple bytes
#define	STD_SENSOR_TYPE_DATA_BLOCK			    0xC0

// IQRF Sensors standard peripheral - FRC commands
#define	FRC_STD_SENSORS_BIT						0x10
#define	FRC_STD_SENSORS_1B						0x90
#define	FRC_STD_SENSORS_2B						0xE0
#define	FRC_STD_SENSORS_4B						0xF9

typedef struct
{
  // Equals to PNUM_STD_SENSORS
  uns8  Header;
  // Sensor type STD_SENSOR_TYPE_???
  uns8  SensorType;
  // Sensor index (bits 0-4) + optional extended data (bits 5-7)
  uns8  SensorIndex;
  // Options
  // bit  0  : sleep
  // bits 1-7: reserved
  uns8  Options;
  // Optional sleep parameters
  TPerOSSleep_Request SleepParameters;
} STRUCTATTR TPerStdSensorFrc;


#if defined( __CC5X__ ) && !defined( CC5XnotDPA )
// The above structure located at memory
TPerStdSensorFrc PerStdSensorFrc @ DataOutBeforeResponseFRC;
#endif  // #ifdef __CC5X__

// Structure for PCMD_STD_SENSORS_READ[_TYPES_AND]_VALUES
typedef struct
{
  uns8	Bitmap[4];
  uns8	WrittenData[DPA_MAX_DATA_LENGTH - 4];
} STRUCTATTR TPerStdSensorRead_Request;

// IQRF Sensors standard peripheral - error values
//  2 bytes
#define	STD_SENSOR_TYPE_TEMPERATURE_SET_ERROR(v)            do { v = 0x8000; } while( 0 )
#define	STD_SENSOR_TYPE_TEMPERATURE_IS_ERROR(v)             ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_CO2_SET_ERROR(v)                    do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_CO2_IS_ERROR(v)                     ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_VOC_SET_ERROR(v)                    do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_VOC_IS_ERROR(v)                     ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_EXTRA_LOW_VOLTAGE_SET_ERROR(v)      do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_EXTRA_LOW_VOLTAGE_IS_ERROR(v)       ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_EARTHS_MAGNETIC_FIELD_SET_ERROR(v)  do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_EARTHS_MAGNETIC_FIELD_IS_ERROR(v)   ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_LOW_VOLTAGE_SET_ERROR(v)            do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_LOW_VOLTAGE_IS_ERROR(v)             ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_CURRENT_SET_ERROR(v)                do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_CURRENT_IS_ERROR(v)                 ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_POWER_SET_ERROR(v)                  do { v = 0xFfFf; } while( 0 )
#define STD_SENSOR_TYPE_POWER_IS_ERROR(v)                   ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_MAINS_FREQUENCY_SET_ERROR(v)        do { v = 0xFfFf; } while( 0 )
#define STD_SENSOR_TYPE_MAINS_FREQUENCY_IS_ERROR(v)         ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_TIMESPAN_SET_ERROR(v)               do { v = 0xFfFf; } while( 0 )
#define STD_SENSOR_TYPE_TIMESPAN_IS_ERROR(v)                ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_ILLUMINANCE_SET_ERROR(v)            do { v = 0xFfFf; } while( 0 )
#define STD_SENSOR_TYPE_ILLUMINANCE_IS_ERROR(v)             ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_NO2_SET_ERROR(v)                    do { v = 0xFfFf; } while( 0 )
#define STD_SENSOR_TYPE_NO2_IS_ERROR(v)                     ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_SO2_SET_ERROR(v)                    do { v = 0xFfFf; } while( 0 )
#define STD_SENSOR_TYPE_SO2_IS_ERROR(v)                     ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_CO_SET_ERROR(v)                     do { v = 0xFfFf; } while( 0 )
#define STD_SENSOR_TYPE_CO_IS_ERROR(v)                      ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_O3_SET_ERROR(v)                     do { v = 0xFfFf; } while( 0 )
#define STD_SENSOR_TYPE_O3_IS_ERROR(v)                      ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_ATMOSPHERIC_PRESSURE_SET_ERROR(v)   do { v = 0xFfFf; } while( 0 )
#define STD_SENSOR_TYPE_ATMOSPHERIC_PRESSURE_IS_ERROR(v)    ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_COLOR_TEMPERATURE_SET_ERROR(v)      do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_COLOR_TEMPERATURE_IS_ERROR(v)       ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_PARTICULATES_PM25_SET_ERROR(v)      do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_PARTICULATES_PM25_IS_ERROR(v)       ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_SOUND_PRESSURE_LEVEL_SET_ERROR(v)   do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_SOUND_PRESSURE_LEVEL_IS_ERROR(v)    ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_ALTITUDE_SET_ERROR(v)               do { v = 0xFfFf; } while( 0 )
#define STD_SENSOR_TYPE_ALTITUDE_IS_ERROR(v)                ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_ACCELERATION_SET_ERROR(v)           do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_ACCELERATION_IS_ERROR(v)            ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_NH3_SET_ERROR(v)                    do { v = 0xFfFf; } while( 0 )
#define	STD_SENSOR_TYPE_NH3_IS_ERROR(v)                     ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_METHANE_SET_ERROR(v)                do { v = 0xFfFf; } while( 0 )
#define	STD_SENSOR_TYPE_METHANE_IS_ERROR(v)                 ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_SHORT_LENGTH_SET_ERROR(v)           do { v = 0xFfFf; } while( 0 )
#define	STD_SENSOR_TYPE_SHORT_LENGTH_IS_ERROR(v)            ( (v) == 0xFfFf )

#define	STD_SENSOR_TYPE_PARTICULATES_PM1_SET_ERROR(v)       do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_PARTICULATES_PM1_IS_ERROR(v)        ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_PARTICULATES_PM4_SET_ERROR(v)       do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_PARTICULATES_PM4_IS_ERROR(v)        ( (v) == 0x8000 )

#define	STD_SENSOR_TYPE_PARTICULATES_PM10_SET_ERROR(v)      do { v = 0x8000; } while( 0 )
#define STD_SENSOR_TYPE_PARTICULATES_PM10_IS_ERROR(v)       ( (v) == 0x8000 )

//  1 byte
#define	STD_SENSOR_TYPE_HUMIDITY_SET_ERROR(v)               do { v = 0xEE; } while( 0 )
#define STD_SENSOR_TYPE_HUMIDITY_IS_ERROR(v)                ( (v) == 0xEE )

#define	STD_SENSOR_TYPE_BINARYDATA7_SET_ERROR(v)            do { v = 0x80; } while( 0 )
#define STD_SENSOR_TYPE_BINARYDATA7_IS_ERROR(v)             ( ( (v) & 0x80 ) != 0x00 )

#define	STD_SENSOR_TYPE_POWER_FACTOR_SET_ERROR(v)           do { v = 0xEE; } while( 0 )
#define STD_SENSOR_TYPE_POWER_FACTOR_IS_ERROR(v)            ( (v) == 0xEE )

#define	STD_SENSOR_TYPE_UV_INDEX_SET_ERROR(v)               do { v = 0xFF; } while( 0 )
#define STD_SENSOR_TYPE_UV_INDEX_IS_ERROR(v)                ( (v) == 0xFF )

#define	STD_SENSOR_TYPE_PH_INDEX_SET_ERROR(v)               do { v = 0xFF; } while( 0 )
#define STD_SENSOR_TYPE_PH_INDEX_IS_ERROR(v)                ( (v) == 0xFF )


//  4 bytes
#define	STD_SENSOR_TYPE_BINARYDATA30_SET_ERROR(v)           do { v = 0x80000000; } while( 0 )
#define STD_SENSOR_TYPE_BINARYDATA30_IS_ERROR(v)            ( ( (v) & 0x80000000 ) != 0x00000000 )

#define	STD_SENSOR_TYPE_CONSUMPTION_SET_ERROR(v)            do { v = 0xFfFfFfFf; } while( 0 )
#define STD_SENSOR_TYPE_CONSUMPTION_IS_ERROR(v)             ( (v) == 0xFfFfFfFf )

#define	STD_SENSOR_TYPE_DATETIME_SET_ERROR(v)               do { v = 0xFfFfFfFf; } while( 0 )
#define STD_SENSOR_TYPE_DATETIME_IS_ERROR(v)                ( (v) == 0xFfFfFfFf )

#define	STD_SENSOR_TYPE_TIMESPAN_LONG_SET_ERROR(v)          do { v = 0xFfFfFfFf; } while( 0 )
#define STD_SENSOR_TYPE_TIMESPAN_LONG_IS_ERROR(v)           ( (v) == 0xFfFfFfFf )

#define	STD_SENSOR_TYPE_LATITUDE_SET_ERROR(v)               do { v = 0xFF000000; } while( 0 )
#define STD_SENSOR_TYPE_LATITUDE_IS_ERROR(v)                ( ( (v) & 0xFF000000 ) == 0xFF000000 )

#define	STD_SENSOR_TYPE_LONGITUDE_SET_ERROR(v)              do { v = 0xFF000000; } while( 0 )
#define STD_SENSOR_TYPE_LONGITUDE_IS_ERROR(v)               ( ( (v) & 0xFF000000 ) == 0xFF000000 )

//  Written data constants
#define STD_SENSOR_TYPE_TEMPERATURE_DATA_GET_1_POINT_CALIBRATION  1
#define STD_SENSOR_TYPE_TEMPERATURE_DATA_SET_1_POINT_CALIBRATION  2

#define STD_SENSOR_TYPE_HUMIDITY_DATA_GET_1_POINT_CALIBRATION  1
#define STD_SENSOR_TYPE_HUMIDITY_DATA_SET_1_POINT_CALIBRATION  2

// -------------------------------------------------------------------------------------------
// IQRF Binary Outputs standard
// -------------------------------------------------------------------------------------------
// IQRF Binary Outputs standard peripheral
#define	PNUM_STD_BINARY_OUTPUTS					0x4B
// IQRF Binary Outputs peripheral type
#define	PERIPHERAL_TYPE_STD_BINARY_OUTPUTS		0x4B
// Current version
#define STD_BINARY_OUTPUTS_VERSION              4

// IQRF Binary Outputs standard peripheral - set outputs
#define	PCMD_STD_BINARY_OUTPUTS_SET				0x00

// Structure returned by PCMD_STD_ENUMERATE
typedef struct
{
  uns8	Count;
} STRUCTATTR TPerStdBinaryOutputEnumerate_Response;

// Structure for PCMD_STD_BINARY_OUTPUTS_SET
typedef struct
{
  uns8	Bitmap[4];
  uns8	NewState[DPA_MAX_DATA_LENGTH - 4];
} STRUCTATTR TPerStdBinaryOutputSet_Request;

#define STD_BINARY_OUTPUT_STATE_OFF                    0x00
#define STD_BINARY_OUTPUT_STATE_ON                     0x01

#define STD_BINARY_OUTPUT_IS_STATE_OK(state)           ( (state) != 0x80 )
#define STD_BINARY_OUTPUT_IS_STATE_OFF(state)          ( (state) == STD_BINARY_OUTPUT_STATE_OFF )
#define STD_BINARY_OUTPUT_IS_STATE_ON(state)           ( (state) >= STD_BINARY_OUTPUT_STATE_ON )
#define STD_BINARY_OUTPUT_STATE_HAS_TIME(state)        ( (state) > STD_BINARY_OUTPUT_STATE_ON )
#define STD_BINARY_OUTPUT_STATE_TIME_IN_SECONDS(state) ( ( (state) & 0x80 ) != 0x00 )
#define STD_BINARY_OUTPUT_STATE_GET_SECONDS(state)     ( (state) & 0x7F )
#define STD_BINARY_OUTPUT_STATE_TIME_IN_MINUTES(state) ( (state) > STD_BINARY_OUTPUT_STATE_ON && (state) <= 0x7F )
#define STD_BINARY_OUTPUT_STATE_GET_MINUTES(state)     (state)

// Structure returned by PCMD_STD_BINARY_OUTPUTS_SET
typedef struct
{
  uns8	PreviousStates[4];
} STRUCTATTR TPerStdBinaryOutputSet_Response;


// -------------------------------------------------------------------------------------------
// IQRF Light standard
// -------------------------------------------------------------------------------------------
// IQRF Light standard peripheral
#define	PNUM_STD_LIGHT							0x71
// IQRF Light standard peripheral type
#define	PERIPHERAL_TYPE_STD_LIGHT				0x71
// Current version
#define STD_LIGHT_VERSION                       5

// IQRF Light standard peripheral - Set Power
#define	PCMD_STD_LIGHT_SET						0x00
// IQRF Light standard peripheral - Increment Power
#define	PCMD_STD_LIGHT_INC						0x01
// IQRF Light standard peripheral - Decrement Power
#define	PCMD_STD_LIGHT_DEC						0x02

// IQRF Light standard peripheral - FRC commands
#define	FRC_STD_LIGHT_ONOFF						0x10
#define	FRC_STD_LIGHT_ALARM						0x11

// Structure returned by PCMD_STD_ENUMERATE
typedef struct
{
  uns8	Count;
} STRUCTATTR TPerStdLightEnumerate_Response;

// Structure for PCMD_STD_LIGHT_???
typedef struct
{
  uns8	Bitmap[4];
  uns8	Power[DPA_MAX_DATA_LENGTH - 4];
} STRUCTATTR TPerStdLightSetIncDec_Request;

#define STD_LIGHT_POWER_MIN                 0
#define STD_LIGHT_POWER_MAX                 100
#define STD_LIGHT_KEEP_POWER                127
#define STD_LIGHT_IS_POWER_OK(power)        ( ( ( (power) & 0x7F ) <= STD_LIGHT_POWER_MAX ) || ( (power) & 0x7F ) == STD_LIGHT_KEEP_POWER )
#define STD_LIGHT_TIME_FOLLOWS_POWER(power) ( ( (power) & 0x80 ) != 0x00 )

#define STD_LIGHT_IS_TIME_OK(time)          ( ( (time) & 0x7F ) != 0x00 )
#define STD_LIGHT_TIME_IN_SECONDS(time)     ( ( (time) & 0x80 ) != 0x00 )
#define STD_LIGHT_TIME_GET_SECONDS(time)    ( (time) & 0x7F )
#define STD_LIGHT_TIME_IN_MINUTES(time)     ( !STD_LIGHT_TIME_IN_SECONDS( time ) )
#define STD_LIGHT_TIME_GET_MINUTES(time)    (time)

// -------------------------------------------------------------------------------------------
// IQRF DALI standard
// -------------------------------------------------------------------------------------------
// IQRF DALI standard peripheral
#define	PNUM_STD_DALI							0x4A
// IQRF DALI standard peripheral type
#define	PERIPHERAL_TYPE_STD_DALI				0x4A
// Current version
#define STD_DALI_VERSION                        0

// IQRF DALI standard peripheral - Send DALI commands
#define	PCMD_STD_DALI_SEND_COMMANDS				0x00
// IQRF DALI standard peripheral - Send DALI commands asynchronously
#define	PCMD_STD_DALI_SEND_COMMANDS_ASYNC		0x01

// IQRF DALI standard peripheral - FRC commands
#define FRC_STD_DALI_SEND						0xE0

#if defined( __CC5X__ )
// DALI answer byte #0
typedef struct
{
  bit Answer;
  bit AnswerError;
  bit _bit2_reserved;
  bit _bit3_reserved;
  bit _bit4_reserved;
  bit _bit5_reserved;
  bit _bit6_reserved;
  bit Always1;
} TSTD_DALI_Answer0;
#endif

// -------------------------------------------------------------------------------------------

// DPA Message data structure (packet w/o NADR, PNUM, PCMD, HWPID) for IQRF standards
typedef union
{
  // Structure for PCMD_STD_SENSORS_READ[_TYPES_AND]_VALUES
  TPerStdSensorRead_Request PerStdSensorRead_Request;

  // Structure returned by PCMD_STD_ENUMERATE for binary output
  TPerStdBinaryOutputEnumerate_Response PerStdBinaryOutputEnumerate_Response;

  // Structure for PCMD_STD_BINARY_OUTPUTS_SET
  TPerStdBinaryOutputSet_Request PerStdBinaryOutputSet_Request;

  // Structure returned by PCMD_STD_BINARY_OUTPUTS_SET
  TPerStdBinaryOutputSet_Response PerStdBinaryOutputSet_Response;

  // Structure returned by PCMD_STD_ENUMERATE for light
  TPerStdLightEnumerate_Response PerStdLightEnumerate_Response;
} TDpaMessageIqrfStd;

#if defined( __CC5X__ ) && !defined( CC5XnotDPA )
// The structure above mapped at the DpaMessage
TDpaMessageIqrfStd  _DpaMessageIqrfStd @ DpaRfMessage;
#endif  // #ifdef __CC5X__

// -------------------------------------------------------------------------------------------

#endif	// _IQRFSTD_HEADER_

//############################################################################################
