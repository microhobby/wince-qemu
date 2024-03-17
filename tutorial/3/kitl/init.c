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
#include <kitl.h>
#include <pkfuncs.h>
#include <ceddk.h>
#include <oal_kitl.h>
#include <bsp_ethdrv.h>

// Init.c
// The comments in this file will vary from OS version to version.
//
// All KITL functions in the template BSP fall into one of three categories:
// REQUIRED - you must implement this function for platform\common-compliant
// KITL functionality
// OPTIONAL - you may implement this function to enable specific functionality
// CUSTOM   - this function is a helper function specific to this BSP
//

// This describes the driver implemented in the KITL Ethernet driver library
// implemented in ..\ethdrv
OAL_KITL_ETH_DRIVER Bsp_Kitl_Ethdrv = {
    KITLEthdrvInit, KITLEthdrvInitDMABuffer, KITLEthdrvDeInit,
    KITLEthdrvSendFrame, KITLEthdrvGetFrame, KITLEthdrvEnableInts,
    KITLEthdrvDisableInts, KITLEthdrvPowerOff, KITLEthdrvPowerOn,
    KITLEthdrvCurrentPacketFilter, KITLEthdrvMulticastList
};

//------------------------------------------------------------------------------
//
// OEMKitlStartup: REQUIRED
//
// This function is the first OEM code that executes in kitl.dll.  It is called
// by the kernel after the BSP calls KITLIoctl( IOCTL_KITL_STARTUP, ... ) in
// OEMInit().  This function should set up internal state, read any boot
// arguments, and call the KitlInit function to initialize KITL in active
// (immediate load) or passive (delay load) mode.
//
// This version uses the platform\common code which is accessible through
// the OALKitlInit function.
//
// To use it, OEMKitlStartup needs to initialize an OAL_KITL_DEVICE and 
// an OAL_KITL_ARGS structure, then call OALKitlInit (which will assume
// responsibility for calling the kernel's KitlInit function.)
//
BOOL OEMKitlStartup()
{
  OAL_KITL_ARGS kitlArgs;
  OAL_KITL_DEVICE kitlDevice;

  DEVICE_LOCATION kitlDevLoc;

  // Set up the device name (byte string).  This should match the
  // bootloader's name.
  UCHAR kitlDeviceName[KITL_MAX_DEV_NAMELEN] = "";

  // Set up the device location structure for the KITL, this will be used
  // in both the OAL_KITL_ARGS and OAL_KITL_DEVICE structures.

  // Set up the interface type according to ceddk.h.  PCIBus is a typical
  // interface type.  If the interface is set to InterfaceTypeUndefined,
  // the platform\common code will use devLoc.Pin for the IRQ of the
  // device.  Otherwise it will query the OAL for the device IRQ using
  // IOCTL_HAL_REQUEST_IRQ.
  kitlDevLoc.IfcType = InterfaceTypeUndefined;

  // Set up the location information for our KITL device.  This will be
  // passed to the KITL driver's Init function during OEMKitlInit, and
  // also to the OEM-specific OAL implementation of OALIntrRequestIrqs
  // during IOCTL_HAL_REQUEST_IRQ (unless the interface type is undefined).
  //
  // In this sample we'll assume the KITL device IRQ is known ahead of time,
  // so the device location information is not relevant.  For a device on
  // a bus this information is important.  See pkfuncs.h for a description
  // of what the values mean for a PCI bus.
  kitlDevLoc.BusNumber = 0;
  kitlDevLoc.LogicalLoc = 0;
  kitlDevLoc.PhysicalLoc = 0;
  
  // Since we're using InterfaceTypeUndefined the Pin represents the IRQ for
  // the KITL device.
  kitlDevLoc.Pin = 0;

  // Initialize the OAL_KITL_ARGS structure.

  // Initialize platform\common-specific KITL arguments, uncomment any of
  // the following flags to use them.

  // Flags are defined in platform\common's oal_kitl.h.
  kitlArgs.flags = 

    // You must set this flag to enable KITL functionality.
       OAL_KITL_FLAGS_ENABLED

    // Initialize KITL to passive (delay load) mode, leaving it inactive
    // until a KITL client registers.
    // | OAL_KITL_FLAGS_PASSIVE

    // Initialize KITL to acquire a DHCP address (or reuse the DHCP
    // address set up by the bootloader).
       | OAL_KITL_FLAGS_DHCP

    // Initialize KITL as a Virtual Miniport adapter, meaning it will
    // act as both a debug device and a network miniport device (albeit
    // with much slower performance).  This is implemented entirely in
    // platform\common so no additional code is needed to support it.
    // | OAL_KITL_FLAGS_VMINI

    // Initialize KITL in polling mode, meaning no interrupts will be used
    // for the KITL device.  This is typically much slower performance, but
    // good for isolating KITL driver interrupt problems.
    // | OAL_KITL_FLAGS_POLL

    // Use platform\common's OALKitlCreateDeviceName to hash the last
    // two bytes of the MAC address and add them to the device name set up
    // here.  This flag should match the bootloader's use.
    // | OAL_KITL_FLAGS_EXTNAME
    ;

  kitlArgs.devLoc = kitlDevLoc;

  // Initialize the OAL_KITL_DEVICE structure

  // Set up the device name (unicode string).  This should match the
  // bootloader's name.
  kitlDevice.name = L"";

  // Initialize the interface name.  Currently unused by platform\common code.
  kitlDevice.ifcType = 0;  

  // Initialize the id of the KITL device.  This is used by the
  // platform\common code to match our KITL device we're using against the
  // list of supported OAL_KITL_DEVICEs.  In this sample we only have
  // one supported device but if we support several how we setup the id
  // will determine which device we use.
  //
  // For InterfaceTypeUndefined and Internal interface types, the id
  // should match the LogicalLoc of the device location.
  //
  // For PCIBus interface type, the id should match the PCI Vendor and Device
  // IDs of the device (bits 0-15 vendor ID, bits 16-31 device ID)
  kitlDevice.id = kitlDevLoc.LogicalLoc;

  // Initialize the resource identifier.  Currently unused by platform\common
  // code.
  kitlDevice.resource = 0;

  // Initialize the driver type.  We're supporting the default Ethernet
  // KITL debug transport, so the type is OAL_KITL_TYPE_ETH.
  kitlDevice.type = OAL_KITL_TYPE_ETH;

  // Initialize the driver pointer to our defined set of Ethernet KITL
  // functions.  These are prototyped in bsp_ethdrv.h and implemented in
  // the driver library.
  kitlDevice.pDriver = &Bsp_Kitl_Ethdrv;

  // Finally, call the platform\common code to use the structures we just
  // set up; it will call KitlInit in the kernel.
  return OALKitlInit (kitlDeviceName, &kitlArgs, &kitlDevice);
}

// ---------------------------------------------------------------------------
// OEMKitlInit:
//
// The platform\common code implements this function in the oal_kitl library.
// It uses the structures initialized in OEMKitlStartup.  So when using the
// platform\common implementation, it's not necessary to write any code for
// OEMKitlInit.
//

// ---------------------------------------------------------------------------
// dpCurSettings: REQUIRED
//
// The platform\common code defines this variable in the kitl_log library.
// So when using the platform\common implementation, it's not necessary to
// write any code for dpCurSettings.
//