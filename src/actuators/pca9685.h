#include "pca9685_constants.h"
#include "../core/bird.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>

namespace bird 
{
    struct Pca9685 : Actuator
    {
        Pca9685(uint8_t address);
        bool update() override;
    private:
        Pca9685_constants constants_;
        I2c i2c_;
    };
}