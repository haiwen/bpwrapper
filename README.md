Introduction [![Build Status](https://secure.travis-ci.org/haiwen/bpwrapper.svg?branch=master)](http://travis-ci.org/haiwen/bpwrapper)
============

A simple plain C wrapper for C++ Google Breakpad.
What is Google Breakpad client library? Read about it here: [Getting Started With Breakpad](https://chromium.googlesource.com/breakpad/breakpad/+/816f242/docs/getting_started_with_breakpad.md)

# Why do I need it?

Actually, you don't need this wrapper, you need Google Breakpad. But Google Breakpad is a c++ library with c++ headers. So, if you have a plain C project, that you want Google Breakpad to use with, you will need simple wrapper.

# How to use it?

First, build and install breakpad library

```sh
git clone https://chromium.googlesource.com/breakpad/breakpad
cd breakpad
mkdir -p src/third_party/lss/
mkdir -p third_party/lss/ && cd third_party/lss/
git clone https://chromium.googlesource.com/linux-syscall-support
cp linux-syscall-support/*.h .
cp linux-syscall-support/*.h ../../src/third_party/lss/
cd -
./configure
make -j2
sudo make install
```

Now build this wrapper library:

```
git clone git@github.com:haiwen/bpwrapper.git
cd bpwrapper
./autogen.sh
./configure
make
sudo make install
```

Then:

- Modify the `main` function of your source code. See [tests/test.c](test.c) for example
- Link your program with `-lbpwrapper -lstdc++`

After that, each time the program crashes, a breakpad minidump file would be generated. See [breadpad doc](https://chromium.googlesource.com/breakpad/breakpad/+/816f242/docs/linux_starter_guide.md) about how to get a full stacktrace and other info from this minidump file.

[Here](example-trace.txt) is example output of running the breakpad `minidump_stackwalk` tool with a minidump. It provides useful information like the reason of crashing, strace trace of each thread, and OS information.
