#include <stdio.h>
#include "userial.h"

const char test[] = "Hello world!\n";

int main (void)
{
  unsigned char c = 0;

  us_init();

  printf ("Writing to serial port\r\n");
  
  us_aprintf("%s", test);


  for(c=0; c<11; ++c)
  {
    us_aprintf("Test %d\n", c);
  }

  return 0;
}
