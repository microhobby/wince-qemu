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

// Timer.c
 
//------------------------------------------------------------------------------
//
// OALGetTickCount: REQUIRED
//
// This function returns number of 1 ms ticks which elapsed since system boot
// or reset (absolute value isn't important).  It is required for the
// platform\common KITL implementation because DHCP and IP use timeouts.
// The implementation can be the same as the OAL or a simplified version.
//
UINT32 OALGetTickCount(void)
{
  // Fill in timer code here.

  return 0;
}

//------------------------------------------------------------------------------
//
// OEMKitlGetSecs: REQUIRED
//
// This function returns number of 1 second ticks which elapsed since system
// boot or reset (absolute value isn't important).  It is commonly implemented
// as below with a query to OALGetTickCount.
//
DWORD OEMKitlGetSecs(void)
{
  return (OALGetTickCount() * 1000);
}

