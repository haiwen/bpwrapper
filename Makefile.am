ACLOCAL_AMFLAGS = -I m4

pcfiles = bpwrapper.pc
pkgconfig_DATA = $(pcfiles)
pkgconfigdir = $(libdir)/pkgconfig

AM_CPPFLAGS = @BREAKPAD_CFLAGS@ \
	@BREAKPADCLIENT_CFLAGS@ \
	-Wall -std=gnu++11

## library rules
lib_LTLIBRARIES = libbpwrapper.la

libbpwrapper_la_SOURCES = c_bpwrapper.cpp

libbpwrapper_la_LDFLAGS = -no-undefined
libbpwrapper_la_LIBADD = @BREAKPAD_LIBS@ @BREAKPADCLIENT_LIBS@

bpwrapperdir = $(includedir)
bpwrapper_HEADERS = c_bpwrapper.h

SUBDIRS = . tests
