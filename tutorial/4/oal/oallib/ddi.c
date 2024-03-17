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
#include <nkexport.h>
#include <ddhal.h>
#include <wingdi.h>

// ddi.c
// The comments in this file will vary from OS version to version.
//
// This file implements functions that support the IOCTL_HAL_DDI handler.
//
// All functions in this file fall into one of three categories:
// REQUIRED - you must implement this function for HALFlat functionality
// OPTIONAL - you may implement this function to enable specific
//            HALFlat functionality, however you must implement a stub
//            at the minimum.
// 
// Since all of the HALFlat functions are called through OEMIoControl,
// the names are modifiable so long as the caller is modified to match.  The
// only things held constant are the IOCTL codes.
//

// Function prototypes
static BOOL GetNumModes(PVOID lpOutBuf, DWORD nOutBufSize,
                        LPDWORD lpBytesReturned);
static BOOL GetModeInfo(ULONG modeId, PVOID lpOutBuf, DWORD nOutBufSize,
                        LPDWORD lpBytesReturned);
static BOOL SetMode(ULONG modeId);
static BOOL SetPalette(const LPVOID lpInBuf, DWORD nInBufSize);
static BOOL Power(BOOL powerOff);

// ---------------------------------------------------------------------------
// OALIoctlHalDdi: REQUIRED
//
// This function is the general-purpose handler for the IOCTL_HAL_DDI code.
// It calls the appropriate subhandler function based on the subcode.  Any
// of the optional HALFlat subcode handlers that are implemented as stubs
// may be omitted from this function, but all subcodes are handled here for
// demonstration's sake.
//
BOOL OALIoctlHalDdi(DWORD dwIoControlCode, const LPVOID lpInBuf, DWORD nInBufSize,
                    PVOID lpOutBuf, DWORD nOutBufSize,
                    LPDWORD lpBytesReturned)
{
  BOOL powerOff, rc = FALSE;
  ULONG modeId, subCode = 0;
  const PALETTEENTRY* paletteInBuf;
  DWORD paletteBufSize;

  // Validate inputs
  if (lpInBuf == NULL || nInBufSize < sizeof(ULONG))
  {
    NKSetLastError(ERROR_INVALID_PARAMETER);
    if (lpBytesReturned != NULL) *lpBytesReturned = 0;
    goto cleanUp;
  }

  // Since we're called by a kernel-mode driver, we can trust this buffer
  subCode = (*(const ULONG*)lpInBuf);

  switch (subCode)
  {
    case DDHAL_COMMAND_GET_NUM_MODES:
      rc = GetNumModes(lpOutBuf, nOutBufSize, lpBytesReturned);
      break;
    case DDHAL_COMMAND_GET_MODE_INFO:
      if (nInBufSize < 2 * sizeof(ULONG))
      {
        NKSetLastError(ERROR_INVALID_PARAMETER);
        if (lpBytesReturned != NULL) *lpBytesReturned = 0;
        goto cleanUp;
      }
      modeId = ((ULONG*)lpInBuf)[1];
      rc = GetModeInfo(modeId, lpOutBuf, nOutBufSize, lpBytesReturned);
      break;
    case DDHAL_COMMAND_SET_MODE:
      if (lpBytesReturned != NULL) *lpBytesReturned = 0;
      if (nInBufSize < 2 * sizeof(ULONG))
      { 
        NKSetLastError(ERROR_INVALID_PARAMETER);
        goto cleanUp;
      }
      modeId = ((ULONG*)lpInBuf)[1];
      rc = SetMode(modeId);
      break;
    case DDHAL_COMMAND_SET_PALETTE:
      if (lpBytesReturned != NULL) *lpBytesReturned = 0;
      // SetPalette uses more from the input buffer,
      // so skip the DDHAL_COMMAND parameter.
      paletteInBuf = (const PALETTEENTRY*)((UCHAR*)lpInBuf + sizeof(ULONG));
      paletteBufSize = nInBufSize - sizeof(ULONG);
      rc = SetPalette(lpInBuf, nInBufSize);  
      break;
    case DDHAL_COMMAND_POWER:
      if (nInBufSize < 2 * sizeof(ULONG))
      {
        NKSetLastError(ERROR_INVALID_PARAMETER);
        goto cleanUp;
      }
      powerOff = ((ULONG*)lpInBuf)[1];
      rc = Power(powerOff);
  }
    
cleanUp:
  return rc;
}

// ---------------------------------------------------------------------------
// GetNumModes: REQUIRED
//
// This function returns the number of display modes supported by the
// HALFlat implementation.
//
static BOOL GetNumModes(PVOID lpOutBuf, DWORD nOutBufSize,
                        LPDWORD lpBytesReturned)
{
  // Fill in number of supported modes code here.

  return TRUE;
}

// ---------------------------------------------------------------------------
// GetModeInfo: REQUIRED
//
// This function returns information about the requested display mode in
// the form of a DDHAL_MODE_INFO structure followed by a UINT32 for each
// (optional) palette color.
//
static BOOL GetModeInfo(ULONG modeId, PVOID lpOutBuf, DWORD nOutBufSize,
                        LPDWORD lpBytesReturned)
{
  // Fill in mode information code here.

  return TRUE;
}

//------------------------------------------------------------------------------
// SetMode: REQUIRED
//
// This function sets the hardware to the mode specified.
//
static BOOL SetMode(ULONG modeId)
{
  // Fill in mode code here

  return TRUE;
}    

//------------------------------------------------------------------------------
// SetPalette: OPTIONAL
//
// This function sets the current color palette to the input index.
//
static BOOL SetPalette(const LPVOID lpInBuf, DWORD nInBufSize)
{
  // Fill in palette code here.

  return TRUE;
}

//------------------------------------------------------------------------------
// Power: OPTIONAL
//
// This function implements the power code for the display driver, turning the
// hardware on or off according to the input.
//
static BOOL Power(BOOL powerOff)
{
  // Fill in power code here

  return TRUE;
}    
