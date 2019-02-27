#include<catch.h>
#include"../src/pid.h"

TEST_CASE("pid_initialization")
{
    Pid_Controller pid;
    Pid_Target target;
    target.value = 0;
    target.change_speed = 0;
    Pid_Set set;
    set.value = 1;
    set.proportional_term.multiplier=1;
    set = pid.process(set,target);
    CHECK(set.value_error == -1);
}
