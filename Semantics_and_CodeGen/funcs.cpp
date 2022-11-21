#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// all of your legacy C code here

int foo(int a, int b)
{
  printf("a + b is : %d\n", a+b);
  return a+b;
}

#ifdef __cplusplus
}
#endif