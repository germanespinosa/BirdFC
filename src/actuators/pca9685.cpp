#include "pca9685.h"

bird::Pca9685::Pca9685()
    : bird::Pca9685(0x40)
{
}

bird::Pca9685::Pca9685(uint8_t address)
    : bird::Actuator(bird::Actuator_Set::plus())
    , i2c_(bird::I2c(address))
{
    
}

bool bird::Pca9685::update()
{
    bird::Range range {0,4095};
    uint8_t propeller = 0;
    i2c_.set_register_address(constants_.LED0_ON_L);
    for (bird::Propeller p : actuator_set_.propellers)
    {
        uint16_t pwm = range.adjust(p.output_value,{0,1});
        i2c_.write_16x(pwm);
        i2c_.write_16x(4095);
        std::cout << p.output_value << "\t";
    }
    std::cout << "\n";
    return true;
}
