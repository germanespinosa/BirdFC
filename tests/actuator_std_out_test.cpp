#include<catch.h>
#include"../src/actuators/std_out.h"


TEST_CASE("initialization")
{
    bird::Std_Out screen;
    bird::Actuator_Set set = screen.get_actuator_set();
    for (int i=0;i<10;i++)
    {
        for (bird::Propeller p : set.propellers)
            p=i;
        screen.update();
    }
}