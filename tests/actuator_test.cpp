#include<catch.h>
#include"../src/core/actuator.h"

TEST_CASE("propeller ratios")
{
    bird::Propeller propeller(0,bird::Rotation::clockwise);
    CHECK(propeller.ratios.roll == 0);
    CHECK(propeller.ratios.pitch == 1);
}

TEST_CASE("Actuator_Set plus")
{ 
    double epsilon = .0001;
    bird::Actuator_Set actuator = bird::Actuator_Set::plus();
    CHECK(std::abs(actuator.propellers[0].ratios.roll) < epsilon );
    CHECK(std::abs(actuator.propellers[1].ratios.roll - 1) < epsilon);
    CHECK(std::abs(actuator.propellers[2].ratios.roll) < epsilon);
    CHECK(std::abs(actuator.propellers[3].ratios.roll + 1) < epsilon);
    CHECK(std::abs(actuator.propellers[0].ratios.pitch - 1) < epsilon);
    CHECK(std::abs(actuator.propellers[1].ratios.pitch) < epsilon);
    CHECK(std::abs(actuator.propellers[2].ratios.pitch + 1) < epsilon);
    CHECK(std::abs(actuator.propellers[3].ratios.pitch) < epsilon);
}

TEST_CASE("Actuator_Set x")
{
    double epsilon = .0001;
    bird::Actuator_Set actuator = bird::Actuator_Set::x();
    CHECK(std::abs(actuator.propellers[0].ratios.roll - .7071) < epsilon );
    CHECK(std::abs(actuator.propellers[1].ratios.roll - .7071) < epsilon);
    CHECK(std::abs(actuator.propellers[2].ratios.roll + .7071) < epsilon);
    CHECK(std::abs(actuator.propellers[3].ratios.roll + .7071) < epsilon);
    CHECK(std::abs(actuator.propellers[0].ratios.pitch - .7071) < epsilon);
    CHECK(std::abs(actuator.propellers[1].ratios.pitch + .7071) < epsilon);
    CHECK(std::abs(actuator.propellers[2].ratios.pitch + .7071) < epsilon);
    CHECK(std::abs(actuator.propellers[3].ratios.pitch - .7071) < epsilon);
}

TEST_CASE("Actuator_Set rotation")
{
    bird::Actuator_Set actuator = bird::Actuator_Set::plus();
    CHECK(actuator.propellers[0].ratios.yaw == bird::Rotation::clockwise);
    CHECK(actuator.propellers[1].ratios.yaw == bird::Rotation::counterclockwise);
    CHECK(actuator.propellers[2].ratios.yaw == bird::Rotation::clockwise);
    CHECK(actuator.propellers[3].ratios.yaw == bird::Rotation::counterclockwise);
}

TEST_CASE("Actuator_Set invert rotation")
{
    bird::Actuator_Set actuator = bird::Actuator_Set::plus();
    actuator.invert_propellers();
    CHECK(actuator.propellers[0].ratios.yaw == bird::Rotation::counterclockwise);
    CHECK(actuator.propellers[1].ratios.yaw == bird::Rotation::clockwise);
    CHECK(actuator.propellers[2].ratios.yaw == bird::Rotation::counterclockwise);
    CHECK(actuator.propellers[3].ratios.yaw == bird::Rotation::clockwise);
    
}
