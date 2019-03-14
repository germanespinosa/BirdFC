#pragma once
#include <iostream>
#include "mpu9250_constants.h"
#include <bird.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <math.h>


namespace bird
{
    struct Mpu9250 : Sensor
    {
        const uint8_t imu_address = 0x68;
        const uint8_t magnetometer_address = 0x0C;
        
        Mpu9250_Constants constants;
        Mpu9250 ()
        {
            init_IMU_();
            set_accelerometer_resolution_();
            set_gyroscope_resolution_();
            set_magnetometer_resolution_();            
        }        
        Mpu9250 (uint8_t gyroscope_scale,uint8_t accelerometer_scale,uint8_t magnetometer_scale)
        {
            gyroscope_scale_ = gyroscope_scale;
            accelerometer_scale_ = accelerometer_scale;
            magnetometer_scale_ = magnetometer_scale;
            init_IMU_();
            set_accelerometer_resolution_();
            set_gyroscope_resolution_();
            set_magnetometer_resolution_();
        }        
        bool update() override;
        void calibrate_IMU();
        void writeAK8963Register(uint8_t subAddress, uint8_t data);
        void readAK8963Registers(uint8_t subAddress, uint8_t count, uint8_t* dest);
    //private:

        struct Data_
        {
            double x;
            double y;
            double z;
        };

        struct Raw_Data_
        {
            int16_t x;
            int16_t y;
            int16_t z;
            Data_ to_data(double resolution)
            {
                return {(double) x * resolution, (double) y * resolution , (double) z * resolution};
            }
        };
        
        struct Calibration_Data_
        {
            uint32_t x;
            uint32_t y;
            uint32_t z;
            Calibration_Data_ operator += (Raw_Data_ data)
            {
                x+=data.x;
                y+=data.y;
                z+=data.z;
                return *this;
            }
            Raw_Data_ operator / (uint16_t divisor)
            {
                Raw_Data_ raw;
                raw.x+=x/divisor;
                raw.y+=y/divisor;
                raw.z+=z/divisor;
                return raw;
            }
            
        };

        Raw_Data_ mag_adjustments_;
        void init_IMU_();
        Raw_Data_ read_accelerometer_raw_();
        Raw_Data_ read_gyroscope_raw_();
        Raw_Data_ read_magnetometer_raw_();
        Data_ read_accelerometer_();
        Data_ read_gyroscope_();
        Data_ read_magnetometer_();
        void set_accelerometer_resolution_();
        void set_gyroscope_resolution_();
        void set_magnetometer_resolution_();
        
        I2c imu_ = I2c(imu_address);
        I2c magnetometer_ = I2c(magnetometer_address);

        uint8_t gyroscope_scale_ = constants.GFS_250DPS;
        uint8_t accelerometer_scale_ = constants.AFS_2G;
        // Choose either 14-bit or 16-bit magnetometer resolution
        uint8_t magnetometer_scale_ = constants.MFS_16BITS;
        
        double accelerometer_resolution_;
        double gyroscope_resolution_;
        double magnetometer_resolution_;
    
    };
}
