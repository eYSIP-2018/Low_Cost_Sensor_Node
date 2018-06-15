#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__

  #define rf24_max(a,b) (a>b?a:b)
  #define rf24_min(a,b) (a<b?a:b)

  #if defined SPI_HAS_TRANSACTION && !defined SPI_UART && !defined SOFTSPI
    #define RF24_SPI_TRANSACTIONS
  #endif
  const uint32_t RF24_SPI_SPEED = 10000000;  
  #include "SPI.h"
  #define _SPI SPI 
  #include <stdint.h>
  #include <stdio.h>
  #include <string.h>
  #define _BV(x) (1<<(x))

   typedef uint16_t prog_uint16_t;
   #define PSTR(x) (x)
   #define printf_P printf
   #define strlen_P strlen
   #define PROGMEM
   #define pgm_read_word(p) (*(p))
   #define PRIPSTR "%s"
#endif // __RF24_CONFIG_H__

