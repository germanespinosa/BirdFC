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
        , actuator_(actuator)
    {
        // spawn threads for the independent sensor and control update
        sensor_thread_ = std::thread (update_sensor_, std::ref(*this));
        control_thread_ = std::thread (update_control_, std::ref(*this));
    }
    
    void Bird::update_sensor_ (Bird &bird)
    {
        while(bird.active_)
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
        while(bird.active_)
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
		static Timer p;
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
				// to set the targets
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
            int i=0;
            for (Propeller &propeller:actuator_set_.propellers)
            {
                double output = 0;
                output += roll_ * propeller.ratios.roll;
                output += pitch_ * propeller.ratios.pitch;
                output += yaw_ * propeller.ratios.yaw;
                output += lateral_ * propeller.ratios.lateral;
                output += longitudinal_ * propeller.ratios.longitudinal;
                output += vertical_ * propeller.ratios.vertical;
                propeller = output;
            }
            // update the actuator 
			
            if (actuator_.update())
            {
                actuator_timer_.restart();
            }
        }
        active_=false;
        sensor_thread_.join();
        control_thread_.join();
    }
}
