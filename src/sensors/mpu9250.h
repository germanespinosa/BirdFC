#pragma once
#include <iostream>
#include "mpu9250_constants.h"
#include "../core/imu.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <math.h>


namespace bird
{
    struct Mpu9250 : Imu
    {
        const uint8_t imu_address = 0x68;
        const uint8_t magnetometer_address = 0x0C;
        
        Mpu9250_Constants constants;
        Mpu9250 ()
            :Imu()
            ,accelerometer_range (get_accelerometer_range(accelerometer_scale_))
            ,gyroscope_range (get_gyroscope_range(gyroscope_scale_))
            ,magnetometer_range (get_magnetometer_range(magnetometer_scale_))
        {
            init_IMU_();
        }        
        Mpu9250 (uint8_t gyroscope_scale,uint8_t accelerometer_scale,uint8_t magnetometer_scale)
            :accelerometer_range (get_accelerometer_range(accelerometer_scale))
            ,gyroscope_range (get_gyroscope_range(gyroscope_scale))
            ,magnetometer_range (get_magnetometer_range(magnetometer_scale))
            ,accelerometer_scale_(accelerometer_scale)
            ,gyroscope_scale_ (gyroscope_scale)
            ,magnetometer_scale_(magnetometer_scale)
        {
            Mpu9250();
        }        
        void calibrate_IMU();
        void writeAK8963Register(uint8_t subAddress, uint8_t data);
        void readAK8963Registers(uint8_t subAddress, uint8_t count, uint8_t* dest);
    //private:

        void init_IMU_();
        I2c imu_ = I2c(imu_address);
        I2c magnetometer_ = I2c(magnetometer_address);
        Imu::Imu_Data read_accelerometer() override;
        Imu::Imu_Data read_gyroscope() override;
        Imu::Imu_Data read_magnetometer() override;
        Range get_accelerometer_range(uint8_t scale);
        Range get_gyroscope_range(uint8_t scale);
        Range get_magnetometer_range(uint8_t scale);
        uint8_t gyroscope_scale_ = constants.GFS_250DPS;
        uint8_t accelerometer_scale_ = constants.AFS_2G;
        uint8_t magnetometer_scale_ = constants.MFS_16BITS;
        Range accelerometer_range;
        Range gyroscope_range;
        Range magnetometer_range;
    
    };
}
