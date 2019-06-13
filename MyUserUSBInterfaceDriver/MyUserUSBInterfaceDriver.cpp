//
//  MyUserUSBInterfaceDriver.cpp
//  MyUserUSBInterfaceDriver
//
//  Created by Scott Knight on 6/13/19.
//  Copyright © 2019 Scott Knight. All rights reserved.
//

#include <os/log.h>

#include <DriverKit/IOUserServer.h>
#include <DriverKit/IOLib.h>
#include <USBDriverKit/IOUSBHostInterface.h>
#include <USBDriverKit/IOUSBHostPipe.h>

#include "MyUserUSBInterfaceDriver.h"

#define __Require(assertion, exceptionLabel)                               \
do                                                                      \
{                                                                       \
if ( __builtin_expect(!(assertion), 0) )                            \
{                                                                   \
goto exceptionLabel;                                            \
}                                                                   \
} while ( 0 )

#define __Require_Action(assertion, exceptionLabel, action)                \
do                                                                      \
{                                                                       \
if ( __builtin_expect(!(assertion), 0) )                            \
{                                                                   \
{                                                               \
action;                                                     \
}                                                               \
goto exceptionLabel;                                            \
}                                                                   \
} while ( 0 )

static const uint32_t kMyEndpointAddress = 1;

struct MyUserUSBInterfaceDriver_IVars
{
    IOUSBHostInterface       *interface;
    IOUSBHostPipe            *inPipe;
    OSAction                 *ioCompleteCallback;
    IOBufferMemoryDescriptor *inData;
    uint16_t                  maxPacketSize;
};

bool
MyUserUSBInterfaceDriver::init()
{
    bool result = false;
    
    os_log(OS_LOG_DEFAULT, "%s", __FUNCTION__);
    
    result = super::init();
    __Require(true == result, Exit);
    
    ivars = IONewZero(MyUserUSBInterfaceDriver_IVars, 1);
    __Require_Action(NULL != ivars, Exit, result = false);
    
Exit:
    return result;
}

kern_return_t
IMPL(MyUserUSBInterfaceDriver, Start)
{
    kern_return_t                    ret;
    IOUSBStandardEndpointDescriptors descriptors;
    
    os_log(OS_LOG_DEFAULT, "%s", __FUNCTION__);
    
    ret = Start(provider, SUPERDISPATCH);
    __Require(kIOReturnSuccess == ret, Exit);
    
    ivars->interface = OSDynamicCast(IOUSBHostInterface, provider);
    __Require_Action(NULL != ivars->interface, Exit, ret = kIOReturnNoDevice);
    
    ret = ivars->interface->Open(this, 0, NULL);
    __Require(kIOReturnSuccess == ret, Exit);
    
    ret = ivars->interface->CopyPipe(kMyEndpointAddress, &ivars->inPipe);
    __Require(kIOReturnSuccess == ret, Exit);
    
    ret = ivars->interface->CreateIOBuffer(kIOMemoryDirectionIn,
                                           ivars->maxPacketSize,
                                           &ivars->inData);
    __Require(kIOReturnSuccess == ret, Exit);
    
    ret = OSAction::Create(this,
                           MyUserUSBInterfaceDriver_ReadComplete_ID,
                           IOUSBHostPipe_CompleteAsyncIO_ID,
                           0,
                           &ivars->ioCompleteCallback);
    __Require(kIOReturnSuccess == ret, Exit);
    
    ret = ivars->inPipe->AsyncIO(ivars->inData,
                                 ivars->maxPacketSize,
                                 ivars->ioCompleteCallback,
                                 0);
    __Require(kIOReturnSuccess == ret, Exit);
    
    // WWDC slides don't show the full function
    // i.e. this is still unfinished
    
Exit:
    return ret;
}

kern_return_t
IMPL(MyUserUSBInterfaceDriver, Stop)
{
    kern_return_t ret = kIOReturnSuccess;
    
    os_log(OS_LOG_DEFAULT, "%s", __FUNCTION__);
    
    return ret;
}

void
MyUserUSBInterfaceDriver::free()
{
    os_log(OS_LOG_DEFAULT, "%s", __FUNCTION__);
}

void
IMPL(MyUserUSBInterfaceDriver, ReadComplete)
{
    os_log(OS_LOG_DEFAULT, "%s", __FUNCTION__);
}
