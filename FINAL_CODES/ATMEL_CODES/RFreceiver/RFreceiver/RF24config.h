#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__
// following used by the method forRF24 object 
// to find min and max size of paylaod (data) size 
  #define rf24_max(a,b) (a>b?a:b)
  #define rf24_min(a,b) (a<b?a:b)
// This is used for SPI transactions in RF24 library API
  #if defined SPI_HAS_TRANSACTION && !defined SPI_UART && !defined SOFTSPI
    #define RF24_SPI_TRANSACTIONS
  #endif  
  #include "SPI.h"
  #define _SPI SPI // SPI is object in SPI.h and _SPI is object in RF24
  // INcludes necessary header files
  #include <stdint.h>
  #include <stdio.h>
  #include <string.h> // to perform operation on string
  #define _BV(x) (1<<(x)) 
  //Following macros are used to access program/flash memory
   typedef uint16_t prog_uint16_t;
   #define PSTR(x) (x)
   #define printf_P printf
   #define strlen_P strlen
   // macro for  program memory access
   #define PROGMEM
   #define pgm_read_word(p) (*(p))
   #define PRIPSTR "%s"
#endif // __RF24_CONFIG_H__

