#include <iostream>
#include"utils.h"
#include"pid.h"
#include"actuator.h"
#include"sensor.h"
#include"control.h"
#include"i2c.h"

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
        Bird (Sensor &sensor, Control &control, Actuator &actuator, Bird_Set bird_set);
        
        void run();
        
    private:
        Actuator &actuator_;
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
