#include"imu.h"
namespace bird
{
    bool Imu::update()
    {
        Imu::Imu_Data accelerometer = read_accelerometer();
        Imu::Imu_Data gyroscope = read_gyroscope();
        Imu::Imu_Data magnetometer = read_magnetometer();
        
        sensor_set_.roll = atan2(accelerometer.x, hypot(accelerometer.y,accelerometer.z));
        sensor_set_.roll.variable.change_speed = gyroscope.x;
        sensor_set_.pitch = atan2(accelerometer.y, hypot(accelerometer.x,accelerometer.z));
        sensor_set_.pitch.variable.change_speed = gyroscope.y;
        sensor_set_.yaw.update_value(gyroscope.z);
        double mag_x = magnetometer.x * cos(sensor_set_.pitch) + magnetometer.y * sin(sensor_set_.roll) * sin(sensor_set_.pitch) + magnetometer.z * cos(sensor_set_.roll) * sin(sensor_set_.pitch);  
        double mag_y = magnetometer.y * cos(sensor_set_.roll) - magnetometer.z * sin(sensor_set_.roll);
        sensor_set_.yaw = atan2(-mag_y,mag_x);
    }
}