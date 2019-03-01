#include<catch.h>
#include"../src/actuation.h"

TEST_CASE("propeller ratios")
{
    bird::Propeller propeller(0,bird::Rotation::clockwise);
    CHECK(propeller.ratios.roll_ratio == 0);
    CHECK(propeller.ratios.pitch_ratio == 1);
}

TEST_CASE("Actuation plus")
{
    double epsilon = .0001;
    bird::Actuation actuation = bird::Actuation::plus();
    CHECK(std::abs(actuation.propellers[0].ratios.roll_ratio) < epsilon );
    CHECK(std::abs(actuation.propellers[1].ratios.roll_ratio - 1) < epsilon);
    CHECK(std::abs(actuation.propellers[2].ratios.roll_ratio) < epsilon);
    CHECK(std::abs(actuation.propellers[3].ratios.roll_ratio + 1) < epsilon);
    CHECK(std::abs(actuation.propellers[0].ratios.pitch_ratio - 1) < epsilon);
    CHECK(std::abs(actuation.propellers[1].ratios.pitch_ratio) < epsilon);
    CHECK(std::abs(actuation.propellers[2].ratios.pitch_ratio + 1) < epsilon);
    CHECK(std::abs(actuation.propellers[3].ratios.pitch_ratio) < epsilon);
}

TEST_CASE("Actuation x")
{
    double epsilon = .0001;
    bird::Actuation actuation = bird::Actuation::x();
    CHECK(std::abs(actuation.propellers[0].ratios.roll_ratio - .7071) < epsilon );
    CHECK(std::abs(actuation.propellers[1].ratios.roll_ratio - .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[2].ratios.roll_ratio + .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[3].ratios.roll_ratio + .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[0].ratios.pitch_ratio - .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[1].ratios.pitch_ratio + .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[2].ratios.pitch_ratio + .7071) < epsilon);
    CHECK(std::abs(actuation.propellers[3].ratios.pitch_ratio - .7071) < epsilon);
}

TEST_CASE("Actuation rotation")
{
    bird::Actuation actuation = bird::Actuation::plus();
    CHECK(actuation.propellers[0].ratios.yaw_ratio == bird::Rotation::clockwise);
    CHECK(actuation.propellers[1].ratios.yaw_ratio == bird::Rotation::counterclockwise);
    CHECK(actuation.propellers[2].ratios.yaw_ratio == bird::Rotation::clockwise);
    CHECK(actuation.propellers[3].ratios.yaw_ratio == bird::Rotation::counterclockwise);
}

TEST_CASE("Actuation invert rotation")
{
    bird::Actuation actuation = bird::Actuation::plus();
    actuation.invert_propellers();
    CHECK(actuation.propellers[0].ratios.yaw_ratio == bird::Rotation::counterclockwise);
    CHECK(actuation.propellers[1].ratios.yaw_ratio == bird::Rotation::clockwise);
    CHECK(actuation.propellers[2].ratios.yaw_ratio == bird::Rotation::counterclockwise);
    CHECK(actuation.propellers[3].ratios.yaw_ratio == bird::Rotation::clockwise);
    
}
