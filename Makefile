BPWRAPPER_LIB=libbpwrapper.a

all: $(BPWRAPPER_LIB)

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

testbp: $(BPWRAPPER_LIB) test.c
	$(CC) $(CFLAGS) -o $@ test.c $(LDFLAGS)

$(BPWRAPPER_LIB): c_bpwrapper.o
	ar rcs $(BPWRAPPER_LIB) c_bpwrapper.o

c_bpwrapper.o: c_bpwrapper.cpp
	$(CXX) $(CFLAGS) -o $@ -c -fPIC -I. $<

dumpsym: testbp
	./dumpsyms.sh

clean:
	rm -f *.o *.a testbp

bpclean:
	rm -rf *.dmp *.syms symbols/

walk:
	minidump_stackwalk *.dmp ./symbols/

install: $(BPWRAPPER_LIB)
	install -c -m 644 $(BPWRAPPER_LIB) /usr/local/lib

.phony: clean all dumpsym bpclean
