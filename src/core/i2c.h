#include <cstdint>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <math.h>

namespace bird
{
    struct I2c
    {
        public:
        I2c(uint8_t device_address);
        void set_register_address(uint8_t register_address);
        uint8_t read_byte();
        uint8_t read_byte(uint8_t register_address);
        uint16_t read_16();
        uint16_t read_16(uint8_t register_address);
        uint16_t read_16x();
        uint16_t read_16x(uint8_t register_address);
        void write_byte(uint8_t data);
        void write_byte(uint8_t register_address, uint8_t data);
        void write_16(uint16_t data);
        void write_16(uint8_t register_address, uint16_t data);
        void write_16x(uint16_t data);
        void write_16x(uint8_t register_address, uint16_t data);
        void read_data(uint8_t register_address, int count, uint8_t *buffer);
        void write_data(uint8_t register_address, int count, uint8_t *buffer);
        private:
        int device_handler_;
        uint8_t current_register_address_ = 0;
    };  
}