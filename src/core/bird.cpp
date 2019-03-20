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
        // spawn threads for the independent sensor and control update
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
        double &roll_pid = roll_.get_pid_set().value;
        double &pitch_pid = pitch_.get_pid_set().value;
        double &yaw_pid = yaw_.get_pid_set().value;
        double &lateral_pid = lateral_.get_pid_set().value;
        double &longitudinal_pid = longitudinal_.get_pid_set().value;
        double &vertical_pid = vertical_.get_pid_set().value;
        Actuator_Set &actuator_set_ = actuator_.get_actuator_set();
        sensor_timer_.restart();
        control_timer_.restart();
        actuator_timer_.restart();
        while( !actuator_timer_.time_out(.5) &&
               !sensor_timer_.time_out(.5) && 
               !control_timer_.time_out(.5))
        {
            {
                // lock the results while they are been used
                // to compute the outputs of the pids controllers
                std::mutex mtx; 
                roll_.update();
                pitch_.update();
                yaw_.update();
                lateral_.update();
                longitudinal_.update();
                vertical_.update();
            }
            // use the pids outputs to update the 
            // propeller values
            for (Propeller propeller:actuator_set_.propellers)
            {
                double output = 0;
                output += roll_pid * propeller.ratios.roll;
                output += pitch_pid * propeller.ratios.pitch;
                output += yaw_pid * propeller.ratios.yaw;
                output += lateral_pid * propeller.ratios.lateral;
                output += longitudinal_pid * propeller.ratios.longitudinal;
                output += vertical_pid * propeller.ratios.vertical;
                propeller.output_value = output;
            }
            // update the actuator 
            if (actuator_.update())
            {
                actuator_timer_.restart();
            }
        }
    }
}
