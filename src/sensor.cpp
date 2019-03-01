#include"sensor.h"
namespace bird
{
    void Sensor_Data::update()
    {
        period = timer_.restart();
    } 
    
    void Sensor_Data::update_change_speed(double new_value)
    {
        update();
        change_speed = ( new_value - value ) / period;
        value = new_value;
    }
    void Sensor_Data::update_value(double new_change_speed)
    {
        update();
        value += new_change_speed * period;
        change_speed = new_change_speed;
    }
    Sensor_Set &Sensor::get_sensor_set()
    {
        return sensor_set_;
    }    
}