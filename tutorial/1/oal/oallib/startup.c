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

extern void KernelStart();

// ---------------------------------------------------------------------------
// StartUp: REQUIRED
//
// This function is the first function that is called in Windows CE after the
// bootloader runs.  It is the entry point of oal.exe (also known as nk.exe),
// which is the kernel process.  Traditionally it is named StartUp, but its
// name can be changed provided it matches the EXEENTRY in the SOURCES file
// where oal.exe is linked.
// 
// This function is repsonsible for performing hardware initialization of the
// CPU, memory controller, clocks, serial port, and caches / TLBs.  For ARM
// and x86 CPUs it is responsible for loading the OEMAddressTable into memory
// for use by the KernelStart function.
//
// Because StartUp implements the lowest level of initialization before the
// MMU is initialized, it is typically implemented in assembly code.  It is
// common for StartUp to be implemented in an assembly file such as startup.s
// or startup.asm.  You should replace this file with such a file and modify
// the SOURCES file in this directory to match.
//
void StartUp(void)
{
  // replace this file with assembly code that jumps to KernelStart
  KernelStart();
}
