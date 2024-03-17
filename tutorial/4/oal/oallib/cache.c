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
// OEMCacheRangeFlush: REQUIRED
//
// This function is used by the kernel to flush or invalidate a certain range
// of the cache or translation look-aside buffer (TLB).
//
void OEMCacheRangeFlush(LPVOID pAddr, DWORD dwLength, DWORD dwFlags)
{
  // Fill in cache code here

  return;
}

