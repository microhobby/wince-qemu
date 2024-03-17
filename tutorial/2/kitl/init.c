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
#include <winnt.h>
#include <oemglobal.h>
#include <kitl.h>

// Init.c
// The comments in this file will vary from OS version to version.
//
// All KITL functions in the template BSP fall into one of three categories:
// REQUIRED - you must implement this function for KITL functionality
// OPTIONAL - you may implement this function to enable specific functionality
// CUSTOM   - this function is a helper function specific to this BSP
//

// Function prototypes for the KITL Ethernet driver
BOOL KITLEthEncodeFrame(LPBYTE pbFrame, USHORT cbData);
LPBYTE KITLEthDecodeFrame(LPBYTE pbFrame, PUSHORT pcbData);
BOOL KITLEthSendFrame(LPBYTE pbFrame, USHORT cbFrame);
BOOL KITLEthRecvFrame(LPBYTE pbBuffer, PUSHORT pcbBuffer);
void KITLEthEnableInt(BOOL fEnable);
BOOL KITLEthGetDevCfg(LPBYTE pbBuffer, PUSHORT pcbBuffer);
BOOL KITLEthSetHostCfg(LPBYTE pbFrame, USHORT cbFrame);
void KITLEthPowerOff(void);
void KITLEthPowerOn(void);


//------------------------------------------------------------------------------
//
// OEMKitlStartup: REQUIRED
//
// This function is the first OEM code that executes in kitl.dll.  It is called
// by the kernel after the BSP calls KITLIoctl( IOCTL_KITL_STARTUP, ... ) in
// OEMInit().  This function should set up internal state, read any boot
// arguments, and call the KitlInit function to initialize KITL in active
// (immediate load) or passive (delay load) mode.
//
BOOL OEMKitlStartup()
{
  BOOL mode = TRUE; // TRUE for active mode, FALSE for passive mode

  // fill in startup code here

  return KitlInit(mode);
}

// ---------------------------------------------------------------------------
// OEMKitlInit: REQUIRED
//
// This function is called from the kernel to initialize the KITL device and
// KITLTRANSPORT structure when it is time to load KITL.  If OEMKitlStartup
// selects active mode KITL, KitlInit will call this function during boot. If
// OEMKitlStartup selects passive mode KITL, this function will not be called
// until an event triggers KITL load.

// When this function returns, the KITLTRANSPORT structure must contain valid
// variable initializations including valid function pointers for each
// required KITL function.  The KITL transport hardware must also be fully
// initialized.
//
BOOL OEMKitlInit(PKITLTRANSPORT pKitl)
{
  // Initialize dwBootFlags, which describe the KITL services to start and
  // whether we will clean boot.  These will actually be overwritten by the
  // selections made by the desktop transport.
  pKitl->dwBootFlags = KITL_FL_DBGMSG | KITL_FL_PPSH | KITL_FL_KDBG
                     | KITL_FL_CLEANBOOT;

  // Initialize device name - this needs to be changed to match the name
  // from the bootloader, and is typically read from memory shared with
  // the bootloader.
  memset(pKitl->szName, 0, sizeof(pKitl->szName));

  // Initialize to polling mode (no interrupt functionality).  Interrupt
  // mode will give far better performance; to use it, change this value
  // and initialize pfnEnableInt.
  pKitl->Interrupt = (UCHAR)KITL_SYSINTR_NOINTR;

  // Legacy value, ignored by KITL
  pKitl->WindowSize = 0;

  // size of the OEM-specific frame header, typically used for checksum.
  // Needs to be updated to match the Ethernet frame header size.
  pKitl->FrmHdrSize = 0;

  // size of the OEM-specific frame tail.  For Ethernet, this is 0.
  pKitl->FrmTlrSize = 0;

  // Legacy value, ignored by KITL
  pKitl->dwPhysBuffer = 0;

  // Legacy value, ignored by KITL
  pKitl->dwPhysBufLen = 0;

  // Initialize to polling mode (no interrupt functionality).  Interrupt
  // mode will give far better performance.
  pKitl->pfnEnableInt = NULL;

  // Set up pointers to our Ethernet driver functions.
  pKitl->pfnEncode = KITLEthEncodeFrame;
  pKitl->pfnDecode = KITLEthDecodeFrame;
  pKitl->pfnSend = KITLEthSendFrame;
  pKitl->pfnRecv = KITLEthRecvFrame;
  pKitl->pfnGetDevCfg = KITLEthGetDevCfg;
  pKitl->pfnSetHostCfg = KITLEthSetHostCfg;
  pKitl->pfnPowerOn = KITLEthPowerOff;
  pKitl->pfnPowerOff = KITLEthPowerOn;

  return TRUE;
}

// ---------------------------------------------------------------------------
// dpCurSettings: REQUIRED
//
// This variable defines debug zones usable by the kernel and this
// implementation.  This is the operating system's standard
// mechanism for debug zones.
//
DBGPARAM dpCurSettings = {
    TEXT("KITL"), {
    TEXT("Warning"),    TEXT("Init"),       TEXT("Frame Dump"),     TEXT("Timer"),
    TEXT("Send"),       TEXT("Receive"),    TEXT("Retransmit"),     TEXT("Command"),
    TEXT("Interrupt"),  TEXT("Adapter"),    TEXT("LED"),            TEXT("DHCP"),
    TEXT("OAL"),        TEXT("Ethernet"),   TEXT("Unused"),         TEXT("Error"), },
    ZONE_WARNING | ZONE_INIT | ZONE_ERROR,
};
