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
#include <nkexport.h>
#include "mmio.h"

struct civil_date
{
	int y;
	unsigned int m;
	unsigned int d;
};

int days_from_civil(struct civil_date t)
{
	int y = t.y;
	unsigned int m = t.m, d = t.d;

	int era;
	unsigned int yoe, doy, doe;

    y -= m <= 2;
    era = (y >= 0 ? y : y-399) / 400;
    yoe = (unsigned int)(y - era * 400);
    doy = (153*(m > 2 ? m-3 : m+9) + 2)/5 + d-1;
    doe = yoe * 365 + yoe/4 - yoe/100 + doy;
    return era * 146097 + (int)doe - 719468;
}

struct civil_date civil_from_days(int z)
{
	int era, y;
	unsigned int doe, yoe, doy, mp, d, m;
	struct civil_date out;

	z += 719468;
    era = (z >= 0 ? z : z - 146096) / 146097;
    doe = (unsigned int)(z - era * 146097);
    yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;
    y = (int)yoe + era * 400;
    doy = doe - (365*yoe + yoe/4 - yoe/100);
    mp = (5*doy + 2)/153;
    d = doy - (153*mp+2)/5 + 1;
    m = mp < 10 ? mp+3 : mp-9;
	out.y = y + (m <= 2);
	out.m = m;
	out.d = d;
    return out;
}

unsigned int weekday_from_days(int z)
{
	return (unsigned int)(z >= -4 ? (z+4) % 7 : (z+5) % 7 + 6);
}

// ---------------------------------------------------------------------------
// OEMGetRealTime: REQUIRED
//
// This function is called by the kernel to retrieve the time from the
// real-time clock.
//

BOOL OEMGetRealTime(LPSYSTEMTIME lpst)
{
	DWORD timestamp = mmio_read(RTC_BASE + RTCDR);
	DWORD days = timestamp / 86400;
	DWORD seconds = timestamp % 86400;
	struct civil_date out = civil_from_days(days);

	lpst->wYear = out.y;
	lpst->wMonth = out.m;
	lpst->wDay = out.d;
	lpst->wDayOfWeek = weekday_from_days(days);

	lpst->wHour = (WORD)(seconds / 3600);
	lpst->wMinute = (seconds % 3600) / 60;
	lpst->wSecond = (seconds % 3600) % 60;
	lpst->wMilliseconds = 0;

	return TRUE;
}

DWORD convert_date(LPSYSTEMTIME lpst)
{
	struct civil_date t;
	int days;

	t.y = lpst->wYear;
	t.m = lpst->wMonth;
	t.d = lpst->wDay;
	days = days_from_civil(t);

	return days * 86400 + lpst->wHour * 3600 + lpst->wMinute * 60 + lpst->wSecond;
}

// ---------------------------------------------------------------------------
// OEMSetRealTime: REQUIRED
//
// This function is called by the kernel to set the real-time clock.
//
BOOL OEMSetRealTime(LPSYSTEMTIME lpst)
{
	DWORD timestamp = convert_date(lpst);
	mmio_write(RTC_BASE + RTCLR, timestamp);

	return TRUE;
}

// ---------------------------------------------------------------------------
// OEMSetAlarmTime: REQUIRED
//
// This function is called by the kernel to set the real-time clock alarm.
//
BOOL OEMSetAlarmTime(LPSYSTEMTIME lpst)
{
	DWORD timestamp = convert_date(lpst);
	mmio_write(RTC_BASE + RTCMR, timestamp);
	mmio_write(RTC_BASE + RTCIMSC, 1);

	return TRUE;
}

uint32_t update_timer(void);

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
	unsigned long long us = update_timer();
	unsigned long long msec = CurMSec;

	lpPerformanceCount->QuadPart = msec * 1000 + us;

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
	lpFrequency->QuadPart = 1000000;

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
	return CurMSec;
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
	DWORD interval = 1;
	DWORD us;

	us = update_timer();
	//DEBUGMSG(1, (TEXT("OEMUpdateReschedTime %u, %u\r\n"), CurMSec, dwTick));

	if (dwTick > CurMSec)
		interval = (dwTick - CurMSec) * 1000 - us;

	mmio_write(SP804_BASE2 + TimerLoad, interval);
	mmio_write(SP804_BASE2 + TimerControl, (1 << 7) | (1 << 5) | (1 << 1) | (1 << 0)); // enable, interrupt, 32bit, oneshot
}

// ---------------------------------------------------------------------------
// OEMRefreshWatchDog: OPTIONAL
//
// This function is called by the kernel to refresh the hardware watchdog
// timer.
//
void OEMRefreshWatchDog(void)
{
	return;
}
