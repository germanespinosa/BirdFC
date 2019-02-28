#include"pid.h"
namespace bird
{
    void Pid_Controller::update(Pid_Set &pid_set)
    {
        pid_set.value_error = pid_set.target.value - pid_set.sensor_data.value;
        pid_set.change_speed_error = pid_set.target.change_speed - pid_set.sensor_data.change_speed;
        double proportional = pid_set.value_error * pid_set.proportional_term.multiplier;
        pid_set.proportional_term.value = pid_set.proportional_term.range.cap(proportional);
        double derivative = pid_set.change_speed_error * pid_set.derivative_term.multiplier;
        pid_set.derivative_term.value = pid_set.derivative_term.range.cap(derivative);
        double integral = pid_set.value_error * pid_set.sensor_data.period * pid_set.integral_term.multiplier;
        pid_set.integral_term.value = pid_set.integral_term.range.cap( pid_set.integral_term.value + integral );
        pid_set.value = pid_set.proportional_term.value - pid_set.derivative_term.value + pid_set.integral_term.value;
    }
}  