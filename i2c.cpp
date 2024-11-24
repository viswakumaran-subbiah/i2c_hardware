#include <avr/io.h>

#include "i2c.h"

void i2c_initialize(unsigned freq)
{
  unsigned char baudrate = ((16000000/(freq*1000))-16)/2;
  TWSR = 0x00;
  TWBR = baudrate;
  TWCR =(1 << TWEN);
}

void i2c_start(void)
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while(!(TWCR & (1 << TWINT)));
}

void i2c_restart(void)
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while(!(TWCR & (1 << TWINT)));
}

void i2c_stop(void)
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

unsigned char i2c_write(unsigned char data)
{
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN) | ( 1 << TWEA);
  while(!(TWCR & (1 << TWINT)));
  return (TWSR & 0xF8) == 0x18 ? false : true;
}

unsigned char i2c_read(unsigned char ack)
{
  TWCR = (1 << TWINT) | ( 1 << TWEN) | (ack ? 0 : 1 << TWEA);
  while(!(TWCR & (1 << TWINT)));
  return TWDR;
}
