#include "c_bpwrapper.h"
#include <stdio.h>

void crash()
{
  volatile int* a = (int*)(NULL);
  *a = 1;
}


int main(int argc, char* argv[])
{
  CBPWrapperExceptionHandler eh;
  eh = newCBPWrapperExceptionHandler();
  crash();
  return 0;
}
