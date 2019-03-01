#include<catch.h>
#include"../src/actuation.h"

TEST_CASE("propeller ratios")
{
    bird::Propeller propeller(0,bird::Rotation::clockwise);
    CHECK(propeller.roll_ratio == 0);
    CHECK(propeller.pitch_ratio == 1);
}

TEST_CASE("Actuation plus")
{
    double epsilon = .0001;
    bird::Actuation actuation = bird::Actuation::plus();
    CHECK(std::abs(actuation.propellers[0].roll_ratio) < epsilon );
    CHECK(std::abs(actuation.propellers[1].roll_ratio - 1) < epsilon);
    CHECK(std::abs(actuation.propellers[2].roll_ratio) < epsilon);
    CHECK(std::abs(actuation.propellers[3].roll_ratio + 1) < epsilon);
    CHECK(std::abs(actuation.propellers[0].pitch_ratio - 1) < epsilon);
    CHECK(std::abs(actuation.propellers[1].pitch_ratio) < epsilon);
    CHECK(std::abs(actuation.propellers[2].pitch_ratio + 1) < epsilon);
    CHECK(std::abs(actuation.propellers[3].pitch_ratio) < epsilon);
}

TEST_CASE("Actuation x")
{
    double epsilon = .0001;
    bird::Actuation actuation = bird::Actuation::x();
    CHECK(std::abs(actuation.propellers[0].roll_ratio - .7071) < epsilon );
    CHECK(std::abs(actuation.propellers[1].roll_ratio - .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[2].roll_ratio + .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[3].roll_ratio + .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[0].pitch_ratio - .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[1].pitch_ratio + .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[2].pitch_ratio + .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[3].pitch_ratio - .7071) < epsilon);
}

TEST_CASE("Actuation rotation")
{
    bird::Actuation actuation = bird::Actuation::plus();
    CHECK(actuation.propellers[0].yaw_ratio == bird::Rotation::clockwise);
    CHECK(actuation.propellers[1].yaw_ratio == bird::Rotation::counterclockwise);
    CHECK(actuation.propellers[2].yaw_ratio == bird::Rotation::clockwise);
    CHECK(actuation.propellers[3].yaw_ratio == bird::Rotation::counterclockwise);
}

TEST_CASE("Actuation invert rotation")
{
    bird::Actuation actuation = bird::Actuation::plus();
    actuation.invert_propellers();
    CHECK(actuation.propellers[0].yaw_ratio == bird::Rotation::counterclockwise);
    CHECK(actuation.propellers[1].yaw_ratio == bird::Rotation::clockwise);
    CHECK(actuation.propellers[2].yaw_ratio == bird::Rotation::counterclockwise);
    CHECK(actuation.propellers[3].yaw_ratio == bird::Rotation::clockwise);
    
}
