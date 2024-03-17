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
#include <ddhal.h>
#include "mmio.h"
#include <pwinuser.h>
#include <pkfuncs.h>

void lcd_config(int width, int height)
{
	mmio_write(LCD_BASE + LCDTiming0, (width / 16 - 1) << 2);
	mmio_write(LCD_BASE + LCDTiming1, height - 1);
	mmio_write(LCD_BASE + LCDUpbase, VRAM_ADDR);
	mmio_write(LCD_BASE + LCDControl, (1 << 11) | (1 << 8) | (1 << 0) | (5 << 1));
}

LPCWSTR platformtype_str = L"Pocket PC";
LPCWSTR platformoem_str = L"QEMU vexpress-a15";
LPCSTR deviceid_str = "QEMU_CE\0CE_QEMU";
BYTE uuid_data[] = { 0x14, 0x86, 0xec, 0xe5, 0x02, 0x7a, 0x4b, 0x7a, 0xb4, 0xe5, 0x73, 0xb3, 0x70, 0x77, 0x15, 0xd7 };
PLATFORMVERSION platformversion[] = {{7, 0}};

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
	DWORD function = (dwIoControlCode >> 2) & 0xFF;
	DWORD *inDword = (DWORD*)lpInBuf;
	DWORD *outDword = (DWORD*)lpOutBuf;
	DWORD cmd;
	DWORD bytes_copied;
	DDHAL_MODE_INFO *mode;
	DEVICE_ID *device_id;
	PROCESSOR_INFO *proc_info;

	switch (dwIoControlCode)
	{
	case IOCTL_HAL_INIT_RTC:
	case IOCTL_HAL_INITREGISTRY:
	case IOCTL_HAL_POSTINIT:
	case IOCTL_HAL_ENABLE_WAKE:
		return TRUE;
	case IOCTL_EDBG_IS_STARTED:
	case IOCTL_HAL_GET_POOL_PARAMETERS:
		return FALSE;
	case IOCTL_HAL_UNKNOWN_IRQ_HANDLER:
	case IOCTL_HAL_GET_HIVE_CLEAN_FLAG:
	case IOCTL_HAL_GET_RANDOM_SEED:
	case IOCTL_HAL_GET_HWENTROPY:
	case IOCTL_HAL_GET_FAST_COUNTER:
	case IOCTL_HAL_GET_FAST_COUNTER_INFO:
		NKSetLastError(ERROR_NOT_SUPPORTED);
		return FALSE;
	case IOCTL_HAL_GET_DEVICE_INFO:
		if (nInBufSize < 4) {
			NKSetLastError(ERROR_BAD_ARGUMENTS);
			return FALSE;
		}
		if (*inDword == SPI_GETPLATFORMTYPE || *inDword == SPI_GETPLATFORMNAME) {
			bytes_copied = (wcslen(platformtype_str) + 1) * 2;
			if (lpBytesReturned)
				*lpBytesReturned = bytes_copied;
			if (nOutBufSize < bytes_copied) {
				NKSetLastError(ERROR_INSUFFICIENT_BUFFER);
				return FALSE;
			}
			memcpy(lpOutBuf, platformtype_str, bytes_copied);
		} else if (*inDword == SPI_GETOEMINFO || *inDword == SPI_GETPROJECTNAME || *inDword == SPI_GETBOOTMENAME) {
			bytes_copied = (wcslen(platformoem_str) + 1) * 2;
			if (lpBytesReturned)
				*lpBytesReturned = bytes_copied;
			if (nOutBufSize < bytes_copied) {
				NKSetLastError(ERROR_INSUFFICIENT_BUFFER);
				return FALSE;
			}
			memcpy(lpOutBuf, platformoem_str, bytes_copied);
		} else if (*inDword == SPI_GETPLATFORMVERSION) {
			bytes_copied = sizeof(PLATFORMVERSION);
			if (lpBytesReturned)
				*lpBytesReturned = bytes_copied;
			if (nOutBufSize < bytes_copied) {
				NKSetLastError(ERROR_INSUFFICIENT_BUFFER);
				return FALSE;
			}
			memcpy(lpOutBuf, platformversion, bytes_copied);
		} else if (*inDword == SPI_GETUUID || *inDword == SPI_GETGUIDPATTERN) {
			bytes_copied = 16;
			if (lpBytesReturned)
				*lpBytesReturned = bytes_copied;
			if (nOutBufSize < bytes_copied) {
				NKSetLastError(ERROR_INSUFFICIENT_BUFFER);
				return FALSE;
			}
			memcpy(lpOutBuf, uuid_data, 16);
		} else {
			NKSetLastError(ERROR_NOT_SUPPORTED);
			return FALSE;
		}
		return TRUE;
	case IOCTL_HAL_GET_DEVICEID:
		if (nOutBufSize == 16) {
			if (lpBytesReturned)
				*lpBytesReturned = 16;
			memcpy(lpOutBuf, deviceid_str, 16);
			return TRUE;
		}
		if (lpBytesReturned)
			*lpBytesReturned = sizeof(DEVICE_ID) + 16;
		if (nOutBufSize < sizeof(DEVICE_ID) + 16) {
			NKSetLastError(ERROR_INSUFFICIENT_BUFFER);
			return FALSE;
		}
		device_id = (DEVICE_ID*)lpOutBuf;
		device_id->dwSize = sizeof(DEVICE_ID) + 16;
		device_id->dwPresetIDOffset = sizeof(DEVICE_ID);
		device_id->dwPresetIDBytes = 8;
		device_id->dwPlatformIDOffset = sizeof(DEVICE_ID) + 8;
		device_id->dwPlatformIDBytes = 8;
		memcpy(device_id + 1, deviceid_str, 16);
		return TRUE;
	case IOCTL_HAL_GET_UUID:
		if (lpBytesReturned)
			*lpBytesReturned = 16;
		if (nOutBufSize < 16) {
			NKSetLastError(ERROR_INSUFFICIENT_BUFFER);
			return FALSE;
		}
		memcpy(lpOutBuf, uuid_data, 16);
		return TRUE;
	case IOCTL_PROCESSOR_INFORMATION:
		if (lpBytesReturned)
			*lpBytesReturned = sizeof(PROCESSOR_INFO);
		if (nOutBufSize < sizeof(PROCESSOR_INFO)) {
			NKSetLastError(ERROR_INSUFFICIENT_BUFFER);
			return FALSE;
		}
		proc_info = (PROCESSOR_INFO*)lpOutBuf;
		memset(proc_info, 0, sizeof(PROCESSOR_INFO));
		proc_info->wVersion = 1;
		proc_info->szProcessCore[0] = L'A';
		proc_info->szProcessCore[1] = L'R';
		proc_info->szProcessCore[2] = L'M';
		proc_info->szProcessCore[3] = 0;
		proc_info->wCoreRevision = 1;
		proc_info->szProcessorName[0] = L'A';
		proc_info->szProcessorName[1] = L'1';
		proc_info->szProcessorName[2] = L'5';
		proc_info->szProcessorName[3] = 0;
		proc_info->wProcessorRevision = 1;
		proc_info->szVendor[0] = L'Q';
		proc_info->szVendor[1] = L'E';
		proc_info->szVendor[2] = L'M';
		proc_info->szVendor[3] = L'U';
		proc_info->szVendor[4] = 0;
		proc_info->dwInstructionSet = PROCESSOR_FLOATINGPOINT;
		proc_info->dwClockSpeed = 500000000;
		return TRUE;
	case IOCTL_HAL_QUERY_DISPLAYSETTINGS:
		if (lpBytesReturned)
			*lpBytesReturned = 3 * 4;
		if (nOutBufSize < 3 * 4) {
			NKSetLastError(ERROR_INSUFFICIENT_BUFFER);
			return FALSE;
		}
		// *(outDword + 0) = 1024;
		// *(outDword + 1) = 600;
		// vga
		*(outDword + 0) = 640;
		*(outDword + 1) = 480;
		*(outDword + 2) = 32;
		return TRUE;
	case IOCTL_HAL_DDI:
		if (nInBufSize < 4) {
			NKSetLastError(ERROR_BAD_ARGUMENTS);
			return FALSE;
		}
		cmd = *inDword;
		if (cmd == DDHAL_COMMAND_GET_NUM_MODES) {
			if (lpBytesReturned)
				*lpBytesReturned = 4;
			if (nOutBufSize < 4) {
				NKSetLastError(ERROR_INSUFFICIENT_BUFFER);
				return FALSE;
			}
			*outDword = 1;
			return TRUE;
		}
		if (cmd == DDHAL_COMMAND_GET_MODE_INFO) {
			if (nInBufSize < 8) {
				NKSetLastError(ERROR_BAD_ARGUMENTS);
				return FALSE;
			}
			if (*(inDword + 1) != 0) {
				NKSetLastError(ERROR_BAD_ARGUMENTS);
				return FALSE;
			}
			if (lpBytesReturned)
				*lpBytesReturned = sizeof(DDHAL_MODE_INFO);
			if (nOutBufSize < sizeof(DDHAL_MODE_INFO)) {
				NKSetLastError(ERROR_INSUFFICIENT_BUFFER);
				return FALSE;
			}
			mode = (DDHAL_MODE_INFO*)lpOutBuf;
			mode->modeId = 0;
			mode->flags = DDHAL_CACHE_FRAME_MEMORY;
			// mode->width = 1024;
			// mode->height = 600;
			// vga
			mode->width = 640;
			mode->height = 480;
			mode->bpp = 32;
			mode->frequency = 60;
			mode->format = EGPE_FORMAT_32BPP;
			mode->phFrameBase = VRAM_ADDR;
			// mode->frameSize = 1024 * 4 * 600;
			// mode->frameStride = 1024 * 4;
			// vga
			mode->frameSize = 640 * 4 * 480;
			mode->frameStride = 640 * 4;
			mode->paletteMode = PAL_BGR;
			mode->entries = 0;
			return TRUE;
		}
		if (cmd == DDHAL_COMMAND_SET_MODE) {
			if (nInBufSize < 8) {
				NKSetLastError(ERROR_BAD_ARGUMENTS);
				return FALSE;
			}
			if (*(inDword + 1) != 0) {
				NKSetLastError(ERROR_BAD_ARGUMENTS);
				return FALSE;
			}
			// lcd_config(1024, 600);
			// vga
			lcd_config(640, 480);
			return TRUE;
		}
		if (cmd == DDHAL_COMMAND_SET_PALETTE) {
			return TRUE;
		}
		if (cmd == DDHAL_COMMAND_POWER) {
			return TRUE;
		}

		NKSetLastError(ERROR_BAD_ARGUMENTS);
		return FALSE;
	}

	DEBUGMSG(1, (TEXT("OEMIoControl: unknown function %u\r\n"), function));
	NKSetLastError(ERROR_NOT_SUPPORTED);
	return FALSE;
}


// ---------------------------------------------------------------------------
// OEMIsProcessorFeaturePresent: OPTIONAL
//
// This function provides information about processor features and support.
//
BOOL OEMIsProcessorFeaturePresent(DWORD dwProcessorFeature)
{
  // Fill in processor feature code here.

	DEBUGMSG(1, (TEXT("OEMProcFeat\r\n")));
  return FALSE;
}


