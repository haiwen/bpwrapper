AM_CFLAGS = @BREAKPAD_CFLAGS@ \
	@BREAKPADCLIENT_CFLAGS@ \
	-Wall

check_PROGRAMS = test-bpwrapper

test_bpwrapper_SOURCES = test.c

test_bpwrapper_CFLAGS = -I$(top_srcdir)

test_bpwrapper_LDADD = @BREAKPAD_LIBS@ @BREAKPADCLIENT_LIBS@ -L$(top_srcdir) -lbpwrapper -lstdc++ -lpthread
