#include"mpu9250.h"

namespace bird
{
    void Mpu9250::init_IMU_()
    {
        // wake up device
        // Clear sleep mode bit (6), enable all sensors
        imu_.write_byte( constants.PWR_MGMT_1, 0x00);
        delay(100); // Wait for all registers to reset

        // Get stable time source
        // Auto select clock source to be PLL gyroscope reference if ready else
        imu_.write_byte(constants.PWR_MGMT_1, 0x01);
        delay(200);

        // Configure Gyro and Thermometer
        // Disable FSYNC and set thermometer and gyro bandwidth to 41 and 42 Hz,
        // respectively;
        // minimum delay time for this setting is 5.9 ms, which means sensor fusion
        // update rates cannot be higher than 1 / 0.0059 = 170 Hz
        // DLPF_CFG = bits 2:0 = 011; this limits the sample rate to 1000 Hz for both
        // With the MPU9250, it is possible to get gyro sample rates of 32 kHz (!),
        // 8 kHz, or 1 kHz
        imu_.write_byte(constants.CONFIG, 0x03);

        // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
        // Use a 200 Hz rate; a rate consistent with the filter update rate
        // determined inset in CONFIG above.
        imu_.write_byte(constants.SMPLRT_DIV, 0x04);

        // Set gyroscope full scale range
        // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are
        // left-shifted into positions 4:3

        // get current GYRO_CONFIG register value
        uint8_t c = imu_.read_byte(constants.GYRO_CONFIG);
        // c = c & ~0xE0; // Clear self-test bits [7:5]
        c = c & ~0x02; // Clear Fchoice bits [1:0]
        c = c & ~0x18; // Clear AFS bits [4:3]
        c = c | gyroscope_scale_ << 3; // Set full scale range for the gyro
        // Set Fchoice for the gyro to 11 by writing its inverse to bits 1:0 of
        // GYRO_CONFIG
        // c =| 0x00;
        // Write new GYRO_CONFIG value to register
        imu_.write_byte(constants.GYRO_CONFIG, c);

        // Set accelerometer full-scale range configuration
        // Get current ACCEL_CONFIG register value
        c = imu_.read_byte(constants.ACCEL_CONFIG);
        // c = c & ~0xE0; // Clear self-test bits [7:5]
        c = c & ~0x18;  // Clear AFS bits [4:3]
        c = c | accelerometer_scale_ << 3; // Set full scale range for the accelerometer
        // Write new ACCEL_CONFIG register value
        imu_.write_byte(constants.ACCEL_CONFIG, c);

        // Set accelerometer sample rate configuration
        // It is possible to get a 4 kHz sample rate from the accelerometer by
        // choosing 1 for accel_fchoice_b bit [3]; in this case the bandwidth is
        // 1.13 kHz
        // Get current ACCEL_CONFIG2 register value
        c = imu_.read_byte(constants.ACCEL_CONFIG2);
        c = c & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
        c = c | 0x03;  // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
        // Write new ACCEL_CONFIG2 register value
        imu_.write_byte(constants.ACCEL_CONFIG2, c);
        // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates,
        // but all these rates are further reduced by a factor of 5 to 200 Hz because
        // of the SMPLRT_DIV setting

        // Configure Interrupts and Bypass Enable
        // Set interrupt pin active high, push-pull, hold interrupt pin level HIGH
        // until interrupt cleared, clear on read of INT_STATUS, and enable
        // I2C_BYPASS_EN so additional chips can join the I2C bus and all can be
        // controlled by the Arduino as master.
        imu_.write_byte(constants.INT_PIN_CFG, 0x22);
        // Enable data ready (bit 0) interrupt
        imu_.write_byte(constants.INT_ENABLE, 0x01);
        delay(100);
        
        
        magnetometer_.write_byte(constants.AK8963_CNTL, 0x00); // Power down magnetometer  
        magnetometer_.write_byte(constants.AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
 
        mag_adjustments_.x = magnetometer_.read_byte(constants.AK8963_ASAX);
        mag_adjustments_.y = magnetometer_.read_byte(constants.AK8963_ASAY);
        mag_adjustments_.z = magnetometer_.read_byte(constants.AK8963_ASAZ);

        double xscale = (double)(mag_adjustments_.x - 128) * 0.5 / 128.0 + 1.0;
        double yscale = (double)(mag_adjustments_.y - 128) * 0.5 / 128.0 + 1.0;
        double zscale = (double)(mag_adjustments_.z - 128) * 0.5 / 128.0 + 1.0;
        std::cout << "adjustment :"  << mag_adjustments_.x << "," << mag_adjustments_.y << "," << mag_adjustments_.z << "\n";
        magnetometer_.write_byte(constants.AK8963_CNTL, constants.AK8963_MODE_CONTINUOUS_8HZ);

    
        sensor_set_.roll.update();
        sensor_set_.pitch.update();
        sensor_set_.yaw.update();
        
    }

    Mpu9250::Raw_Data_ Mpu9250::read_accelerometer_raw_()
    {
      Mpu9250::Raw_Data_ raw;
      raw.x = imu_.read_16(constants.ACCEL_XOUT_H);
      raw.y = imu_.read_16(constants.ACCEL_YOUT_H);
      raw.z = imu_.read_16(constants.ACCEL_ZOUT_H);
      return raw;
    } 

    Mpu9250::Raw_Data_ Mpu9250::read_gyroscope_raw_()
    {
      Mpu9250::Raw_Data_ raw;
      raw.x = imu_.read_16(constants.GYRO_XOUT_H);
      raw.y = imu_.read_16(constants.GYRO_YOUT_H);
      raw.z = imu_.read_16(constants.GYRO_ZOUT_H);
      return raw;
    }
    
    Mpu9250::Data_ Mpu9250::read_accelerometer_()
    {
      return read_accelerometer_raw_().to_data(accelerometer_resolution_);
    }
    double adjustMagValue(int16_t value, uint8_t adjust) {
      return ((double) value * (((((double) adjust - 128) * 0.5) / 128) + 1));
    }
    Mpu9250::Data_ Mpu9250::read_magnetometer_()
    {
      Raw_Data_ raw_ = read_magnetometer_raw_();
      Data_ data;
      data.x = adjustMagValue(raw_.x,mag_adjustments_.x);
      data.y = adjustMagValue(raw_.y,mag_adjustments_.y);
      data.z = adjustMagValue(raw_.z,mag_adjustments_.z);
      return data;
    }
    
    Mpu9250::Data_ Mpu9250::read_gyroscope_()
    {
      return read_gyroscope_raw_().to_data(gyroscope_resolution_);
    }

    Mpu9250::Raw_Data_ Mpu9250::read_magnetometer_raw_()
    {
      uint8_t magBuf[7];
      magnetometer_.read_data(constants.AK8963_XOUT_L,7,magBuf);
      Raw_Data_ raw;
/*      raw.x = magnetometer_.read_16x(constants.AK8963_XOUT_L );
      raw.y = magnetometer_.read_16x(constants.AK8963_YOUT_L );
      raw.z = magnetometer_.read_16x(constants.AK8963_ZOUT_L );*/
      raw.x =   (((int16_t) magBuf[1]) << 8) | magBuf[0];
      raw.y =   (((int16_t) magBuf[3]) << 8) | magBuf[2];
      raw.z =   (((int16_t) magBuf[5]) << 8) | magBuf[4];
      bool overflow = magBuf[6];//magnetometer_.read_byte() & 0x08;
      if (overflow)
          std::cout << "overflown\n";
      return raw;
    }

    void Mpu9250::set_magnetometer_resolution_()
    {
      switch (magnetometer_scale_)
      {
        // Possible magnetometer scales (and their register bit settings) are:
        // 14 bit resolution (0) and 16 bit resolution (1)
        case constants.MFS_14BITS:
          magnetometer_resolution_ = 10.0f * 4912.0f / 8190.0f; // Proper scale to return milliGauss
          break;
        case constants.MFS_16BITS:
          magnetometer_resolution_ = 10.0f * 4912.0f / 32760.0f; // Proper scale to return milliGauss
          break;
      }
    }

    void Mpu9250::set_gyroscope_resolution_()
    {
      switch (gyroscope_scale_)
      {
        // Possible gyro scales (and their register bit settings) are:
        // 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS (11).
        // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that
        // 2-bit value:
        case constants.GFS_250DPS:
          gyroscope_resolution_ = 250.0f / 32768.0f / 360.0f * 2 * constants.PI;
          break;
        case constants.GFS_500DPS:
          gyroscope_resolution_ = 500.0f / 32768.0f / 360.0f * 2 * constants.PI;
          break;
        case constants.GFS_1000DPS:
          gyroscope_resolution_ = 1000.0f / 32768.0f / 360.0f * 2 * constants.PI;
          break;
        case constants.GFS_2000DPS:
          gyroscope_resolution_ = 2000.0f / 32768.0f / 360.0f * 2 * constants.PI;
          break;
      }
    }

    void Mpu9250::set_accelerometer_resolution_()
    {
      switch (accelerometer_scale_)
      {
        // Possible accelerometer scales (and their register bit settings) are:
        // 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11).
        // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that
        // 2-bit value:
        case constants.AFS_2G:
          accelerometer_resolution_ = 2.0f / 32768.0f;
          break;
        case constants.AFS_4G:
          accelerometer_resolution_ = 4.0f / 32768.0f;
          break;
        case constants.AFS_8G:
          accelerometer_resolution_ = 8.0f / 32768.0f;
          break;
        case constants.AFS_16G:
          accelerometer_resolution_ = 16.0f / 32768.0f;
          break;
      }
    }
    
    bool Mpu9250::update()
    {
        Mpu9250::Data_ accelerometer = read_accelerometer_();
        Mpu9250::Data_ gyroscope = read_gyroscope_();
        read_magnetometer_();
        sensor_set_.roll.variable.value = atan2(accelerometer.x, fabs(accelerometer.z));
        sensor_set_.roll.variable.change_speed = gyroscope.x;
        sensor_set_.pitch.variable.value = atan2(accelerometer.y, fabs(accelerometer.z));
        sensor_set_.pitch.variable.change_speed = gyroscope.y;
        sensor_set_.yaw.update_value(gyroscope.z);
        sensor_set_.vertical.update_value(accelerometer.z);
        sensor_set_.longitudinal.update_value(accelerometer.x);
        sensor_set_.lateral.update_value(accelerometer.y);
    }
    

    // Function which accumulates gyro and accelerometer data after device
    // initialization. It calculates the average of the at-rest readings and then
    // loads the resulting offsets into accelerometer and gyro bias registers.
    void Mpu9250::calibrate_IMU()
    {
      uint8_t data[12]; // data array to hold accelerometer and gyro x, y, z, data
      uint16_t ii, packet_count, fifo_count;
      int32_t gyro_bias[3]  = {0, 0, 0}, accel_bias[3] = {0, 0, 0};

      // reset device
      // Write a one to bit 7 reset bit; toggle reset device
      imu_.write_byte(constants.PWR_MGMT_1, constants.I2C_READ_FLAG);
      delay(100);

      // get stable time source; Auto select clock source to be PLL gyroscope
      // reference if ready else use the internal oscillator, bits 2:0 = 001
      imu_.write_byte(constants.PWR_MGMT_1, 0x01);
      imu_.write_byte(constants.PWR_MGMT_2, 0x00);
      delay(200);

      // Configure device for bias calculation
      // Disable all interrupts
      imu_.write_byte(constants.INT_ENABLE, 0x00);
      // Disable FIFO
      imu_.write_byte(constants.FIFO_EN, 0x00);
      // Turn on internal clock source
      imu_.write_byte(constants.PWR_MGMT_1, 0x00);
      // Disable I2C master
      imu_.write_byte(constants.I2C_MST_CTRL, 0x00);
      // Disable FIFO and I2C master modes
      imu_.write_byte(constants.USER_CTRL, 0x00);
      // Reset FIFO and DMP
      imu_.write_byte(constants.USER_CTRL, 0x0C);
      delay(15);

      // Configure MPU6050 gyro and accelerometer for bias calculation
      // Set low-pass filter to 188 Hz
      imu_.write_byte(constants.CONFIG, 0x01);
      // Set sample rate to 1 kHz
      imu_.write_byte(constants.SMPLRT_DIV, 0x00);
      // Set gyro full-scale to 250 degrees per second, maximum sensitivity
      imu_.write_byte(constants.GYRO_CONFIG, 0x00);
      // Set accelerometer full-scale to 2 g, maximum sensitivity
      imu_.write_byte(constants.ACCEL_CONFIG, 0x00);

      uint16_t  gyrosensitivity  = 131;   // = 131 LSB/degrees/sec
      uint16_t  accelsensitivity = 16384; // = 16384 LSB/g

      // Configure FIFO to capture accelerometer and gyro data for bias calculation
      imu_.write_byte(constants.USER_CTRL, 0x40);  // Enable FIFO
      // Enable gyro and accelerometer sensors for FIFO  (max size 512 bytes in
      // MPU-9150)
      imu_.write_byte(constants.FIFO_EN, 0x78);
      delay(40);  // accumulate 40 samples in 40 milliseconds = 480 bytes

      // At end of sample accumulation, turn off FIFO sensor read
      // Disable gyro and accelerometer sensors for FIFO
      imu_.write_byte(constants.FIFO_EN, 0x00);
      // Read FIFO sample count

      int8_t *rfifo_count = (int8_t *)&fifo_count;
      rfifo_count[1] = imu_.read_byte(constants.FIFO_COUNTH);
      rfifo_count[0] = imu_.read_byte(constants.FIFO_COUNTL);

      // How many sets of full gyro and accelerometer data for averaging
      packet_count = fifo_count/12;

      for (ii = 0; ii < packet_count; ii++)
      {
        int16_t accel_temp[3] = {0, 0, 0}, gyro_temp[3] = {0, 0, 0};
        // Read data for averaging
        // Form signed 16-bit integer for each sample in FIFO
        accel_temp[0] = imu_.read_16(constants.FIFO_R_W);
        accel_temp[1] = imu_.read_16();
        accel_temp[2] = imu_.read_16();
        gyro_temp[0] = imu_.read_16();
        gyro_temp[1] = imu_.read_16();
        gyro_temp[2] = imu_.read_16();
        // Sum individual signed 16-bit biases to get accumulated signed 32-bit
        // biases.
        accel_bias[0] += (int32_t) accel_temp[0];
        accel_bias[1] += (int32_t) accel_temp[1];
        accel_bias[2] += (int32_t) accel_temp[2];
        gyro_bias[0]  += (int32_t) gyro_temp[0];
        gyro_bias[1]  += (int32_t) gyro_temp[1];
        gyro_bias[2]  += (int32_t) gyro_temp[2];
      }
      
      // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
      accel_bias[0] /= (int32_t) packet_count;
      accel_bias[1] /= (int32_t) packet_count;
      accel_bias[2] /= (int32_t) packet_count;
      gyro_bias[0]  /= (int32_t) packet_count;
      gyro_bias[1]  /= (int32_t) packet_count;
      gyro_bias[2]  /= (int32_t) packet_count;

      // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
      if (accel_bias[2] > 0L)
      {
        accel_bias[2] -= (int32_t) accelsensitivity;
      }
      else
      {
        accel_bias[2] += (int32_t) accelsensitivity;
      }

      // Construct the gyro biases for push to the hardware gyro bias registers,
      // which are reset to zero upon device startup.
      // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input
      // format.
      data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF;
      // Biases are additive, so change sign on calculated average gyro biases
      data[1] = (-gyro_bias[0]/4)       & 0xFF;
      data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
      data[3] = (-gyro_bias[1]/4)       & 0xFF;
      data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
      data[5] = (-gyro_bias[2]/4)       & 0xFF;

      // Push gyro biases to hardware registers
      imu_.write_byte(constants.XG_OFFSET_H, data[0]);
      imu_.write_byte(constants.XG_OFFSET_L, data[1]);
      imu_.write_byte(constants.YG_OFFSET_H, data[2]);
      imu_.write_byte(constants.YG_OFFSET_L, data[3]);
      imu_.write_byte(constants.ZG_OFFSET_H, data[4]);
      imu_.write_byte(constants.ZG_OFFSET_L, data[5]);

      // Construct the accelerometer biases for push to the hardware accelerometer
      // bias registers. These registers contain factory trim values which must be
      // added to the calculated accelerometer biases; on boot up these registers
      // will hold non-zero values. In addition, bit 0 of the lower byte must be
      // preserved since it is used for temperature compensation calculations.
      // Accelerometer bias registers expect bias input as 2048 LSB per g, so that
      // the accelerometer biases calculated above must be divided by 8.

      // A place to hold the factory accelerometer trim biases
      int32_t accel_bias_reg[3] = {0, 0, 0};
      // Read factory accelerometer trim values
      accel_bias_reg[0] = imu_.read_16(constants.XA_OFFSET_H);
      accel_bias_reg[1] = imu_.read_16(constants.YA_OFFSET_H);
      accel_bias_reg[2] = imu_.read_16(constants.ZA_OFFSET_H);

      // Define mask for temperature compensation bit 0 of lower byte of
      // accelerometer bias registers
      uint32_t mask = 1uL;
      // Define array to hold mask bit for each accelerometer bias axis
      uint8_t mask_bit[3] = {0, 0, 0};

      for (ii = 0; ii < 3; ii++)
      {
        // If temperature compensation bit is set, record that fact in mask_bit
        if ((accel_bias_reg[ii] & mask))
        {
          mask_bit[ii] = 0x01;
        }
      }

      // Construct total accelerometer bias, including calculated average
      // accelerometer bias from above
      // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g
      // (16 g full scale)
      accel_bias_reg[0] -= (accel_bias[0]/8);
      accel_bias_reg[1] -= (accel_bias[1]/8);
      accel_bias_reg[2] -= (accel_bias[2]/8);

      data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
      data[1] = (accel_bias_reg[0])      & 0xFF;
      // preserve temperature compensation bit when writing back to accelerometer
      // bias registers
      data[1] = data[1] | mask_bit[0];
      data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
      data[3] = (accel_bias_reg[1])      & 0xFF;
      // Preserve temperature compensation bit when writing back to accelerometer
      // bias registers
      data[3] = data[3] | mask_bit[1];
      data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
      data[5] = (accel_bias_reg[2])      & 0xFF;
      // Preserve temperature compensation bit when writing back to accelerometer
      // bias registers
      data[5] = data[5] | mask_bit[2];

      // Apparently this is not working for the acceleration biases in the MPU-9250
      // Are we handling the temperature correction bit properly?
      // Push accelerometer biases to hardware registers
      imu_.write_byte(constants.XA_OFFSET_H, data[0]);
      imu_.write_byte(constants.XA_OFFSET_L, data[1]);
      imu_.write_byte(constants.YA_OFFSET_H, data[2]);
      imu_.write_byte(constants.YA_OFFSET_L, data[3]);
      imu_.write_byte(constants.ZA_OFFSET_H, data[4]);
      imu_.write_byte(constants.ZA_OFFSET_L, data[5]);
      
    }

    
}