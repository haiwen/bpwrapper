#include "c_bpwrapper.h"
#include <stdio.h>

void crash()
{
  volatile int* a = (int*)(NULL);
  *a = 1;
}


int main(int argc, char* argv[])
{
  const char *dump_path = "test.dmp";
  if (argc > 1) {
      dump_path = argv[1];
  }
  newCBPWrapperExceptionHandler(dump_path);
  crash();
  return 0;
}
