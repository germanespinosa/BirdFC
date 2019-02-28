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
        double value = 0;
    };
    struct Pid_Target
    {
    public:
        double value = 0;
        double change_speed = 0;
    };
    struct Pid_Set
    {
    public:
        Pid_Term proportional_term;
        Pid_Term derivative_term;
        Pid_Term integral_term;
        double value_error;
        double change_speed_error;
        Sensor_Data sensor_data;
        Pid_Target target;
        double value = 0;
    };

    struct Pid_Controller
    { 
    public:
        Pid_Controller() 
        {
        }
        void update(Pid_Set &request);
    };
};