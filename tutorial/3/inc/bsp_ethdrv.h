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

// Bsp_ethdrv.h

// This file declares functions for a platform\common-compliant Ethernet KITL
// debug transport driver.
// 

BOOL KITLEthdrvInit(UINT8 *pAddress, UINT32 offset, UINT16 mac[3]);
BOOL KITLEthdrvInitDMABuffer(UINT32 address, UINT32 size);
BOOL KITLEthdrvDeInit(void);
UINT16 KITLEthdrvSendFrame(UINT8 *pData, UINT32 size);
UINT16 KITLEthdrvGetFrame(UINT8 *pData, UINT16 *pSize);
VOID KITLEthdrvEnableInts(void);
VOID KITLEthdrvDisableInts(void);
VOID KITLEthdrvPowerOff(void);
VOID KITLEthdrvPowerOn(void);
VOID KITLEthdrvCurrentPacketFilter(UINT32 filter);
BOOL KITLEthdrvMulticastList(UINT8 *pAddresses, UINT32 count);

