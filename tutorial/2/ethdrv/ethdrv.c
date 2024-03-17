//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
#include <windows.h>
#include <kitl.h>

// Ethdrv.c
// The comments in this file will vary from OS version to version.
//
// This file implements functions that support the default Ethernet KITL debug
// transport supported by Windows CE.  These functions are called through 
// the PKITLTRANSPORT structure found in public\common\oak\inc\kitl.h.  
//
// All functions in this file fall into one of three categories:
// REQUIRED - you must implement this function for Ethernet KITL debug 
// functionality
// OPTIONAL - you may implement this function to enable specific functionality
// CUSTOM   - this function is a helper function specific to this BSP
//
// While the function signatures match those of the PKITLTRANSPORT structure,
// the function names themselves are not hardcoded and can be modified.  If
// the names are modified, the OEMKitlInit function pointers must be modified
// to point at the new function names.
//


//------------------------------------------------------------------------------
//
// KITLEthEncodeFrame: REQUIRED
//
// This function wraps the input frame in the transport-specific header and
// tailer.  For the default Ethernet KITL debug transport this means wrapping
// the frame in MAC, UDP, and IP headers as follows: 
//          ----------------
//          |  MAC Header  |
//          ----------------
//          |   IP Header  |
//          ----------------
//          |  UDP Header  |
//          |--------------|
//          |     Data     | // of size cbData
//          |--------------|
//
// For the default Ethernet KITL debug transport, there is no tailer.
//
BOOL KITLEthEncodeFrame(LPBYTE pbFrame, USHORT cbData)
{
  // Fill in encode code here.

  return TRUE;
}

//------------------------------------------------------------------------------
//
// KITLEthDecodeFrame: REQUIRED
//
// This function decodes the input frame according to the transport, returning
// a pointer to the data if the frame is valid.  For the default Ethernet KITL
// debug transport this means decoding ARP, ICMP, DHCP, or special KITL UDP
// packets and sending any necessary reply packets.
//
LPBYTE KITLEthDecodeFrame(LPBYTE pbFrame, PUSHORT pcbData)
{
  // Fill in decode code here.

  return NULL;
}

//------------------------------------------------------------------------------
//
// KITLEthSendFrame: REQUIRED
//
// This function sends the input frame to the host KITL transport.  For the
// default Ethernet KITL debug transport this means transmitting an Ethernet
// packet using the hardware.
//
BOOL KITLEthSendFrame(LPBYTE pbFrame, USHORT cbFrame)
{
  // Fill in send code here.

  return TRUE;
}

//------------------------------------------------------------------------------
//
// KITLEthRecvFrame: REQUIRED
//
// This function receives a frame from the host KITL transport.  For the
// default Ethernet KITL debug transport this means receiving an Ethernet
// packet using the hardware.
//
BOOL KITLEthRecvFrame(LPBYTE pbBuffer, PUSHORT pcbBuffer)
{
  // Fill in receive code here.

  return TRUE;
}

//------------------------------------------------------------------------------
//
// KITLEthEnableInt: OPTIONAL
//
// This function enables/disables the KITL transport interrupt (if the
// transport is interrupt-based).  For the default Ethernet KITL debug
// transport this means enabling/disabling the Ethernet hardware interrupt.
//
// This function is optional because polling mode may be used for any
// transport.  Typically, polling mode is much slower and CPU-intensive than
// interrupt mode.  It is also typically easier to implement and debug.
//
// If this function is not implemented, the corresponding function pointer must
// be initialized to NULL and the Interrupt member of the PKITLTRANSPORT
// structure must be initialized to KITL_SYSINTR_NOINTR, indicating that KITL
// only supports polling mode.
//
void KITLEthEnableInt(BOOL fEnable)
{
  // Fill in interrupt code here.

  return;
}

//------------------------------------------------------------------------------
//
// KITLEthGetDevCfg: REQUIRED
//
// This function provides information about the device to the transport layer.
// For the default Ethernet KITL debug transport, the information should be
// the device IP address, MAC address, and UDP port number, in that order.
//
BOOL KITLEthGetDevCfg(LPBYTE pbBuffer, PUSHORT pcbBuffer)
{
  // Fill in device configuration code here.

  return TRUE;
}

//------------------------------------------------------------------------------
//
// KITLEthSetHostCfg: REQUIRED
//
// This function negotiaties in response to information sent by the host KITL
// transport.  For the default Ethernet KITL debug transport, no negotiation is
// used, so this function may be left blank.
//
BOOL KITLEthSetHostCfg(LPBYTE pbData, USHORT cbSize)
{
  // Fill in any custom negotiation code here.

  return TRUE;
}

//------------------------------------------------------------------------------
//
// KITLEthPowerOff: OPTIONAL
//
// This function saves KITL device state and powers down KITL hardware.
//
void KITLEthPowerOff(void)
{
  // Fill in power code here.

  return;
}

//------------------------------------------------------------------------------
//
// KITLEthPowerOn: OPTIONAL
//
// This function restores KITL device state and powers up KITL hardware.
//
void KITLEthPowerOn(void)
{
  // Fill in power code here.

  return;
}


