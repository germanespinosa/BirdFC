#pragma once
#include<time.h>
#include<algorithm>
#include"utils.h"
#include"sensor.h"

namespace bird
{
    
    struct Pid_Term 
    {
    public:
        double multiplier;
        Range range{0,0};
    };
    struct Pid_Configuration
    {
    public:
        Pid_Term proportional;
        Pid_Term derivative;
        Pid_Term integral;
    };
    
    struct Pid_Set
    {
    public:
        Pid_Set( Sensor_Data &sensor_data, Variable &target, Pid_Configuration Actuator_Set);
        Pid_Configuration Actuator_Set;
        double proportional_value = 0;
        double derivative_value = 0;
        double integral_value = 0;
        double value_error = 0;
        double change_speed_error = 0;
        Sensor_Data &sensor_data;
        Variable &target;
        double value = 0;
        operator double()
        {
            return value;
        }
    };

    struct Pid
    { 
    public:
        Pid(Pid_Set pid_set);
        void update();
        Pid_Set &get_pid_set();
        operator double()
        {
            return pid_set_;
        }
    private:
        Pid_Set pid_set_;
    };
};