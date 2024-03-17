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
// This contains IOCTL codes needed by oal_ioctl_tab.h
#include <pkfuncs.h>
// This is the platform\common ioctl header.
#include <oal_ioctl.h>
#include <oemglobal.h>

// ---------------------------------------------------------------------------
// OEMIoControl: REQUIRED
//
// This function provides a generic I/O control code (IOCTL) for
// OEM-supplied information.
//
// OEMIoControl is supplied by a platform\common library in this
// tutorial, so we should not implement it here in the BSP.

// ---------------------------------------------------------------------------
// g_oalIoCtlTable: REQUIRED
//
// The platform\common implementation requires that we define this variable
// describing which IOCTLs we support.
//
const OAL_IOCTL_HANDLER g_oalIoCtlTable[] = {
// Required Termination
{ 0,                                        0,  NULL                        }
};

// ---------------------------------------------------------------------------
// OEMKDIoctl: OPTIONAL
//
// This function supports requests from the kernel debugger.
//
BOOL OEMKDIoctl(DWORD dwCode, LPVOID pBuf, DWORD cbSize)
{
  // Fill in IOCTL code here.

  return TRUE;
}

// ---------------------------------------------------------------------------
// OEMIsProcessorFeaturePresent: OPTIONAL
//
// This function provides information about processor features and support.
//
BOOL OEMIsProcessorFeaturePresent(DWORD dwProcessorFeature)
{
  // Fill in processor feature code here.

  return TRUE;
}


