#include "../../src/actuators/std_out.h"
#include "../../src/sensors/mpu9250.h"


struct Timed_Control : bird::Control
{
    Timed_Control()
    {
        timer.restart();
        control_set_.roll=0;
        control_set_.pitch=-0;
        control_set_.yaw=0;
        control_set_.vertical=0;
        control_set_.lateral=0;
        control_set_.longitudinal=0;
    }
    bird::Timer timer;
    bool update() override
    {
        if (timer.time_out(1))
        {
            timer.restart();
            control_set_.roll=-control_set_.roll;
            control_set_.pitch=-control_set_.pitch;
            control_set_.yaw=-control_set_.yaw;
        }
        return true;
    }
};

int main()
{
    bird::Mpu9250 imu;
    int i=0;
	
	std::vector<bird::Propeller> propellers;
	
	propellers.push_back(bird::Output_Ratios({1,0,0,0,0,0}));
	propellers.push_back(bird::Output_Ratios({0,1,0,0,0,0}));
	propellers.push_back(bird::Output_Ratios({0,0,1,0,0,0}));
	
	bird::Actuator_Set as = bird::Actuator_Set(propellers);
	
    bird::Std_Out so(as,.5);
    bird::Bird_Set bs;
    Timed_Control tc;
    
    bs.roll.proportional = 1;
	bs.roll.proportional.range = {-bird::PI,bird::PI};
    bs.pitch.proportional = 1;
	bs.pitch.proportional.range = {-bird::PI,bird::PI};
    bs.yaw.proportional = 1;
	bs.yaw.proportional.range = {-bird::PI,bird::PI};
    bs.vertical.proportional = 1;
    bs.lateral.proportional = 1;
    bs.longitudinal.proportional = 1;
    
    bs.roll.derivative = 0;
    bs.pitch.derivative = 0;
    bs.yaw.derivative = 0;
    bs.vertical.derivative = 0;
    bs.lateral.derivative = 0;
    bs.longitudinal.derivative = 0;
    
    bs.roll.integral = 0;
    bs.pitch.integral = 0;
    bs.yaw.integral = 0;
    bs.vertical.integral = 0;
    bs.lateral.integral = 0;
    bs.longitudinal.integral = 0;
    
    bird::Bird bird (imu,tc,so,bs);
    bird.run();
}
