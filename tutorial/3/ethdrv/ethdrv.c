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
// This file implements functions that support the platform\common Ethernet
// KITL OAL_KITL_ETH_DRIVER structure.
//
// All functions in this file fall into one of three categories:
// REQUIRED - you must implement this function for platform\common-compatible
// Ethernet KITL debug functionality
// OPTIONAL - you may implement this function to enable specific functionality
// CUSTOM   - this function is a helper function specific to this BSP
//
// While the function signatures match those of the OAL_KITL_ETH_DRIVER
// structure, the function names themselves are not hardcoded and can be
// modified.
//


//------------------------------------------------------------------------------
//
// KITLEthdrvInit: REQUIRED
//
// This function initializes the KITL Ethernet device driver and hardware.  
//
BOOL KITLEthdrvInit(UINT8 *pAddress, UINT32 offset, UINT16 mac[3])
{
  // Fill in init code here.

  return TRUE;
}

//------------------------------------------------------------------------------
//
// KITLEthdrvInitDMABuffer: OPTIONAL
//
// This function initializes the DMA buffer for the KITL Ethernet hardware.
// It is called just before the driver's Init function.
//
BOOL KITLEthdrvInitDMABuffer(UINT32 address, UINT32 size)
{
  // Fill in DMA init code here.

  return TRUE;
}

//------------------------------------------------------------------------------
//
// KITLEthdrvInitDeInit: OPTIONAL
//
// This function deinitializes the KITL Ethernet device driver and hardware.
// It is currently unused by platform\common code.
//
BOOL KITLEthdrvDeInit(void)
{
  // Fill in deinit code here.

  return TRUE;
}

//------------------------------------------------------------------------------
//
// KITLEthdrvSendFrame: REQUIRED
//
// This function sends the input frame to the host KITL transport using the
// Ethernet hardware.
//
UINT16 KITLEthdrvSendFrame(UINT8 *pData, UINT32 size)
{
  // Fill in send code here.

  return 0;
}

//------------------------------------------------------------------------------
//
// KITLEthdrvGetFrame: REQUIRED
//
// This function receives a frame from the host KITL transport using the
// Ethernet hardware.
//
UINT16 KITLEthdrvGetFrame(UINT8 *pData, UINT16 *pSize)
{
  // Fill in receive code here.

  return 0;
}

//------------------------------------------------------------------------------
//
// KITLEthdrvEnableInt: OPTIONAL
//
// This function enables the Ethernet hardware interrupt.
//
// This function is optional because polling mode may be used for any
// transport.  Typically, polling mode is much slower and CPU-intensive than
// interrupt mode.  It is also typically easier to implement and debug.
//
// If this function is not implemented, OAL_KITL_FLAGS_POLL must be set,
// instructing platform\common to initialize KITL in polling mode.
//
// This function is required for interrupt-mode functionality.
//
VOID KITLEthdrvEnableInts(void)
{
  // Fill in interrupt code here.

  return;
}

//------------------------------------------------------------------------------
//
// KITLEthDisableInt: OPTIONAL
//
// This function disables the Ethernet hardware interrupt.
//
// This function is optional because polling mode may be used for any
// transport.  Typically, polling mode is much slower and CPU-intensive than
// interrupt mode.  It is also typically easier to implement and debug.
//
// If this function is not implemented, OAL_KITL_FLAGS_POLL must be set,
// instructing platform\common to initialize KITL in polling mode.
//
// This function is required for interrupt-mode functionality.
//
VOID KITLEthdrvDisableInts(void)
{
  // Fill in interrupt code here.

  return;
}

//------------------------------------------------------------------------------
//
// KITLEthdrvPowerOff: OPTIONAL
//
// This function saves KITL device state and powers down KITL hardware.
//
void KITLEthdrvPowerOff(void)
{
  // Fill in power code here.

  return;
}

//------------------------------------------------------------------------------
//
// KITLEthdrvPowerOn: OPTIONAL
//
// This function restores KITL device state and powers up KITL hardware.
//
void KITLEthdrvPowerOn(void)
{
  // Fill in power code here.

  return;
}

//------------------------------------------------------------------------------
//
// KITLEthdrvCurrentPacketFilter: OPTIONAL
//
// This function sets the current packet filter of the NIC.  It is only
// used for VMINI functionality, but is required for VMINI functionality.
//
VOID KITLEthdrvCurrentPacketFilter(UINT32 filter)
{
  // Fill in packet filter code here.

  return;
}

//------------------------------------------------------------------------------
//
// KITLEthdrvMulticastList: OPTIONAL
//
// This function inserts addresses into the Ethernet multicast list.  It is
// only used for VMINI functionality.  It is optional for VMINI functionality
// but required for VMINI Multicast functionality (and recommended if the
// hardware supports Multicast).
//
BOOL KITLEthdrvMulticastList(UINT8 *pAddresses, UINT32 count)
{
  // Fill in multicast code here.

  return TRUE;
}

