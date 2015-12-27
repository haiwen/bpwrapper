#include <client/linux/handler/exception_handler.h>
#include <client/linux/handler/minidump_descriptor.h>
#include <stdio.h>

#include "c_bpwrapper.h"

bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context,
                  bool succeeded)
{
    printf("Dump path: %s\n", descriptor.path());
    return succeeded;
}

extern "C" {
CBPWrapperExceptionHandler newCBPWrapperExceptionHandler(void)
{
    printf("init Simple breakpad\n");
    google_breakpad::MinidumpDescriptor descriptor(".");
    return reinterpret_cast<void*>(new google_breakpad::ExceptionHandler(
        descriptor, NULL, DumpCallback, NULL, true, -1));
}
}
