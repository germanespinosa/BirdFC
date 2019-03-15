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
        variable.change_speed = ( new_value - variable.value ) / period;
        variable.value = new_value;
    }
    void Sensor_Data::update_value(double new_change_speed)
    {
        update();
        variable.value += new_change_speed * period;
        variable.change_speed = new_change_speed;
    }
    Sensor_Set &Sensor::get_sensor_set()
    {
        return sensor_set_;
    }    
}