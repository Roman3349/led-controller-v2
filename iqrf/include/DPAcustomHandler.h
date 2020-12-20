// *********************************************************************
//   Main Custom DPA Handler header                                    *
// *********************************************************************
// Copyright (c) IQRF Tech s.r.o.
//
// File:    $RCSfile: DPAcustomHandler.h,v $
// Version: $Revision: 1.126 $
// Date:    $Date: 2020/09/03 15:37:12 $
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
//   2019/01/10  Release for DPA 4.00
//   2018/10/25  Release for DPA 3.03
//   2017/11/16  Release for DPA 3.02
//   2017/08/14  Release for DPA 3.01
//   2017/03/13  Release for DPA 3.00
//   2016/09/12  Release for DPA 2.28
//   2016/04/14  Release for DPA 2.27
//   2016/03/03  Release for DPA 2.26
//   2016/01/21  Release for DPA 2.25
//   2015/12/01  Release for DPA 2.24
//   2015/10/23  Release for DPA 2.23
//   2015/09/25  Release for DPA 2.22
//   2015/09/03  Release for DPA 2.21
//   2015/08/05  Release for DPA 2.20
//   2014/10/31  Release for DPA 2.10
//   2014/04/30  Release for DPA 2.00
//   2013/10/03  Release for DPA 1.00
//
// *********************************************************************

// Online DPA documentation https://doc.iqrf.org/DpaTechGuide/
// IQRF Standards documentation https://www.iqrfalliance.org/iqrf-interoperability/

#ifndef _CUSTOM_DPA_HANDLER_
#define _CUSTOM_DPA_HANDLER_

//############################################################################################
// 1st include

// Custom DPA Handler routine declaration
bit CustomDpaHandler();

// Various DPA flags shared between DPA and Custom DPA Handler
uns8 DpaFlags @ usedBank4[0];
#ifdef COORDINATOR_CUSTOM_HANDLER
// [C] TRUE if interface master is not connected (detected)
bit IFaceMasterNotConnected @ DpaFlags.2;
#endif
// [N] [CN] DPA by interface notification is sent also when there was a "reading" like DPA request
bit EnableIFaceNotificationOnRead @ DpaFlags.3;
// [N] [NC] TRUE when node was just bonded using default bonding procedure
bit NodeWasBonded @ DpaFlags.4;
// [N] When TRUE, then next call of DpaApiRfTxDpaPacket sends non-routed packet
bit NonroutedRfTxDpaPacket @ DpaFlags.7;

// [C] Ticks (decrementing) counter usable for timing in the coordinator's Customer DPA Handler
uns16 DpaTicks @ usedBank4[1];
// [N] [NC] toutRF for LP mode, read from configuration memory after reset
uns8 LPtoutRF @ usedBank4[3];
// DPA Request/Response HWPID
uns16 _HWPID @ usedBank4[4];
// Identifies type of reset (stored at UserReg0 upon module reset). See Reset chapter at IQRF User's Guide for more information
uns8 ResetType @ usedBank4[6];
// User DPA Values to return
uns8 UserDpaValue @ usedBank4[7];
// Network depth of the DPA request/response, increases on bridging, decreases on back-bridging
uns8 NetDepth @ usedBank4[8];
// TRUE when node was at DPA Service Mode after last boot
bit DSMactivated @ usedBank4[9].0;
// If set to TRUE, then LP RX mode in the main loop can be terminated by pin, see _RLPMAT
bit LpRxPinTerminate @ usedBank4[9].1;
// If set to TRUE, then [C] executes asynchronous DPA requests received from [N]
bit AsyncReqAtCoordinator @ usedBank4[9].2;
// RX filter used at the DPA main loop checkRF call
uns8 RxFilter @ usedBank4[11];
// Countdown variable for button bonding before going to deep sleep
uns16 BondingSleepCountdown @ usedBank4[12];
#define BONDING_SLEEP_COUNTDOWN_UNIT  290
// Non-zero pseudo-random value, read-only, updated on every Reset and Idle event, at [N] only.
uns16 Random @ usedBank4[14];

// Macro to return an error from the peripheral handler. If the code size is not an issue this macro is the right choice.
#define DpaApiReturnPeripheralError(error) do { \
	DpaApiSetPeripheralError( error ); \
	return Carry; \
  } while( 0 )

// DPA API functions, see documentation for details
#define	DpaApiRfTxDpaPacket( dpaValue, netDepthAndFlags ) DpaApiEntry( dpaValue, netDepthAndFlags, DPA_API_RFTX_DPAPACKET )
#define	DpaApiReadConfigByte( index )					  DpaApiEntry( index, param3.low8, DPA_API_READ_CONFIG_BYTE )
#define	DpaApiLocalRequest()							  DpaApiEntry( param2, param3.low8, DPA_API_LOCAL_REQUEST )
#define	DpaApiSetPeripheralError( error )				  DpaApiEntry( error, param3.low8, DPA_API_SET_PERIPHERAL_ERROR )
#define	DpaApiSendToIFaceMaster( dpaValue, flags )		  DpaApiEntry( dpaValue, flags, DPA_API_SEND_TO_IFACEMASTER )
#define	DpaApiSetRfDefaults()							  DpaApiEntry( param2, param3.low8, DPA_API_SET_RF_DEFAULTS )
#define	DpaApiLocalFrc( frcCommand, replyTxPower )        DpaApiEntry( frcCommand, replyTxPower, DPA_API_LOCAL_FRC )
#define	DpaApiCrc8( crc8, data )                          DpaApiEntry( crc8, data, DPA_API_CRC8 )

#ifdef COORDINATOR_CUSTOM_HANDLER
#define	DpaApiRfTxDpaPacketCoordinator()				  DpaApiEntry( param2, param3.low8, DPA_API_COORDINATOR_RFTX_DPAPACKET )
#endif

#ifdef COORDINATOR_CUSTOM_HANDLER
#undef	DpaEvent_Interrupt
#undef	DpaEvent_BeforeSleep
#undef	DpaEvent_AfterSleep
#undef	DpaEvent_FrcValue
#undef	DpaEvent_FrcResponseTime
#else
#undef  DpaEvent_ReceiveDpaResponse
#undef  DpaEvent_IFaceReceive
#endif

// To detect overlapping code in case someone would put some code before this header by mistake
#pragma origin __APPLICATION_ADDRESS
#pragma updateBank 0

//############################################################################################
// Main IQRF entry point jumps to the main DPA entry point
void APPLICATION()
//############################################################################################
{
  #asm
    DW  __MOVLP( MAIN_DPA_ADDRESS >> 8 );
  DW  __GOTO( MAIN_DPA_ADDRESS );
  #endasm

#ifndef NO_CUSTOM_DPA_HANDLER
    // Fake call to force CustomDpaHandler() compilation
    CustomDpaHandler();
#endif

  // Fake call to force DpaApiEntry() compilation
  DpaApiEntry( param2, param3.low8, W );
}

//############################################################################################
// Entry stub to the real DPA API entry
#pragma origin DPA_API_ADDRESS_ENTRY
uns8  DpaApiEntry( uns8 par1 @ param2, uns8 par2 @ param3.low8, uns8 apiIndex @ W )
//############################################################################################
{
  #asm
    DW  __MOVLP( DPA_API_ADDRESS >> 8 );
  DW  __CALL( DPA_API_ADDRESS );
  DW  __MOVLP( DPA_API_ADDRESS_ENTRY >> 8 );
  #endasm

    return W;
}

//############################################################################################
#pragma origin DPA_API_ADDRESS_ENTRY + 0x08

//############################################################################################

#ifndef NO_CUSTOM_DPA_HANDLER
// Next comes Custom DPA handler routine
#pragma origin CUSTOM_HANDLER_ADDRESS
#endif

#pragma updateBank 1

//############################################################################################
#else // _CUSTOM_DPA_HANDLER_
//############################################################################################
// 2nd include

#ifndef NO_CUSTOM_DPA_HANDLER
// Code bumper to detect too long code of Custom DPA handler + other routines
#pragma origin CUSTOM_HANDLER_ADDRESS_END
// To avoid adding some code after handler by mistake
#pragma origin __MAX_FLASH_ADDRESS
#endif

#endif	// _CUSTOM_DPA_HANDLER_
//############################################################################################
