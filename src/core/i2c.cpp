#include"i2c.h"

namespace bird
{
    I2c::I2c(uint8_t device_address)
    {
        device_handler_ = wiringPiI2CSetup(device_address);
    }
    void I2c::set_register_address(uint8_t register_address)
    {
        current_register_address_ = register_address;
    }
    uint8_t I2c::read_byte()
    {
        return wiringPiI2CReadReg8(device_handler_,current_register_address_++);
    }
    uint8_t I2c::read_byte(uint8_t register_address)
    {
        current_register_address_ = register_address;
        return read_byte();
    }
    void I2c::write_byte(uint8_t data)
    {
        wiringPiI2CWriteReg8(device_handler_, current_register_address_++, data);
    }
    void I2c::write_byte(uint8_t register_address, uint8_t data)
    {
        current_register_address_ = register_address;
        write_byte(data);
    }
    void I2c::write_16(uint16_t data)
    {
      int8_t *rdata = (int8_t *)&data;
      write_byte(rdata[1]);
      write_byte(rdata[0]);
    }
    void I2c::write_16(uint8_t register_address, uint16_t data)
    {
        current_register_address_ = register_address;
        write_16(data);
    }
    void I2c::write_16x(uint16_t data)
    {
      int8_t *rdata = (int8_t *)&data;
      write_byte(rdata[0]);
      write_byte(rdata[1]);
    }
    void I2c::write_16x(uint8_t register_address, uint16_t data)
    {
        current_register_address_ = register_address;
        write_16(data);
    }
    void I2c::read_data(uint8_t register_address, int count, uint8_t *buffer)
    {
        current_register_address_ = register_address;
        for (int i=0;i<count;i++)
            buffer[i] = read_byte();
    }
    void I2c::write_data(uint8_t register_address, int count, uint8_t *buffer)
    {
        current_register_address_ = register_address;
        for (int i=0;i<count;i++)
            write_byte(buffer[i]);
    }
    uint16_t I2c::read_16(uint8_t register_address) 
    {
      current_register_address_ = register_address;
      return read_16();
    }
    uint16_t I2c::read_16()
    {
      uint16_t res;
      int8_t *rres = (int8_t *)&res;
      rres[1] = read_byte();
      rres[0] = read_byte();
      return res;
    }
    uint16_t I2c::read_16x(uint8_t register_address) 
    {
      current_register_address_ = register_address;
      return read_16x();
    }
    uint16_t I2c::read_16x() 
    {
      uint16_t res;
      int8_t *rres = (int8_t *)&res;
      rres[0] = read_byte();
      rres[1] = read_byte();
      return res;
    }
} 