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
#include <pkfuncs.h>
#include <oemglobal.h>

// Function prototype for our IOCTL_HAL_DDI handler function, implemented
// in ddi.c
BOOL OALIoctlHalDdi(DWORD dwIoControlCode, const LPVOID lpInBuf, DWORD nInBufSize,
                    PVOID lpOutBuf, DWORD nOutBufSize,
                    LPDWORD lpBytesReturned
);

// ---------------------------------------------------------------------------
// OEMIoControl: REQUIRED
//
// This function provides a generic I/O control code (IOCTL) for
// OEM-supplied information.
//
BOOL OEMIoControl(
  DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, PVOID lpOutBuf,
  DWORD nOutBufSize, LPDWORD lpBytesReturned 
)
{
  // Fill in IOCTL code here.

  // Handle the IOCTL_HAL_DDI call
  switch(dwIoControlCode)
  {
      case IOCTL_HAL_DDI:
          OALIoctlHalDdi(dwIoControlCode, lpInBuf, nInBufSize, lpOutBuf,
                         nOutBufSize, lpBytesReturned);
          break;
  }  

  return TRUE;
}

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


