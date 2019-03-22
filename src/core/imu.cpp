#include"imu.h"
namespace bird
{
    bool Imu::update()
    {
        static Low_Pass_Filter lpf_roll({-PI,PI},.01);
        static Low_Pass_Filter lpf_pitch({-PI,PI},.01);

        Imu::Imu_Data accelerometer = read_accelerometer();
        Imu::Imu_Data gyroscope = read_gyroscope();
        Imu::Imu_Data magnetometer = read_magnetometer();
        
        sensor_set_.roll = atan2(accelerometer.x, fabs(accelerometer.z));
        sensor_set_.roll.variable.change_speed = gyroscope.x;
        sensor_set_.pitch = atan2(accelerometer.y, fabs(accelerometer.z));
        sensor_set_.pitch.variable.change_speed = gyroscope.y;
        sensor_set_.yaw.update_value(gyroscope.z);
/*        sensor_set_.vertical.update_value(accelerometer.z);
        sensor_set_.longitudinal.update_value(accelerometer.x);
        sensor_set_.lateral.update_value(accelerometer.y);*/
        
        
    }
}