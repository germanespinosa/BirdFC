#include"pid.h"
#include<iostream>
namespace bird
{
    Pid_Set::Pid_Set( Sensor_Data &sensor_data, Variable &target, Pid_Configuration Actuator_Set)
        : sensor_data (sensor_data)
        , target (target)
        , Actuator_Set (Actuator_Set)
    {
    }

    Pid::Pid(Pid_Set pid_set)
        : pid_set_(pid_set)
    {
    }
    
    void Pid::update()
    {
        //compute between values and targets
        pid_set_.value_error = pid_set_.target.value - pid_set_.sensor_data.variable.value;
        pid_set_.change_speed_error = pid_set_.target.change_speed - pid_set_.sensor_data.variable.change_speed;
        
        // proportional controller
        double proportional = pid_set_.value_error * pid_set_.Actuator_Set.proportional.multiplier;
        pid_set_.proportional_value = pid_set_.Actuator_Set.proportional.range.cap(proportional);
        // derivative controller
        double derivative = pid_set_.change_speed_error * pid_set_.Actuator_Set.derivative.multiplier;
        pid_set_.derivative_value = pid_set_.Actuator_Set.derivative.range.cap(derivative);


        // integral controller
        double integral = pid_set_.value_error * pid_set_.sensor_data.period * pid_set_.Actuator_Set.integral.multiplier;
        pid_set_.integral_value = pid_set_.Actuator_Set.integral.range.cap( pid_set_.integral_value + integral );
        
		
		pid_set_.value = pid_set_.proportional_value - pid_set_.derivative_value + pid_set_.integral_value;
    }
    

    Pid_Set &Pid::get_pid_set()
    {
        return pid_set_;
    }    
}  