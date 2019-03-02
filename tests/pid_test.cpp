#include<catch.h>
#include"../src/pid.h"

TEST_CASE("pid error")
{
    bird::Pid_Configuration config = {{1,{-10,10}},{1,{-10,10}},{1,{-10,10}}};
    bird::Sensor_Data sensor_data;
    bird::Variable target;
    bird::Pid_Set set_init(sensor_data,target,config);
    bird::Pid pid(set_init);
    bird::Pid_Set &set = pid.get_pid_set();
    set.sensor_data.variable.value = 5;
    set.sensor_data.variable.change_speed = 10;
    set.sensor_data.period = .5;
    set.target.value = 0;
    set.target.change_speed = 0;
    pid.update();
    CHECK(set.value_error == -5);
    CHECK(set.change_speed_error == -10);
    CHECK(set.value == 2.5);
} 


TEST_CASE("pid proportional")
{
    bird::Pid_Configuration config = {{1,{-10,10}},{1,{-10,10}},{1,{-10,10}}};
    bird::Sensor_Data sensor_data;
    bird::Variable target;
    bird::Pid_Set set_init(sensor_data,target,config);
    bird::Pid pid(set_init);
    bird::Pid_Set &set = pid.get_pid_set();
    set.sensor_data.variable.value = 5;
    set.sensor_data.variable.change_speed = 10;
    set.sensor_data.period = .5;
    set.target.value = 0;
    set.target.change_speed = 0;
    pid.update();
    CHECK(set.proportional_value == -5);
}

TEST_CASE("pid derivative")
{
    bird::Pid_Configuration config = {{1,{-10,10}},{1,{-10,10}},{1,{-10,10}}};
    bird::Sensor_Data sensor_data;
    bird::Variable target;
    bird::Pid_Set set_init(sensor_data,target,config);
    bird::Pid pid(set_init);
    bird::Pid_Set &set = pid.get_pid_set();
    set.sensor_data.variable.value = 5;
    set.sensor_data.variable.change_speed = 10;
    set.sensor_data.period = .5;
    set.target.value = 0;
    set.target.change_speed = 5;
    pid.update();
    CHECK(set.derivative_value == -5);
}

TEST_CASE("pid integral")
{
    bird::Pid_Configuration config = {{1,{-10,10}},{1,{-10,10}},{1,{-10,10}}};
    bird::Sensor_Data sensor_data;
    bird::Variable target;
    bird::Pid_Set set_init(sensor_data,target,config);
    bird::Pid pid(set_init);
    bird::Pid_Set &set = pid.get_pid_set();
    set.sensor_data.variable.value = 5;
    set.sensor_data.variable.change_speed = 10;
    set.sensor_data.period = .5;
    set.target.value = 0;
    set.target.change_speed = 5;
    pid.update();
    CHECK(set.integral_value == -2.5);
    pid.update();
    CHECK(set.integral_value == -5);
    set.sensor_data.variable.value = -10;
    pid.update();
    CHECK(set.integral_value == 0);
}

TEST_CASE("pid proportional range")
{
    bird::Pid_Configuration config = {{1,{-10,10}},{1,{-10,10}},{1,{-10,10}}};
    bird::Sensor_Data sensor_data;
    bird::Variable target;
    bird::Pid_Set set_init(sensor_data,target,config);
    bird::Pid pid(set_init);
    bird::Pid_Set &set = pid.get_pid_set();
    set.sensor_data.variable.value = 15;
    set.sensor_data.variable.change_speed = 10;
    set.sensor_data.period = .5;
    set.target.value = 0;
    set.target.change_speed = 0;
    pid.update();
    CHECK(set.proportional_value == -10);
    set.sensor_data.variable.value = -15;
    pid.update();
    CHECK(set.proportional_value == 10);
}

TEST_CASE("pid derivative range")
{
    bird::Pid_Configuration config = {{1,{-10,10}},{1,{-10,10}},{1,{-10,10}}};
    bird::Sensor_Data sensor_data;
    bird::Variable target;
    bird::Pid_Set set_init(sensor_data,target,config);
    bird::Pid pid(set_init);
    bird::Pid_Set &set = pid.get_pid_set();
    set.sensor_data.variable.value = 5;
    set.sensor_data.variable.change_speed = 15;
    set.sensor_data.period = .5;
    set.target.value = 0;
    set.target.change_speed = 5;
    pid.update();
    CHECK(set.derivative_value == -10);
    set.sensor_data.variable.change_speed = -15;
    pid.update();
    CHECK(set.derivative_value == 10);
}

TEST_CASE("pid integral range")
{
    bird::Pid_Configuration config = {{1,{-10,10}},{1,{-10,10}},{1,{-10,10}}};
    bird::Sensor_Data sensor_data;
    bird::Variable target;
    bird::Pid_Set set_init(sensor_data,target,config);
    bird::Pid pid(set_init);
    bird::Pid_Set &set = pid.get_pid_set();
    set.sensor_data.variable.value = 10;
    set.sensor_data.period = .5;
    set.target.value = 0;
    set.target.change_speed = 5;
    pid.update();
    CHECK(set.integral_value == -5);
    pid.update();
    CHECK(set.integral_value == -10);
    pid.update();
    CHECK(set.integral_value == -10);
    set.sensor_data.variable.value = -10;
    pid.update();
    CHECK(set.integral_value == -5);
    pid.update();
    CHECK(set.integral_value == 0);
    pid.update();
    CHECK(set.integral_value == 5);
    pid.update();
    CHECK(set.integral_value == 10);
}
