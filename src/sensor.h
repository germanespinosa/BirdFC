#pragma once
#include"utils.h"
#include <sys/time.h>

namespace bird
{
    struct Sensor_Data
    {
        Sensor_Data(){}
        Sensor_Data(double secs):
            timer_(secs){}
        double value = 0;
        double change_speed = 0;
        double period=0;
        Range range{0,0};
        void update();
        void update_value(double new_change_speed);
        void update_change_speed(double new_value);
    private:
        Timer timer_;
    };
    
    struct Sensor_Set
    {
        Sensor_Data roll;
        Sensor_Data pitch;
        Sensor_Data yaw;
        Sensor_Data lateral;      // Left - Right
        Sensor_Data longitudinal; // Backward - Forward
        Sensor_Data vertical;     // Down - Up
    };
    
    struct Sensor
    {
    public:
        virtual bool update() = 0;
        Sensor_Set &get_sensor_set()
        {
            return sensor_set_;
        }
    private:
        Sensor_Set sensor_set_;
    };    
}
