#include"pid.h"
namespace bird
{
    void Pid::update()
    {
        //compute between values and targets
        pid_set_.value_error = pid_set_.target.value - pid_set_.sensor_data.value;
        pid_set_.change_speed_error = pid_set_.target.change_speed - pid_set_.sensor_data.change_speed;
        
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
}  