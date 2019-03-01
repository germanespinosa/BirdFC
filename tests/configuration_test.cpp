#include<catch.h>
#include"../src/configuration.h"

TEST_CASE("propeller ratios")
{
    bird::Propeller propeller(0,bird::Rotation::clockwise);
    CHECK(propeller.roll_ratio == 0);
    CHECK(propeller.pitch_ratio == 1);
}

TEST_CASE("configuration plus")
{
    double epsilon = .0001;
    bird::Configuration configuration = bird::Configuration::plus();
    CHECK(std::abs(configuration.propellers[0].roll_ratio) < epsilon );
    CHECK(std::abs(configuration.propellers[1].roll_ratio - 1) < epsilon);
    CHECK(std::abs(configuration.propellers[2].roll_ratio) < epsilon);
    CHECK(std::abs(configuration.propellers[3].roll_ratio + 1) < epsilon);
    CHECK(std::abs(configuration.propellers[0].pitch_ratio - 1) < epsilon);
    CHECK(std::abs(configuration.propellers[1].pitch_ratio) < epsilon);
    CHECK(std::abs(configuration.propellers[2].pitch_ratio + 1) < epsilon);
    CHECK(std::abs(configuration.propellers[3].pitch_ratio) < epsilon);
}

TEST_CASE("configuration x")
{
    double epsilon = .0001;
    bird::Configuration configuration = bird::Configuration::x();
    CHECK(std::abs(configuration.propellers[0].roll_ratio - .7071) < epsilon );
    CHECK(std::abs(configuration.propellers[1].roll_ratio - .7071) < epsilon);
    CHECK(std::abs(configuration.propellers[2].roll_ratio + .7071) < epsilon);
    CHECK(std::abs(configuration.propellers[3].roll_ratio + .7071) < epsilon);
    CHECK(std::abs(configuration.propellers[0].pitch_ratio - .7071) < epsilon);
    CHECK(std::abs(configuration.propellers[1].pitch_ratio + .7071) < epsilon);
    CHECK(std::abs(configuration.propellers[2].pitch_ratio + .7071) < epsilon);
    CHECK(std::abs(configuration.propellers[3].pitch_ratio - .7071) < epsilon);
}

TEST_CASE("configuration rotation")
{
    bird::Configuration configuration = bird::Configuration::plus();
    CHECK(configuration.propellers[0].yaw_ratio == bird::Rotation::clockwise);
    CHECK(configuration.propellers[1].yaw_ratio == bird::Rotation::counterclockwise);
    CHECK(configuration.propellers[2].yaw_ratio == bird::Rotation::clockwise);
    CHECK(configuration.propellers[3].yaw_ratio == bird::Rotation::counterclockwise);
    
}

TEST_CASE("configuration invert rotation")
{
    bird::Configuration configuration = bird::Configuration::plus();
    configuration.invert_propellers();
    CHECK(configuration.propellers[0].yaw_ratio == bird::Rotation::counterclockwise);
    CHECK(configuration.propellers[1].yaw_ratio == bird::Rotation::clockwise);
    CHECK(configuration.propellers[2].yaw_ratio == bird::Rotation::counterclockwise);
    CHECK(configuration.propellers[3].yaw_ratio == bird::Rotation::clockwise);
    
}
