#include <stdio.h>
#include <cbm.h>

char rs232_read_buf[512];
char rs232_write_buf[512];

char** RIBUF = (char**)0x00f7;
char** ROBUF = (char**)0x00f9;

//bypass cc65 Charter translation
static unsigned char us_name1200[] = {0x08, 0x00, 0x00}; //1200 8N1

char us_buffer[256];

void us_putc(char c)
{
  cbm_k_ckout(2);
  cbm_k_bsout(c);
}

void us_printf( const char * format, ... )
{
  char k=0; 
  char c;
  va_list args;
  va_start (args, format);
  vsprintf (us_buffer,format, args);
  cbm_k_ckout(2);

  while(k<255) 
  {
    c = us_buffer[k];
    if (c == NULL)
      break;
    cbm_k_bsout(c);
    ++k;
  }
  va_end (args);
  cbm_k_clrch();
}

void us_init()
{

  *RIBUF = (char*)(((int)rs232_read_buf & 0xff00) + 256);
  *ROBUF = (char*)(((int)rs232_write_buf & 0xff00) + 256);

  // open rs232 channel
  cbm_k_setlfs (2,2,3);
  cbm_k_setnam (us_name1200);
  cbm_k_open ();
}

// unsigned char __fastcall__ (*cbm_k_getin)(void) = 0xffe4;

