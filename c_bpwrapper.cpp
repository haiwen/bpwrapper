#if defined(WIN32)
#include <client/windows/handler/exception_handler.h>
#elif defined(__linux__)
#include <client/linux/handler/exception_handler.h>
#include <client/linux/handler/minidump_descriptor.h>
#endif
#include <stdio.h>
#include <string>

#include "c_bpwrapper.h"

#ifdef __linux__
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
#endif

#ifdef WIN32

bool DumpCallback(const wchar_t* dump_path,
                  const wchar_t* minidump_id,
                  void* context,
                  EXCEPTION_POINTERS* exinfo,
                  MDRawAssertionInfo* assertion,
                  bool succeeded)
{
    wprintf(L"succeeded = %s\n", succeeded ? L"true" : L"false");
    wprintf(L"Dump path: %s\n", dump_path);
    wprintf(L"Dump id: %s\n", minidump_id);
    return succeeded;
}


extern "C" {
CBPWrapperExceptionHandler newCBPWrapperExceptionHandler(const char *dump_path)
{
    wprintf(L"init Simple breakpad\n");
    std::wstring path = std::to_wstring(123);
    return reinterpret_cast<void*>(new google_breakpad::ExceptionHandler(
        path, NULL,
        (google_breakpad::ExceptionHandler::MinidumpCallback)DumpCallback, NULL,
        google_breakpad::ExceptionHandler::HANDLER_ALL));
}
}
#endif
