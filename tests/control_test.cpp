#include<catch.h>
#include"../src/core/control.h"

TEST_CASE("control_set ranges")
{
    bird::Control_Set set;
    CHECK(set.roll.range.min == -1);
    CHECK(set.pitch.range.min == -1);
    CHECK(set.yaw.range.min == -1);
    CHECK(set.vertical.range.min == -1);
    CHECK(set.lateral.range.min == -1);
    CHECK(set.longitudinal.range.min == -1);
    CHECK(set.roll.range.max == 1);
    CHECK(set.pitch.range.max == 1);
    CHECK(set.yaw.range.max == 1);
    CHECK(set.vertical.range.max == 1);
    CHECK(set.lateral.range.max == 1);
    CHECK(set.longitudinal.range.max == 1);
}

struct ST : bird::Control
{
    bool update() override
    {
        control_set_.roll.value+=1;
        control_set_.pitch.value+=1;
        control_set_.yaw.value+=1;
        control_set_.vertical.value+=1;
        control_set_.lateral.value+=1;
        control_set_.longitudinal.value+=1;
        return true;
    }
};

TEST_CASE("control_set inheritance")
{
    ST control;
    CHECK(control.update());
    CHECK(control.get_control_set().roll.value == 1);
    CHECK(control.get_control_set().pitch.value == 1);
    CHECK(control.get_control_set().yaw.value == 1);
    CHECK(control.get_control_set().vertical.value == 1);
    CHECK(control.get_control_set().lateral.value == 1);
    CHECK(control.get_control_set().longitudinal.value == 1);
    CHECK(control.update());
    CHECK(control.get_control_set().roll.value == 2);
    CHECK(control.get_control_set().pitch.value == 2);
    CHECK(control.get_control_set().yaw.value == 2);
    CHECK(control.get_control_set().vertical.value == 2);
    CHECK(control.get_control_set().lateral.value == 2);
    CHECK(control.get_control_set().longitudinal.value == 2);
}
