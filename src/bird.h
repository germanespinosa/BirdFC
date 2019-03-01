#include <iostream>
#include"utils.h"
#include"pid.h"
#include"configuration.h"
#include"sensor.h"
#include"control.h" 

namespace bird
{

    struct Bird_Set
    {
        Pid_Configuration roll;
        Pid_Configuration pitch;
        Pid_Configuration yaw;
        Pid_Configuration lateral;      // Left - Right
        Pid_Configuration longitudinal; // Backward - Forward
        Pid_Configuration vertical;     // Down - Up        
    };

    struct Bird
    {
    public:
        Bird (Configuration &configuration, Sensor &sensor, Control &control, Bird_Set bird_set)
            : configuration_(configuration)
            , sensor_(sensor)
            , control_(control)
            , roll_ (Pid(Pid_Set(sensor.get_sensor_set().roll,control.get_control_set().roll,bird_set.roll)))
            , pitch_ (Pid(Pid_Set(sensor.get_sensor_set().pitch,control.get_control_set().pitch,bird_set.pitch)))
            , yaw_ (Pid(Pid_Set(sensor.get_sensor_set().yaw,control.get_control_set().yaw,bird_set.yaw)))
            , lateral_ (Pid(Pid_Set(sensor.get_sensor_set().lateral,control.get_control_set().lateral,bird_set.lateral)))
            , longitudinal_ (Pid(Pid_Set(sensor.get_sensor_set().longitudinal,control.get_control_set().longitudinal,bird_set.longitudinal)))
            , vertical_ (Pid(Pid_Set(sensor.get_sensor_set().vertical,control.get_control_set().vertical,bird_set.vertical)))
        {
        }
        
        void run()
        {
            while(sensor_.update() && control_.update())
            {
                roll_.update();
                pitch_.update();
                yaw_.update();
                lateral_.update();
                longitudinal_.update();
                vertical_.update();
            }
        }
        
    private:
        Configuration &configuration_;
        Sensor &sensor_;
        Control &control_;
        Pid roll_;
        Pid pitch_;
        Pid yaw_;
        Pid lateral_;      // Left - Right
        Pid longitudinal_; // Backward - Forward
        Pid vertical_;     // Down - Up
        
    };

}
