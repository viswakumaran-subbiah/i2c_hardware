#ifndef _I2C_H
#define _I2C_H

extern void i2c_initialize(unsigned int freq);
extern void i2c_start(void);
extern void i2c_restart(void);
extern void i2c_stop(void);

extern unsigned char i2c_write(unsigned char data);
extern unsigned char i2c_read(unsigned char ack);

#endif
