#include "../core/bird.h"

namespace bird
{
    struct Imu : Sensor
    {
        Imu()
        {
            sensor_set_.roll.update();
            sensor_set_.pitch.update();
            sensor_set_.yaw.update();
        }
        bool update() override;
        struct Imu_Data
        {
            double x;
            double y;
            double z;
            Range range;
            Imu_Data adjust(Range new_range)
            {
                x=new_range.adjust(x,range);
                y=new_range.adjust(x,range);
                z=new_range.adjust(x,range);
                range = range; 
                return *this;
            }
            Imu_Data(Range r)
                :range(r){};
        };
        virtual Imu_Data read_accelerometer() = 0;
        virtual Imu_Data read_gyroscope() = 0;
        virtual Imu_Data read_magnetometer() = 0;
    };
}