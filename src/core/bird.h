#include <functional>
#include<iostream>
#include<thread>
#include<mutex>
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
        std::thread sensor_thread_;
        std::thread control_thread_; 
        static void update_sensor_(Bird &bird);
        static void update_control_(Bird &bird);
        Timer sensor_timer_ = 0;
        Timer control_timer_ = 0;
        Sensor &sensor_;
        Control &control_;
        Sensor_Set sensor_set_;
        Control_Set control_set_;
        Actuator &actuator_;
        Pid roll_;
        Pid pitch_;
        Pid yaw_;
        Pid lateral_;      // Left - Right
        Pid longitudinal_; // Backward - Forward
        Pid vertical_;     // Down - Up
        
    };

}
