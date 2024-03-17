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

// This file contains required functions and variables that are specific
// to a CPU and required before the OEMGlobal table is available.  Therefore
// their names are hard-coded and they must be implemented for their
// respective CPU architectures.
#if defined (ARM)
// ---------------------------------------------------------------------------
// OEMARMCacheMode: REQUIRED (ARM CPUs only)
//
// This function sets the cache mode used to build the ARM CPU page tables.
// It sets the value of g_pOemGlobal->dwARMCacheMode before the OemGlobal
// table is initialized.
//
DWORD OEMARMCacheMode(void)
{
  // Fill in cache code here.

  return 0;
}

// ---------------------------------------------------------------------------
// OEMPTEUpdateBarrier: OPTIONAL (ARM CPUs only)
//
// This function is called when a page table entry is modified; this is used
// only for certain ARM CPU designs which need a hazard barrier to cache
// page table entries.
//
void OEMPTEUpdateBarrier(LPVOID pte, DWORD cbSize)
{
  // Fill in hazard barrier code here.

  return;
}

#elif defined (MIPS)
// ---------------------------------------------------------------------------
// OEMTLBSize: REQUIRED (MIPS CPUs only)
//
// This variable specifies the last index for the TLB which corresponds to
// the size of the TLB minus 1.  It sets the value of
// g_pOemGlobal->dwOEMTLBLastIdx before the OemGlobal table is initialized.
//
DWORD OEMTLBSize = -1;

// ---------------------------------------------------------------------------
// IntrPriority: REQUIRED (MIPS CPUs only)
//
// This variable specifies a pointer to an array that provides the kernel
// with information about which nested interrupts are masked while the
// current interrupt is being handled. It sets the value of
// g_pOemGlobal->pIntrPrio before the OemGlobal table is initialized.
//
BYTE IntrPriority[] = { 0 };

// ---------------------------------------------------------------------------
// IntrMask: REQUIRED (MIPS CPUs only)
//
// This variable specifies a pointer to an array that provides the kernel
// with information about which nested interrupts are masked while the
// current interrupt is being handled. It sets the value of
// g_pOemGlobal->pIntrMask before the OemGlobal table is initialized.
//
BYTE IntrMask [] = { 0 };

#endif
