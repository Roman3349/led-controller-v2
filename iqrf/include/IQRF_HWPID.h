// *********************************************************************
//   IQRF HWPIDs                                                       *
// *********************************************************************
// Copyright (c) IQRF Tech s.r.o.
//
// File:    $RCSfile: IQRF_HWPID.h,v $
// Version: $Revision: 1.87 $
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

#ifndef _IQRFSTD_HWPID_
#define _IQRFSTD_HWPID_

//# Class #1 #################################################################################
// Manufacturer: bits:0-9, bit.0=0 (even numbers, but not 0x000)
// Product: bits:10-15 (6 bits)
//############################################################################################
#ifdef __CC5X__
#define HWPID_CLS1(prod,man) \
#if prod < 0 || prod > 0b11.1111 \
#error "HWPID_CLS1: invalid product number" \
#endif \
#if man == 0 || man > 0x3FF || ( man & 1 ) != 0 \
#error "HWPID_CLS1: invalid manufacturer number" \
#endif \
( (uns16)(man) | ( (uns16)(prod) << 10 ) )
#else
#define HWPID_CLS1(prod,man) ( (uns16)(man) | ( (uns16)(prod) << 10 ) )
#endif

// -------------------------------------------------------------------------------------------
// IQRF Tech s.r.o.
#define	HWPID_IQRF_TECH	  0x002

// DDC-SE-01 sensor example
// (0002_DDC-SE01.c)
#define	HWPID_IQRF_TECH__DEMO_DDC_SE01				  HWPID_CLS1( 0x00, HWPID_IQRF_TECH ) // 0x0002

// DDC-SE-01 + DDC-RE-01 sensor example
// (0402_DDC-SE+RE.c)
#define	HWPID_IQRF_TECH__DEMO_DDC_SE01_RE01			  HWPID_CLS1( 0x01, HWPID_IQRF_TECH ) // 0x0402

// TR temperature sensor example
// (0802_TrThermometer.c)
#define	HWPID_IQRF_TECH__DEMO_TR_THERMOMETER		  HWPID_CLS1( 0x02, HWPID_IQRF_TECH ) // 0x0802

// Binary output example using LEDs and DDC-RE-01
// (0C02_BinaryOutput-Template.c)
#define	HWPID_IQRF_TECH__DEMO_BINARY_OUTPUT			  HWPID_CLS1( 0x03, HWPID_IQRF_TECH ) // 0x0C02

// Light example
// (1002_Light-Template.c)
#define	HWPID_IQRF_TECH__DEMO_LIGHT					  HWPID_CLS1( 0x04, HWPID_IQRF_TECH ) // 0x1002

// Sensor template
// (1402_Sensor-Template.c)
#define	HWPID_IQRF_TECH__DEMO_SENSOR_TEMPLATE		  HWPID_CLS1( 0x05, HWPID_IQRF_TECH ) // 0x1402

// ToDo Description DK-SW2-01
// ToDo (?.c)
#define	HWPID_IQRF_TECH__DK_SW2_01                    HWPID_CLS1( 0x06, HWPID_IQRF_TECH ) // 0x1802

// ToDo Description IQD-SW1-01
// ToDo (?.c)
#define	HWPID_IQRF_TECH__IQD_SW1_01                   HWPID_CLS1( 0x07, HWPID_IQRF_TECH ) // 0x1C02

// ToDo Description IQD-SW2-01
// ToDo (?.c)
#define	HWPID_IQRF_TECH__IQD_SW2_01                   HWPID_CLS1( 0x08, HWPID_IQRF_TECH ) // 0x2002

// ToDo Description IQD-RC3-01
// ToDo (?.c)
#define	HWPID_IQRF_TECH__IQD_RC3_01                   HWPID_CLS1( 0x09, HWPID_IQRF_TECH ) // 0x2402

// ToDo Description IQD-SM1
// ToDo (2802_IQD-SM1.c)
#define	HWPID_IQRF_TECH__IQD_SM1                      HWPID_CLS1( 0x0A, HWPID_IQRF_TECH ) // 0x2802

// ToDo Description IQD-RC4-01
// ToDo (?.c)
#define	HWPID_IQRF_TECH__RC4_01                       HWPID_CLS1( 0x0B, HWPID_IQRF_TECH ) // 0x2C02

// ToDo Description IQD-RC4-02
// ToDo (?.c)
#define	HWPID_IQRF_TECH__RC4_02                       HWPID_CLS1( 0x0C, HWPID_IQRF_TECH ) // 0x3002

// ToDo Description IQD-REP-01
// ToDo (?.c)
#define	HWPID_IQRF_TECH__REP_01                       HWPID_CLS1( 0x0D, HWPID_IQRF_TECH ) // 0x3402

// ToDo Description IQD-SW1-02
// ToDo (?.c)
#define	HWPID_IQRF_TECH__IQD_SW1_02                   HWPID_CLS1( 0x0F, HWPID_IQRF_TECH ) // 0x3C02

// DDC-SE-01 + DDC-RE-01 sensor + binary output example - LP version
// (4402_DDC-SE+RE_LP.c)
#define	HWPID_IQRF_TECH__DEMO_DDC_SE01_RE01_LP		  HWPID_CLS1( 0x11, HWPID_IQRF_TECH ) // 0x4402

// DDC-RE-01 binary output example - LP version
// (4802_DDC-RE_LP.c)
#define	HWPID_IQRF_TECH__DEMO_DDC_RE01_LP		      HWPID_CLS1( 0x12, HWPID_IQRF_TECH ) // 0x4802

// DDC-SE-01 sensor example - LP version
// (4C02_DDC-SE_LP.c)
#define	HWPID_IQRF_TECH__DEMO_DDC_SE01_LP		      HWPID_CLS1( 0x13, HWPID_IQRF_TECH ) // 0x4C02

// IQD_REP_02_W1D
// (5002_IQD_REP_02_W1D.c + IQD_REP_02_x1D)
#define	HWPID_IQRF_TECH__IQD_REP_02_W1D				  HWPID_CLS1( 0x14, HWPID_IQRF_TECH ) // 0x5002

// IQD_REP_02_S1D
// (5402_IQD_REP_02_S1D.c + IQD_REP_02_x1D)
#define	HWPID_IQRF_TECH__IQD_REP_02_S1D				  HWPID_CLS1( 0x15, HWPID_IQRF_TECH ) // 0x5402

// DALI_TEMPLATE
// (5802_DALI_TEMPLATE.c)
#define	HWPID_IQRF_TECH__DALI_TEMPLATE				  HWPID_CLS1( 0x16, HWPID_IQRF_TECH ) // 0x5802

// IQD-REP-03
// (5C02_P-IQD-REP-03.c)
#define	HWPID_IQRF_TECH__P_IQD_REP_03 				  HWPID_CLS1( 0x17, HWPID_IQRF_TECH ) // 0x5C02

// IQD_REP_02_W2D
// (6002_IQD_REP_02_W2D.c + IQD_REP_02_x1D)
#define	HWPID_IQRF_TECH__IQD_REP_02_W2D				  HWPID_CLS1( 0x18, HWPID_IQRF_TECH ) // 0x6002

// IQD_REP_02_S2D
// (6402_IQD_REP_02_S2D.c + IQD_REP_02_x1D)
#define	HWPID_IQRF_TECH__IQD_REP_02_S2D				  HWPID_CLS1( 0x19, HWPID_IQRF_TECH ) // 0x6402

// -------------------------------------------------------------------------------------------
// MICRORISC s.r.o.
#define	HWPID_MICRORISC	  0x004

// IQD_REP_02
// (?.c)
#define	HWPID_MICRORISC__IQD_REP_02				  HWPID_CLS1( 0x00, HWPID_MICRORISC )     // 0x0004

// Radar Counter
// (0404_RadarCounter.c)
#define	HWPID_MICRORISC__RADAR_COUNTER			  HWPID_CLS1( 0x01, HWPID_MICRORISC )     // 0x0404

// IQD-DALI-01
// (0804_IQD-DALI-01.c)
#define	HWPID_MICRORISC__IQD_DALI_01			  HWPID_CLS1( 0x02, HWPID_MICRORISC )     // 0x0804

// P-IQD-TEMP-01
// (0C04_P-IQD-TEMP-01.c)
#define	HWPID_MICRORISC__P_IQD_TEMP_01			  HWPID_CLS1( 0x03, HWPID_MICRORISC )     // 0x0C04

// IQD-TEMP-02
// (1004_IQD-TEMP-02.c)
#define	HWPID_MICRORISC__IQD_TEMP_02			  HWPID_CLS1( 0x04, HWPID_MICRORISC )     // 0x1004

// IQD-CNT-01
// (1404_IQD-CNT-01.c)
#define	HWPID_MICRORISC__IQD_CNT_01			      HWPID_CLS1( 0x05, HWPID_MICRORISC )     // 0x1404

// IQD-CNT-02
// (1804_IQD-CNT-02.c)
#define	HWPID_MICRORISC__IQD_CNT_02			      HWPID_CLS1( 0x06, HWPID_MICRORISC )     // 0x1804

// IQD-CNT1-01-T-E-01
// (1C04_IQD-CNT1-01-T-E-01.c)
#define HWPID_MICRORISC_IQD_CNT1_01_T_E_01        HWPID_CLS1( 0x07, HWPID_MICRORISC )     // 0x1C04

// IQD-CNT1-01-TH-I-01
// (2004_IQD-CNT1-01-TH-I-01.c)
#define HWPID_MICRORISC_IQD_CNT1_01_TH_F_01       HWPID_CLS1( 0x08, HWPID_MICRORISC )     // 0x2004

// IQD-CNT1-01-TH-F-01
// (2404_IQD-CNT1-01-TH-F-01.c)
#define HWPID_MICRORISC_IQD_CNT1_01_TH_I_01       HWPID_CLS1( 0x09, HWPID_MICRORISC )     // 0x2404

//# Class #2 #################################################################################
// Manufacturer: bits:0-11, bit.0=1 (odd numbers, never value 0x??F)
// Product: bits:12-15 (4 bits)
//############################################################################################
#ifdef __CC5X__
#define HWPID_CLS2(prod,man) \
#if prod < 0 || prod > 0b1111 \
#error "HWPID_CLS2: invalid product number" \
#endif \
#if man > 0xFFF || ( man & 1 ) == 0 || ( max & 0xF ) == 0xF \
#error "HWPID_CLS2: invalid manufacturer number" \
#endif \
( (uns16)(man) | ( (uns16)(prod) << 12 ) )
#else
#define HWPID_CLS2(prod,man) ( (uns16)(man) | ( (uns16)(prod) << 12 ) )
#endif
// -------------------------------------------------------------------------------------------
// PROTRONIX s.r.o.
#define	HWPID_PROTRONIX	  0x001

// Temperature+Humidity+CO2 sensor
// (0001_Protronix-T+RH+CO2.c)
#define	HWPID_PROTRONIX__TEMP_HUM_CO2				  HWPID_CLS2( 0x0, HWPID_PROTRONIX ) // 0x0001

// Temperature+Humidity+VOC sensor
// (1001_Protronix-T+RH+VOC.c)
#define	HWPID_PROTRONIX__TEMP_HUM_VOC				  HWPID_CLS2( 0x1, HWPID_PROTRONIX ) // 0x1001

// Temperature+Humidity+CO2 sensor + Relay
// (2001_Protronix-T+RH+CO2+Relay.c)
#define	HWPID_PROTRONIX__TEMP_HUM_CO2_RELAY			  HWPID_CLS2( 0x2, HWPID_PROTRONIX ) // 0x2001

// Temperature+Humidity sensor
// (3001_Protronix-T+RH.c)
#define	HWPID_PROTRONIX__TEMP_HUM					  HWPID_CLS2( 0x3, HWPID_PROTRONIX ) // 0x3001

// Temperature+Humidity+CO2 sensor [LP]
// (4001_Protronix-LP-T+RH+CO2.c)
#define	HWPID_PROTRONIX__LP_TEMP_HUM_CO2			  HWPID_CLS2( 0x4, HWPID_PROTRONIX ) // 0x4001

// Temperature+Humidity sensor [LP]
// (5001_Protronix-LP-T+RH.c)
#define	HWPID_PROTRONIX__LP_TEMP_HUM				  HWPID_CLS2( 0x5, HWPID_PROTRONIX ) // 0x5001

// PM 2,5 sensor [LP]
// (6001_Protronix-NLII_PM25.c)
#define	HWPID_PROTRONIX__NLII_PM25  				  HWPID_CLS2( 0x6, HWPID_PROTRONIX ) // 0x6001

// -------------------------------------------------------------------------------------------
// NETIO products a.s.
#define	HWPID_NETIO		  0x003

// Cobra 1 - 1x power plug
// (0003_Netio-Cobra1.c)
#define	HWPID_NETIO__COBRA1							  HWPID_CLS2( 0x0, HWPID_NETIO )	 // 0x0003

// Cobra 1 - 1x power plug [LP]
// (1003_Netio-LP-Cobra1.c)
#define	HWPID_NETIO__LP_COBRA1						  HWPID_CLS2( 0x1, HWPID_NETIO )	 // 0x1003

// -------------------------------------------------------------------------------------------
// DATmoLUX a.s.
#define	HWPID_DATMOLUX	  0x005

// DATmoLUX Light
// 0005_DATmoLUX-Light.*
#define	HWPID_DATMOLUX__LIGHT						  HWPID_CLS2( 0x0, HWPID_DATMOLUX )	 // 0x0005

// -------------------------------------------------------------------------------------------
// CITIQ s.r.o.
#define	HWPID_CITIQ		  0x007

// -------------------------------------------------------------------------------------------
// Austyn International s.r.o.
#define	HWPID_AUSTYN	  0x009

// Room temperature controller
// (0009_RoomTemperatureController.c)
#define	HWPID_AUSTYN__ROOM_CONTROLLER				  HWPID_CLS2( 0x0, HWPID_AUSTYN )	 // 0x0009

// -------------------------------------------------------------------------------------------
// Aledo s.r.o.
#define	HWPID_ALEDO		  0x00B

// Room temperature controller
// (000B_Aledo-Reader_R02A230.c)
#define	HWPID_ALEDO__READER_R02A230					  HWPID_CLS2( 0x0, HWPID_ALEDO )	 // 0x000B

// -------------------------------------------------------------------------------------------
// SANELA spol. s r. o.
#define	HWPID_SANELA	  0x00D

// Sanela SL626 Person presence sensor
// (000D_Sanela-SL626.c)
#define	HWPID_SANELA__SL626							  HWPID_CLS2( 0x0, HWPID_SANELA )	 // 0x000D

// Sanela SL626A sink sensor
// (100D_Sanela-SL626A.c)
#define	HWPID_SANELA__SL626A					      HWPID_CLS2( 0x1, HWPID_SANELA )	 // 0x100D

// -------------------------------------------------------------------------------------------
// TESLA Blatná, a.s.
#define	HWPID_TESLA_BLATNA  0x011

// TESLA Blatná Smart City environmental module
// (0011_TESLA_Blatna-EnvironmentalModule.c)
#define	HWPID_TESLA_BLATNA__EnvironmentalModule		  HWPID_CLS2( 0x0, HWPID_TESLA_BLATNA )	 // 0x0011

// -------------------------------------------------------------------------------------------
// JoTio Tech s.r.o.
#define	HWPID_JOTIO_TECH  0x013

// IRIS
#define	HWPID_JOTIO_TECH__IRIS              		  HWPID_CLS2( 0x0, HWPID_JOTIO_TECH )	 // 0x0013

// ALTAIR
#define	HWPID_JOTIO_TECH__ALTAIR            		  HWPID_CLS2( 0x1, HWPID_JOTIO_TECH )	 // 0x1013

// -------------------------------------------------------------------------------------------
// HARDWARIO s.r.o. (BigClown)
#define	HWPID_HARDWARIO  0x015

// Presence sensor
#define	HWPID_HARDWARIO_PRESENCE_SENSOR		          HWPID_CLS2( 0x0, HWPID_HARDWARIO )	 // 0x0015

// COOPER
// (1015_HARDWARIO-COPPER.c)
#define	HWPID_HARDWARIO_COOPER      		          HWPID_CLS2( 0x1, HWPID_HARDWARIO )	 // 0x1015

// -------------------------------------------------------------------------------------------
// 4IOTECH s.r.o.
#define	HWPID_4IOTECH  0x017

// 4IOT-SEN-01
#define	HWPID_4IOTECH_4IOT_SEN_01    		          HWPID_CLS2( 0x0, HWPID_4IOTECH )	     // 0x0017

// -------------------------------------------------------------------------------------------
// Liteplan Ltd.
#define	HWPID_LITEPLAN  0x019

// IQD-DALI-01
#define	HWPID_LITEPLAN_IQD_DALI_01    		          HWPID_CLS2( 0x0, HWPID_LITEPLAN )	     // 0x0019


// -------------------------------------------------------------------------------------------
// Danlers https://www.danlers.co.uk/
#define	HWPID_DANLERS  0x01B

// DANLERS-PIR
// (001B_DANLERS-PIR.c)
#define	HWPID_DANLERS_PIR              		          HWPID_CLS2( 0x0, HWPID_DANLERS )	     // 0x001B

// -------------------------------------------------------------------------------------------
// IQRF Solutions s.r.o.
#define	HWPID_IQRF_SOLUTIONS  0x507

// Water Quality Sensor
#define	HWPID_IQRF_SOLUTIONS_WATER_QUALITY_SENSOR     HWPID_CLS2( 0x0, HWPID_IQRF_SOLUTIONS )	 // 0x0507

// Air Quality Sensor
#define	HWPID_IQRF_SOLUTIONS_AIR_QUALITY_SENSOR       HWPID_CLS2( 0x1, HWPID_IQRF_SOLUTIONS )	 // 0x1507

// IQRF RS232 Bridge
#define	HWPID_IQRF_SOLUTIONS_IQRF_RE232_BRIDGE        HWPID_CLS2( 0x2, HWPID_IQRF_SOLUTIONS )	 // 0x2507

#endif	// _IQRFSTD_HWPID_

//############################################################################################
