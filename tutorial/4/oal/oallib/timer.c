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
// OEMInitClock: OPTIONAL
//
// This function is obsolete and its functionality should typically be
// moved to OEMPowerOff.
//
// This function initializes the clock after the OAL returns from
// OEMPowerOff.  The kernel calls OEMPowerOff first, then this function (if
// it is implemented).
//
void OEMInitClock(void)
{
  // Fill in timer code here.

  return;
}

// ---------------------------------------------------------------------------
// OEMGetRealTime: REQUIRED
//
// This function is called by the kernel to retrieve the time from the
// real-time clock.
//
BOOL OEMGetRealTime(LPSYSTEMTIME lpst)
{
  // Fill in timer code here.

  return TRUE;
}

// ---------------------------------------------------------------------------
// OEMSetRealTime: REQUIRED
//
// This function is called by the kernel to set the real-time clock.
//
BOOL OEMSetRealTime(LPSYSTEMTIME lpst)
{
  // Fill in timer code here.

  return TRUE;
}

// ---------------------------------------------------------------------------
// OEMSetAlarmTime: REQUIRED
//
// This function is called by the kernel to set the real-time clock alarm.
//
BOOL OEMSetAlarmTime(LPSYSTEMTIME lpst)
{
  // Fill in timer code here.

  return TRUE;
}

// ---------------------------------------------------------------------------
// OEMQueryPerformanceCounter: OPTIONAL
//
// This function retrieves the current value of the high-resolution
// performance counter.
//
// This function is optional.  Generally, it should be implemented for
// platforms that provide timer functions with higher granularity than
// OEMGetTickCount.
//
BOOL OEMQueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount)
{
  // Fill in high-resolution timer code here.

  return TRUE;
}

// ---------------------------------------------------------------------------
// OEMQueryPerformanceFrequency: OPTIONAL
//
// This function retrieves the frequency of the high-resolution
// performance counter.
//
// This function is optional.  Generally, it should be implemented for
// platforms that provide timer functions with higher granularity than
// OEMGetTickCount.
//
BOOL OEMQueryPerformanceFrequency(LARGE_INTEGER* lpFrequency)
{
  // Fill in high-resolution timer frequency code here.

  return TRUE;
}

// ---------------------------------------------------------------------------
// OEMGetTickCount: REQUIRED
//
// For Release configurations, this function returns the number of
// milliseconds since the device booted, excluding any time that the system
// was suspended. GetTickCount starts at zero on boot and then counts up from
// there.
//
// For debug configurations, 180 seconds is subtracted from the
// number of milliseconds since the device booted. This enables code that
// uses GetTickCount to be easily tested for correct overflow handling.
//
DWORD OEMGetTickCount(void)
{
  // Fill in timer code here.

  return 0;
}

// ---------------------------------------------------------------------------
// OEMUpdateReschedTime: OPTIONAL
//
// This function is called by the kernel to set the next reschedule time.  It
// is used in variable-tick timer implementations.
//
// It must set the timer hardware to interrupt at dwTick time, or as soon as
// possible if dwTick has already passed.  It must save any information
// necessary to calculate the g_pNKGlobal->dwCurMSec variable correctly.
//
VOID OEMUpdateReschedTime(DWORD dwTick)
{
  // Fill in timer code here.

  return;
}

// ---------------------------------------------------------------------------
// OEMRefreshWatchDog: OPTIONAL
//
// This function is called by the kernel to refresh the hardware watchdog
// timer.
//
void OEMRefreshWatchDog(void)
{
  // Fill in watchdog code here.

  return;
}

// ---------------------------------------------------------------------------
// OEMProfilerTimerEnable: OPTIONAL
//
// This function enables an optional profiler interrupt.
//
void OEMProfilerTimerEnable(DWORD dwUSec)
{
  // Fill in profiler code here.

  return;
}

// ---------------------------------------------------------------------------
// OEMProfilerTimerDisable: OPTIONAL
//
// This function disables an optional profiler interrupt.
//
void OEMProfilerTimerDisable(void)
{
  // Fill in profiler code here.

  return;
}

