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
#include <pkfuncs.h>
#include <oemglobal.h>

// Init.c
// The comments in this file will vary from OS version to version.
// Look up OEMGlobal on MSDN for a full reference of OAL functions,
// or see public\common\oak\inc\oemglobal.h
//
// All OAL functions in the template BSP fall into one of three categories:
// REQUIRED - you must implement this function for kernel functionality
// OPTIONAL - you may implement this function to enable specific functionality
// CUSTOM   - this function is a helper function specific to this BSP
//
// OEMGlobal is initialized by the kernel to use default function names
// for all required functions.  See the comments in
// public\common\oak\inc\oemglobal.h for a concise listing of the default
// function names along with their required/optional status.
//
// In this BSP all of the functions are implemented using the default
// function names.  However, with the exception of the OEMInitDebugSerial
// and OEMInit functions, you can change these function names from the
// defaults by pointing the kernel calls to use a different name - see
// RemapOALGlobalFunctions for an example of how to do this.  
//

// custom BSP functions
void RemapOALGlobalFunctions(void);
void SetOALGlobalVariables(void);

// forward declarations of optional OAL functions
void OEMWriteDebugByte(BYTE bChar);
void OEMWriteDebugString(LPCWSTR pszStr);
int OEMReadDebugByte(void);
void OEMWriteDebugLED(WORD wIndex, DWORD dwPattern);
void OEMInitClock(void);
BOOL OEMQueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);
BOOL OEMQueryPerformanceFrequency(LARGE_INTEGER* lpFrequency);
void OEMNotifyThreadExit(DWORD dwThrdId, DWORD dwExitCode);
void OEMNotifyReschedule(DWORD dwThrdId, DWORD dwPrio, DWORD dwQuantum, DWORD dwFlags);
DWORD OEMNotifyIntrOccurs(DWORD dwSysIntr);
VOID OEMUpdateReschedTime(DWORD dwTick);
DWORD OEMEnumExtensionDRAM(PMEMORY_SECTION pMemSections, DWORD dwMemSections);
DWORD OEMCalcFSPages(DWORD dwMemPages, DWORD dwDefaultFSPages);
void OEMInitCoProcRegs(LPBYTE pArea);
void OEMSaveCoProcRegs(LPBYTE pArea);
void OEMRestoreCoProcRegs(LPBYTE pArea);
DWORD OEMReadRegistry(DWORD dwFlags, LPBYTE pBuf, DWORD len);
BOOL OEMWriteRegistry (DWORD dwFlags, LPBYTE pBuf, DWORD len);
void OEMProfilerTimerEnable(DWORD dwUSec);
void OEMProfilerTimerDisable(void);
BOOL OEMIsRom(DWORD dwShiftedPhysAddr);
void OEMMapW32Priority(int nPrios, LPBYTE pPrioMap);
BOOL OEMMpStartAllCPUs(PLONG pnCpus, FARPROC pfnContinue);
DWORD OEMMpPerCPUInit(void);
BOOL OEMMpCpuPowerFunc(DWORD dwProcessor, BOOL fOnOff, DWORD dwHint);
void OEMIpiHandler(DWORD dwCommand, DWORD dwData);
BOOL OEMSendIPI(DWORD dwType, DWORD dwTarget);
void OEMIdleEx(LARGE_INTEGER *pliIdleTime);
void OEMInitInterlockedFunctions(void);
#if defined (ARM)
void OEMSaveVFPCtrlRegs(LPDWORD lpExtra, int nMaxRegs);
void OEMRestoreVFPCtrlRegs(LPDWORD lpExtra, int nMaxRegs);
BOOL OEMHandleVFPException(ULONG fpexc, EXCEPTION_RECORD* pExr, CONTEXT* pContext, DWORD* pdwReserved, BOOL fInKMode);
BOOL OEMIsVFPFeaturePresent(DWORD dwProcessorFeature);
BOOL OEMVFPCoprocControl(DWORD dwCommand);
void OEMPTEUpdateBarrier(LPVOID pte, DWORD cbSize);
#endif

// Declaration of KITL entry point
extern BOOL WINAPI KitlDllMain (HINSTANCE DllInstance, DWORD dwReason, LPVOID Reserved);

// Declaration of kernel security cookie for linking purposes
extern DWORD_PTR __security_cookie;
extern DWORD_PTR __security_cookie_complement;

// Declaration of kernel page pool parameters for linking purposes
extern NKPagePoolParameters pagePoolParams;

// ---------------------------------------------------------------------------
// OEMInitDebugSerial: REQUIRED
//
// This function initializes the debug serial port on the target device,
// useful for debugging OAL bringup.
//
// This is the first OAL function that the kernel calls, before the OEMInit
// function and before the kernel data section is fully initialized.
//
// OEMInitDebugSerial can use global variables; however, these variables might
// not be initialized and might subsequently be cleared when the kernel data
// section is initialized.
//
void OEMInitDebugSerial(void)
{

  // Fill in debug serial initialization code here.

  return;
}

// ---------------------------------------------------------------------------
// OEMInit: REQUIRED
//
// This function intializes device hardware as well as initiates the KITL
// debug transport.
//
// This is the second OAL function that the kernel calls.
//
// When the kernel calls OEMInit, interrupts are disabled and the kernel is
// unable to handle exceptions. The only kernel service available to this
// function is HookInterrupt.
//
void OEMInit(void)
{
  // Optionally customize function names for kernel entry points.
  RemapOALGlobalFunctions();

  // Optionally initialize OAL variables
  SetOALGlobalVariables();

  // Fill in hardware initialization code here.

  // Fill in KITL initiation here.

  return;
}

// ---------------------------------------------------------------------------
// CustomWriteDebugByte: CUSTOM
//
// This is an example function that kernel calls instead of OEMWriteDebugByte.
// We point the call to OEMWriteDebugByte here in the RemapOALFunctions
// function.
//
// This example function capitalizes any letters sent before passing it on
// to OEMWriteDebugByte to actually do the hardware write.  Provided you
// remapped the function pointer in OEMGlobal, you could do the hardware
// write here and simply not implement OEMWriteDebugByte.
//
void CustomWriteDebugByte(BYTE ch)
{
  if(ch >= 0x61 && ch <= 0x7A)
  {
    ch -= 32;
  }
  OEMWriteDebugByte(ch);

  return;
}

// ---------------------------------------------------------------------------
// RemapOALGlobalFunctions: CUSTOM
//
// The kernel calls OAL functions through a table of function pointers called
// OEMGlobal (see oemglobal.h for the full listing).  If you want to use a
// different function name for a required function, or use an optional
// function, simply change the pointer here.
//
void RemapOALGlobalFunctions(void)
{
  // Example remapping of a required function from default to a custom name:
  g_pOemGlobal->pfnWriteDebugByte = CustomWriteDebugByte;

  // Example mappings of optional functions.  Uncomment any line to map
  // (use) the optional function.
  //g_pOemGlobal->pfnWriteDebugByte = OEMWriteDebugByte;
  //g_pOemGlobal->pfnWriteDebugString = OEMWriteDebugString;
  //g_pOemGlobal->pfnReadDebugByte = OEMReadDebugByte;
  //g_pOemGlobal->pfnWriteDebugLED = OEMWriteDebugLED;
  //g_pOemGlobal->pfnInitClock = OEMInitClock;
  //g_pOemGlobal->pfnQueryPerfCounter = OEMQueryPerformanceCounter;
  //g_pOemGlobal->pfnQueryPerfFreq = OEMQueryPerformanceFrequency;
  //g_pOemGlobal->pfnNotifyThreadExit = OEMNotifyThreadExit;
  //g_pOemGlobal->pfnNotifyReschedule = OEMNotifyReschedule;
  //g_pOemGlobal->pfnNotifyIntrOccurs = OEMNotifyIntrOccurs;
  //g_pOemGlobal->pfnUpdateReschedTime = OEMUpdateReschedTime;
  //g_pOemGlobal->pfnEnumExtensionDRAM = OEMEnumExtensionDRAM;
  //g_pOemGlobal->pfnCalcFSPages = OEMCalcFSPages;
  //g_pOemGlobal->pfnInitCoProcRegs = OEMInitCoProcRegs;
  //g_pOemGlobal->pfnSaveCoProcRegs = OEMSaveCoProcRegs;
  //g_pOemGlobal->pfnRestoreCoProcRegs = OEMRestoreCoProcRegs;
  //g_pOemGlobal->pfnReadRegistry = OEMReadRegistry;
  //g_pOemGlobal->pfnWriteRegistry = OEMWriteRegistry;
  //g_pOemGlobal->pfnProfileTimerEnable= OEMProfilerTimerEnable;
  //g_pOemGlobal->pfnProfileTimerDisable = OEMProfilerTimerDisable;
  //g_pOemGlobal->pfnIsRom = OEMIsRom;
  //g_pOemGlobal->pfnMapW32Priority = OEMMapW32Priority;
  //g_pOemGlobal->pfnStartAllCpus = OEMMpStartAllCPUs;
  //g_pOemGlobal->pfnMpPerCPUInit = OEMMpPerCPUInit;
  //g_pOemGlobal->pfnMpCpuPowerFunc = OEMMpCpuPowerFunc;
  //g_pOemGlobal->pfnIpiHandler = OEMIpiHandler;
  //g_pOemGlobal->pfnSendIpi = OEMSendIPI;
  //g_pOemGlobal->pfnIdleEx = OEMIdleEx;
  //g_pOemGlobal->pfnInitInterlockedFunc = OEMInitInterlockedFunctions;

  // Set the KITL entry point.  This is already set by default to
  // KitlDllMain, but if we want to change it we can do so here.
  //g_pOemGlobal->pfnKITLGlobalInit = KitlDllMain;

  // The following optional functions are processor-specific, so they will
  // only exist when compiling for a certain cpu type
#if defined (ARM)
  //g_pOemGlobal->pfnSaveVFPCtrlRegs = OEMSaveVFPCtrlRegs;
  //g_pOemGlobal->pfnRestoreVFPCtrlRegs = OEMRestoreVFPCtrlRegs;
  //g_pOemGlobal->pfnHandleVFPExcp = OEMHandleVFPException;
  //g_pOemGlobal->pfnIsVFPFeaturePresent = OEMIsVFPFeaturePresent;
  //g_pOemGlobal->pfnVFPCoprocControl = OEMVFPCoprocControl;
  //g_pOemGlobal->pfnPTEUpdateBarrier = OEMPTEUpdateBarrier;
#endif

  return;
}

// ---------------------------------------------------------------------------
// SetOALGlobalVariables: CUSTOM
//
// The kernel uses several OAL global variables for configuration purposes.
// Any changes to these variables should generally be separated into more
// logical groups during OEMInit.
//
// Changing the variables is optional since they will all have benign
// default values (listed below).  This function is designed only to
// illustrate how you would override the defaults.
//
 void SetOALGlobalVariables(void)
{
  // Specifies the thread quantum for OS (scheduler period).
  g_pOemGlobal->dwDefaultThreadQuantum = DEFAULT_THREAD_QUANTUM;

  // Specifies the next available address following the first available
  // contiguous block of memory.  The kernel sets this variable before
  // OEMInit is called.  This should only be touched when extending
  // the contiguous memory range available the to kernel.
  //g_pOemGlobal->dwMainMemoryEndAddress = 0;

  // Specifies the size of the memory allocation, in bytes, needed for the
  // OEM to save or restore coprocessor registers. This variable is only
  // used if the particular platform or CPU has coprocessor registers that
  // must be saved or restored during context switches.
  g_pOemGlobal->cbCoProcRegSize = 0;

  // Controls whether the save/restore of coprocessor registers is
  // performed.
  g_pOemGlobal->fSaveCoProcReg = FALSE;

  // Specifies the watchdog period, in milliseconds, where the hardware
  // watchdog must be refreshed before system reset. The default value,
  // 0, indicates that the watchdog timer does not exist.
  g_pOemGlobal->dwWatchDogPeriod = 0;

  // Specifies the kernel watchdog thread priority.
  g_pOemGlobal->dwWatchDogThreadPriority = DEFAULT_WATCHDOG_PRIORITY;

  // Specifies the amount of memory for the error reporting dump area
  g_pOemGlobal->cbErrReportSize = 0;

  // Specifies XIP region(s)
  g_pOemGlobal->pROMChain = NULL;

  // Platform-specific information passed from the OAL to KITL
  g_pOemGlobal->pKitlInfo = NULL;

  // Specifies compiler /GS flag security cookies
  g_pOemGlobal->p__security_cookie = &__security_cookie;
  g_pOemGlobal->p__security_cookie_complement = &__security_cookie_complement;

  // Specifies the alarm resolution in ms
  g_pOemGlobal->dwAlarmResolution = DEFAULT_ALARMRESOLUTION_MSEC;

  // Specifies number of years for RTC rollover
  g_pOemGlobal->dwYearsRTCRollover  = 0;

  // Specifies platform capabilities such as Vector Floating Point support
  g_pOemGlobal->dwPlatformFlags = 0;

  // Set to the location of the kernel's page pool parameters, which are
  // used for controlling the size and behavior of the kernel page pool.
  g_pOemGlobal->pPagePoolParam = &pagePoolParams;

  // Try to keep 3 megabytes' of memory available for executable code
  pagePoolParams.Loader.Target = 3 * 1024 * 1024;

  // Try to keep 1 megabyte of memory available for memory-mapped files
  pagePoolParams.File.Target = 1 * 1024 * 1024;

  // Start a thread freeing pages when we dip below 1 megabyte's worth of pages
  g_pOemGlobal->cpPageOutLow = 1 * 1024 * 1024 / VM_PAGE_SIZE;

  // Stop the thread freeing pages when we rise above 3 megabytes' worth of pages
  g_pOemGlobal->cpPageOutHigh = 3 * 1024 * 1024 / VM_PAGE_SIZE;

  // Specifies whether multiprocessor support is enabled
  g_pOemGlobal->fMPEnable = FALSE;

#ifdef DEBUG
  // A reference to the OAL's debug zone settings DBGPARAM structure
  // This only exists in debug builds, thus the #ifdef.
  g_pOemGlobal->pdpCurSettings = &dpCurSettings;
#else
  g_pOemGlobal->pdpCurSettings = NULL;
#endif

  // The following variables are processor-specific, so they will
  // only exist when compiling for a certain cpu type
#if defined (x86)
  // Specifies the IPI vector (initialized to any invalid value)
  g_pOemGlobal->dwIpiVector = 0x10000;
#elif defined (ARM)
  // Specifies extra 1st level page table bits
  g_pOemGlobal->dwARM1stLvlBits = 0;

  // Specifies C and B bits (used to build the ARM CPU page tables).
  g_pOemGlobal->dwARMCacheMode = 0;

  // Indicates Instruction-Cache is Virtually Indexed Virtually
  // Tagged ASID-tagged - for ARMv6 only.
  g_pOemGlobal->f_V6_VIVT_ICache = 0;

  // Specifies cache bits for page table access (inner/outer)
  g_pOemGlobal->dwPageTableCacheBits = 0;

  // Specifies cache bits for page tables in Translation Table Base
  // Register (TTBR) if page table is cacheable (inner/outer)
  g_pOemGlobal->dwTTBRCacheBits = 0;
#elif defined (MIPS)
  // Specifies the bits to enable the platform-specific coprocessor
  g_pOemGlobal->dwCoProcBits = MIPS_DEFAULT_FPU_ENABLE;

  // Specifies the last index for the TLB which corresponds to the size
  // of the TLB minus 1.
  g_pOemGlobal->dwOEMTLBLastIdx = 0;

  // Specifies the architecture flag override value.  If the default
  // value is used, the kernel attempts to auto-detect all architecture
  // flags.
  g_pOemGlobal->dwArchFlagOverride = MIPS_FLAG_NO_OVERRIDE;

  // Pointers to arrays that provides the kernel with
  // information about which nested interrupts are masked while the
  // current interrupt is being handled.  This must be initialized;
  // while NULL is a compilable default, the tables must be
  // populated for the kernel to function on MIPS CPUs.
  // Pointer to 64 bytes
  g_pOemGlobal->pIntrPrio = NULL;
  // Pointer to 8 bytes
  g_pOemGlobal->pIntrMask = NULL;
#elif defined (SHx)
  // Specifies the interrupt event code length for SHx processors
  g_pOemGlobal->dwSHxIntEventCodeLength = SH4_INTEVT_LENGTH;
#endif

  return;
}


