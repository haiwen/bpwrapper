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
CBPWrapperExceptionHandler newCBPWrapperExceptionHandler(const char *dump_dir)
{
    printf("init Simple breakpad\n");
    google_breakpad::MinidumpDescriptor descriptor(dump_dir);
    return reinterpret_cast<void*>(new google_breakpad::ExceptionHandler(
        descriptor, NULL, DumpCallback, NULL, true, -1));
}
}
#endif

#ifdef WIN32

wchar_t *utf8ToWString(const std::string& src)
{
    wchar_t dst[4096];
    int len;

    len = MultiByteToWideChar
        (CP_UTF8,                        /* multibyte code page */
         0,                              /* flags */
         src.c_str(),                    /* src */
         -1,                             /* src len, -1 for all includes \0 */
         dst,                            /* dst */
         sizeof(dst) / sizeof(wchar_t)); /* dst buf len */

    if (len <= 0) {
        return NULL;
    }

    return wcsdup(dst);
}

std::string wStringToUtf8(const wchar_t *src)
{
    char dst[4096];
    int len;

    len = WideCharToMultiByte
        (CP_UTF8,               /* multibyte code page */
         0,                     /* flags */
         src,                   /* src */
         -1,                    /* src len, -1 for all includes \0 */
         dst,                   /* dst */
         sizeof(dst),           /* dst buf len */
         NULL,                  /* default char */
         NULL);                 /* BOOL flag indicates default char is used */

    if (len <= 0) {
        return "";
    }

    return dst;
}

std::string wStringToLocale(const wchar_t *src)
{
    char dst[4096];
    int len;

    len = WideCharToMultiByte
        (CP_ACP,        /* multibyte code page */
         0,             /* flags */
         src,           /* src */
         -1,            /* src len, -1 for all includes \0 */
         dst,           /* dst */
         sizeof(dst),   /* dst buf len */
         NULL,          /* default char */
         NULL);         /* BOOL flag indicates default char is used */

    if (len <= 0) {
        return "";
    }

    return dst;
}

bool DumpCallback(const wchar_t* dump_path,
                  const wchar_t* minidump_id,
                  void* context,
                  EXCEPTION_POINTERS* exinfo,
                  MDRawAssertionInfo* assertion,
                  bool succeeded)
{
    printf("succeeded = %s\n", succeeded ? "true" : "false");
    printf("Dump path: %s\n", wStringToLocale(dump_path));
    printf("len(dump_path) = %d\n", wcslen(dump_path));
    printf("Dump id: %s\n", wStringToLocale(minidump_id));
    printf("len(minidump_id) = %d\n", wcslen(minidump_id));
    return succeeded;
}


extern "C" {
CBPWrapperExceptionHandler newCBPWrapperExceptionHandler(const char *dump_dir)
{
    printf("initializing breakpad exception handler\n");
    std::wstring path = utf8ToWString(dump_dir);
    return reinterpret_cast<void*>(new google_breakpad::ExceptionHandler(
        path, NULL,
        (google_breakpad::ExceptionHandler::MinidumpCallback)DumpCallback, NULL,
        google_breakpad::ExceptionHandler::HANDLER_ALL));
}
}
#endif
