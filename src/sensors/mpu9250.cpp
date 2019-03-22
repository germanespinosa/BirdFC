#include"mpu9250.h"

namespace bird
{
    void Mpu9250::init_IMU_()
    {
        imu_.write_byte( constants.PWR_MGMT_1, 0x00);
        delay(100); // Wait for all registers to reset
        imu_.write_byte(constants.PWR_MGMT_1, 0x01);
        delay(200);
        imu_.write_byte(constants.SMPLRT_DIV, 0x04);
        uint8_t c = imu_.read_byte(constants.GYRO_CONFIG);
        c = c & ~0x02; // Clear Fchoice bits [1:0]
        c = c & ~0x18; // Clear AFS bits [4:3]
        c = c | gyroscope_scale_ << 3; // Set full scale range for the gyro
        imu_.write_byte(constants.GYRO_CONFIG, c);
        c = imu_.read_byte(constants.ACCEL_CONFIG);
        c = c & ~0x18;  // Clear AFS bits [4:3]
        c = c | accelerometer_scale_ << 3; // Set full scale range for the accelerometer
        imu_.write_byte(constants.ACCEL_CONFIG, c);
        c = imu_.read_byte(constants.ACCEL_CONFIG2);
        c = c & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
        c = c | 0x03;  // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
        imu_.write_byte(constants.ACCEL_CONFIG2, c);
        imu_.write_byte(constants.INT_PIN_CFG, 0x22);
        imu_.write_byte(constants.INT_ENABLE, 0x01);      
        magnetometer_.write_byte(constants.AK8963_CNTL, 0x00); // Power down magnetometer  
        magnetometer_.write_byte(constants.AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
        uint8_t mag_adjustments_x = magnetometer_.read_byte(constants.AK8963_ASAX);
        uint8_t mag_adjustments_y = magnetometer_.read_byte(constants.AK8963_ASAY);
        uint8_t mag_adjustments_z = magnetometer_.read_byte(constants.AK8963_ASAZ);
        magnetometer_.write_byte(constants.AK8963_CNTL, constants.AK8963_MODE_CONTINUOUS_8HZ);
    }

    Imu::Imu_Data Mpu9250::read_accelerometer()
    {
      Imu::Imu_Data raw({-32768,32767});
      raw.x = imu_.read_16(constants.ACCEL_XOUT_H);
      raw.y = imu_.read_16(constants.ACCEL_YOUT_H);
      raw.z = imu_.read_16(constants.ACCEL_ZOUT_H);
      return raw.adjust(accelerometer_range);
    } 

    Imu::Imu_Data Mpu9250::read_gyroscope()
    {
      Imu::Imu_Data raw({-32768,32767});
      raw.x = imu_.read_16(constants.GYRO_XOUT_H);
      raw.y = imu_.read_16(constants.GYRO_YOUT_H);
      raw.z = imu_.read_16(constants.GYRO_ZOUT_H);
      return raw.adjust(gyroscope_range);
    }
    
    Imu::Imu_Data Mpu9250::read_magnetometer()
    {
      Imu::Imu_Data raw(get_magnetometer_range(magnetometer_scale_));
      raw.x = magnetometer_.read_16x(constants.AK8963_XOUT_L);
      raw.y = magnetometer_.read_16x(constants.AK8963_YOUT_L);
      raw.z = magnetometer_.read_16x(constants.AK8963_ZOUT_L);
      return raw.adjust({-49120.0f,49120.0f});
    }

    Range Mpu9250::get_gyroscope_range(uint8_t scale)
    {
      switch (scale)
      {
        case constants.GFS_250DPS:
          return {-250,250};
        case constants.GFS_500DPS:
          return {-500,500};
        case constants.GFS_1000DPS:
          return {-1000,1000};
        case constants.GFS_2000DPS:
          return {-2000,2000};
      }
    }

    Range Mpu9250::get_accelerometer_range(uint8_t scale)
    {
      switch (scale)
      {
        case constants.AFS_2G:
          return {-2,2};
        case constants.AFS_4G:
          return {-4,4};
        case constants.AFS_8G:
          return {-8,8};
        case constants.AFS_16G:
          return {-16,16};
      }
    }
    
    Range Mpu9250::get_magnetometer_range(uint8_t scale)
    {
      switch (scale)
      {
        case constants.MFS_14BITS:
          return {-8190.0f,8190.0f}; 
          break;
        case constants.MFS_16BITS:
          return {-32760.0f,32760.0f}; 
          break;
      }
    }
}