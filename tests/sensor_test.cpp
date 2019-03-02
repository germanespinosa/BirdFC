#include<catch.h>
#include"../src/sensor.h"

TEST_CASE("sensor_data update_value")
{
    bird::Sensor_Data sensor_data(.01);
    double change_speed = 2000;
    sensor_data.update_value(change_speed);
    CHECK(sensor_data.variable.value == 20);
    CHECK(sensor_data.variable.change_speed == 2000);
}

TEST_CASE("sensor_data update_change_speed")
{
    bird::Sensor_Data sensor_data(.01);
    double value = 20;
    sensor_data.update_change_speed(value);
    CHECK(sensor_data.variable.change_speed == 2000);
    CHECK(sensor_data.variable.value == 20);
}

TEST_CASE("sensor_data accumulative update_value")
{
    bird::Sensor_Data sensor_data(.01);
    double change_speed = 2000;
    sensor_data.update_value(change_speed);
    CHECK(sensor_data.variable.value == 20);
    CHECK(sensor_data.variable.change_speed == 2000);
    change_speed = 1000;
    sensor_data.update_value(change_speed);
    CHECK(sensor_data.variable.value == 30);
    CHECK(sensor_data.variable.change_speed == 1000);
    change_speed = -5000;
    sensor_data.update_value(change_speed);
    CHECK(sensor_data.variable.value == -20);
    CHECK(sensor_data.variable.change_speed == -5000);
}

TEST_CASE("sensor_data iterative update_change_speed")
{
    bird::Sensor_Data sensor_data(.01);
    double value = 20;
    sensor_data.update_change_speed(value);
    CHECK(sensor_data.variable.change_speed == 2000);
    CHECK(sensor_data.variable.value == 20);
    value = 30;
    sensor_data.update_change_speed(value);
    CHECK(sensor_data.variable.change_speed == 1000);
    CHECK(sensor_data.variable.value == 30);
    value = -20;
    sensor_data.update_change_speed(value);
    CHECK(sensor_data.variable.change_speed == -5000);
    CHECK(sensor_data.variable.value == -20);
}
