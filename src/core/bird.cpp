#include"bird.h"

namespace bird
{

    Bird::Bird (Sensor &sensor, Control &control, Actuator &actuator, Bird_Set bird_set)
        : sensor_(sensor)
        , control_(control)
        , roll_ (Pid(Pid_Set(sensor.get_sensor_set().roll,control.get_control_set().roll,bird_set.roll)))
        , pitch_ (Pid(Pid_Set(sensor.get_sensor_set().pitch,control.get_control_set().pitch,bird_set.pitch)))
        , yaw_ (Pid(Pid_Set(sensor.get_sensor_set().yaw,control.get_control_set().yaw,bird_set.yaw)))
        , lateral_ (Pid(Pid_Set(sensor.get_sensor_set().lateral,control.get_control_set().lateral,bird_set.lateral)))
        , longitudinal_ (Pid(Pid_Set(sensor.get_sensor_set().longitudinal,control.get_control_set().longitudinal,bird_set.longitudinal)))
        , vertical_ (Pid(Pid_Set(sensor.get_sensor_set().vertical,control.get_control_set().vertical,bird_set.vertical)))
        , actuator_(actuator_)
    {
    }
        
    
    void Bird::run()
    {
        
        Actuator_Set &actuator_set = actuator_.get_actuator_set();
        
        while(sensor_.update() && control_.update())
        {
            roll_.update();
            pitch_.update();
            yaw_.update();
            lateral_.update();
            longitudinal_.update();
            vertical_.update();
            for (Propeller propeller:actuator_set.propellers)
            {
                double output = 0;
                output += roll_.get_pid_set().value * propeller.ratios.roll;
                output += pitch_.get_pid_set().value * propeller.ratios.pitch;
                output += yaw_.get_pid_set().value * propeller.ratios.yaw;
                output += lateral_.get_pid_set().value * propeller.ratios.lateral;
                output += longitudinal_.get_pid_set().value * propeller.ratios.longitudinal;
                output += vertical_.get_pid_set().value * propeller.ratios.vertical;
                propeller.output_value = output;
            }
        }
    }
}
