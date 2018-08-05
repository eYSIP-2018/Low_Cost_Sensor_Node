
#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED
// for disbaling name transformation  of function form C file to cpp file 
extern "C"
{
	#include "gpio2.h"
};
// SPI_HAS_TRANSACTION means SPI has beginTransaction(), endTransaction(), 
#define SPI_HAS_TRANSACTION 1
class SPIClass {
public:
  // Initialize the SPI library
  static void begin();
  // Before using SPI.transfer() or asserting chip select pins,
  // this function is used to gain exclusive access to the SPI bus
  // and configure the correct settings.
  inline static void beginTransaction()
   {
    SPCR = 0x50;// fosc/4 , mode 0 ,master mode ,spi enable ,MSB first
    SPSR = 0x00;// no double data rate 
  }

  // Write to the SPI bus (MOSI pin) and also receive (MISO pin)
  inline static uint8_t transfer(uint8_t data) 
  {
    SPDR = data;
    /*
     * The following NOP introduces a small delay that can prevent the wait
     * loop form iterating when running at the maximum speed. This gives
     * about 10% more speed, even if it seems counter-intuitive. At lower
     * speeds it is unnoticed.
     */
    asm volatile("nop");
    while (!(SPSR & _BV(SPIF))) ; // wait
    return SPDR;
  }

  inline static void transfer(void *buf, size_t count)
   {
    if (count == 0) return;
    uint8_t *p = (uint8_t *)buf;
    SPDR = *p;
    while (--count > 0) {
      uint8_t out = *(p + 1);
      while (!(SPSR & _BV(SPIF))) ;
      uint8_t in = SPDR;
      SPDR = out;
      *p++ = in;
    }
    while (!(SPSR & _BV(SPIF))) ;
    *p = SPDR;
  }
  // After performing a group of transfers and releasing the chip select
  // signal, this function allows others to access the SPI bus
  inline static void endTransaction(void) 
  {
    
  }

  // Disable the SPI bus
  static void end();
};
extern SPIClass SPI;
#endif
