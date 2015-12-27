all: testbp

CC=gcc
CXX=g++

BP_CFLAGS=$(shell pkg-config --cflags breakpad breakpad-client)
BP_LIBS=$(shell pkg-config --libs breakpad breakpad-client)

CFLAGS += \
	-g -O0 \
	$(BP_CFLAGS)

LDFLAGS += \
	-L.	-lbpwrapper \
	$(BP_LIBS) \
	-lstdc++

BP_SYMBOLS_FILE=testbp.syms

testbp: libbpwrapper.a test.c
	$(CC) $(CFLAGS) -o $@ test.c $(LDFLAGS)

libbpwrapper.a: c_bpwrapper.o
	ar rcs libbpwrapper.a c_bpwrapper.o

c_bpwrapper.o: c_bpwrapper.cpp
	$(CXX) $(CFLAGS) -o $@ -c -fPIC -I. $<

dumpsym:
	./dumpsyms.sh

clean:
	rm -f *.o *.a testbp

bpclean:
	rm -rf *.dmp *.syms symbols/

walk:
	minidump_stackwalk *.dmp ./symbols/


.phony: clean all dumpsym bpclean
