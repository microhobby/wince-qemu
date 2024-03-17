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
#include <oemglobal.h>

// ---------------------------------------------------------------------------
// OEMNotifyThreadExit: OPTIONAL
//
// This function is called by the kernel when a thread exits.
//
void OEMNotifyThreadExit(DWORD dwThrdId, DWORD dwExitCode)
{
  // Fill in code here.

  return;
}

// ---------------------------------------------------------------------------
// OEMNotifyReschedule: OPTIONAL
//
// This function is called by the kernel when a new thread is ready to run.
//
void OEMNotifyReschedule(DWORD dwThrdId, DWORD dwPrio, DWORD dwQuantum, DWORD dwFlags)
{
  // Fill in code here.

  return;
}

// ---------------------------------------------------------------------------
// OEMMapW32Priority: OPTIONAL
//
// This function is called by the kernel to initialize a custom mapping of
// Win32 thread priorities to CE thread priorities.
//
void OEMMapW32Priority(int nPrios, LPBYTE pPrioMap)
{
  // Fill in mapping code here.

  return;
}


