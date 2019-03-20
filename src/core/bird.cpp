#include"bird.h"

namespace bird
{

    Bird::Bird (Sensor &sensor, Control &control, Actuator &actuator, Bird_Set bird_set)
        : sensor_(sensor)
        , control_(control)
        , roll_ (Pid(Pid_Set(sensor_set_.roll,control_set_.roll,bird_set.roll)))
        , pitch_ (Pid(Pid_Set(sensor_set_.pitch,control_set_.pitch,bird_set.pitch)))
        , yaw_ (Pid(Pid_Set(sensor_set_.yaw,control_set_.yaw,bird_set.yaw)))
        , lateral_ (Pid(Pid_Set(sensor_set_.lateral,control_set_.lateral,bird_set.lateral)))
        , longitudinal_ (Pid(Pid_Set(sensor_set_.longitudinal,control_set_.longitudinal,bird_set.longitudinal)))
        , vertical_ (Pid(Pid_Set(sensor_set_.vertical,control_set_.vertical,bird_set.vertical)))
        , actuator_(actuator_)
    {
        sensor_thread_ = std::thread (update_sensor_, std::ref(*this));
        control_thread_ = std::thread (update_control_, std::ref(*this));
    }
    
    void Bird::update_sensor_ (Bird &bird)
    {
        while(true)
        {
            if (bird.sensor_.update())
            {
                std::mutex mtx; // lock the results while they are copied
                bird.sensor_set_ = bird.sensor_.get_sensor_set();
                bird.sensor_timer_.restart();
            }
        }
    }

    void Bird::update_control_ (Bird &bird)
    {
        while(true)
        {
            if (bird.control_.update())
            {
                std::mutex mtx; // lock the results while they are copied
                bird.control_set_ = bird.control_.get_control_set();
                bird.control_timer_.restart();
            }
        }
    }

    void Bird::run()
    {
        
        Actuator_Set &actuator_set_ = actuator_.get_actuator_set();
        sensor_timer_.restart();
        control_timer_.restart();
        while(sensor_timer_.time_out(.5) && control_timer_.time_out(.5))
        {
            {
                std::mutex mtx; // lock the results while they are been used
                roll_.update();
                pitch_.update();
                yaw_.update();
                lateral_.update();
                longitudinal_.update();
                vertical_.update();
            }
            for (Propeller propeller:actuator_set_.propellers)
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
