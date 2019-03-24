#pragma once
#include"utils.h"
#include <sys/time.h>

namespace bird
{
    struct Sensor_Data
    {
    public:
        Sensor_Data(){}
        Sensor_Data(double secs):
            timer_(secs){}
        Variable variable = Variable({ -PI, PI});
        double period=0;
        void update();
        void update_value(double new_change_speed);
        void update_change_speed(double new_value);
        double operator = (double v)
        {
            variable = v ;
        }
        operator double()
        {
            return variable;
        }            
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
        Sensor_Set &get_sensor_set();
        Sensor_Set sensor_set_;
    };
}
