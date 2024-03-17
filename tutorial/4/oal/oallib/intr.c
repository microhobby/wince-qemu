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
// OEMInterruptEnable: REQUIRED
//
// This function performs all hardware operations necessary to enable the
// specified hardware interrupt.
//
BOOL OEMInterruptEnable(DWORD dwSysIntr, LPVOID pvData, DWORD cbData)
{
  // Fill in interrupt code here.

  return TRUE;
}

// ---------------------------------------------------------------------------
// OEMInterruptDisable: REQUIRED
//
// This function performs all hardware operations necessary to disable the
// specified hardware interrupt.
//
void OEMInterruptDisable(DWORD dwSysIntr)
{
  // Fill in interrupt code here.

  return;
}

// ---------------------------------------------------------------------------
// OEMInterruptDone: REQUIRED
//
// This function signals completion of interrupt processing.  This function
// should re-enable the interrupt if the interrupt was previously masked.
//
void OEMInterruptDone(DWORD dwSysIntr)
{
  // Fill in interrupt code here.

  return;
}

// ---------------------------------------------------------------------------
// OEMInterruptMask: REQUIRED
//
// This function masks or unmasks the interrupt according to its SysIntr
// value.
//
void OEMInterruptMask(DWORD dwSysIntr, BOOL fDisable)
{
  // Fill in interrupt code here.

  return;
}

// ---------------------------------------------------------------------------
// OEMNotifyIntrOccurs: OPTIONAL
//
// This function is called by the kernel when an interrupt occurs.  It is
// not an ISR intended to handle interrupts.
//
DWORD OEMNotifyIntrOccurs(DWORD dwSysIntr)
{
  // Fill in code here.

  return 0;
}

#if defined(x86)
// ---------------------------------------------------------------------------
// OEMNMIHandler (void return): REQUIRED for x86, UNUSED for other cpus
//
// This function handles the Non-Maskable Interrupt (NMI) on x86 cpus.
//
void OEMNMIHandler(void)
{
  // Fill in interrupt code here.

  return;
}

#elif defined(SHx)
// ---------------------------------------------------------------------------
// OEMNMIHandler (DWORD return): REQUIRED for SHx, UNUSED for other cpus
//
// This function handles the Non-Maskable Interrupt (NMI) on SHx cpus.
//
DWORD OEMNMI(void)
{
  // Fill in interrupt code here.

  return 0;
}

#elif defined (ARM)
// ---------------------------------------------------------------------------
// OEMInterruptHandler: REQUIRED for ARM, UNUSED for other cpus
//
// This function handles the standard ARM interrupt, providing all ISR
// functionality for ARM-based platforms.
//
DWORD OEMInterruptHandler(DWORD dwEPC)
{
  // Fill in interrupt code here.

  return 0;
}

// ---------------------------------------------------------------------------
// OEMInterruptHandlerFIQ: REQUIRED for ARM, UNUSED for other cpus
//
// This function handles the fast-interrupt request (FIQ) ARM interrupt,
// providing all FIQ ISR functionality for ARM-based platforms.
//
void OEMInterruptHandlerFIQ(void)
{
  // Fill in interrupt code here.

  return;
}
#endif

