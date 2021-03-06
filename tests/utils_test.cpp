#include<catch.h>
#include"../src/core/utils.h"

TEST_CASE("range small")
{
    bird::Range range(.03,.04);
    CHECK( range.min == .03 );
    CHECK( range.max == .04 );
}

TEST_CASE("range big")
{
    bird::Range range(1,1000000);
    CHECK( range.min == 1 );
    CHECK( range.max == 1000000 );
}

TEST_CASE("range negative")
{
    bird::Range range(-1000000,1000000);
    CHECK( range.min == -1000000 );
    CHECK( range.max == 1000000 );
}

TEST_CASE("range between true")
{
    bird::Range range(.03,.04);
    CHECK( range.between(.03) );
    CHECK( range.between(.031) );
    CHECK( range.between(.039) );
    CHECK( range.between(.04) );
}

TEST_CASE("range between false")
{
    bird::Range range(.03,.04);
    CHECK( !range.between(.029) );
    CHECK( !range.between(.041) );
}

TEST_CASE("range cap")
{
    bird::Range range(5,10);
    CHECK( range.cap(1) == 5 );
    CHECK( range.cap(100) == 10 );
}

TEST_CASE("range size")
{
    bird::Range range(-10,10);
    CHECK( range.size() == 20 );
}

TEST_CASE("range adjust")
{
    bird::Range range1(-10,10);
    bird::Range range2(0,100);
    CHECK(range1.adjust(75,range2) == 5);
    CHECK(range1.adjust(50,range2) == 0);
    CHECK(range2.adjust(-5,range1) == 25);
    CHECK(range2.adjust(0,range1) == 50);
    CHECK(range2.adjust(10,range2) == 10);
}
TEST_CASE("timer fixed")
{
    bird::Timer timer(.5);
    CHECK(timer.restart() == .5);
    CHECK(timer.elapsed() == .5);
}

TEST_CASE("timer dynamic")
{
    bird::Timer timer;
    while(timer.elapsed() <.01);
    CHECK(timer.restart() >  0);
    while(timer.elapsed() <.01);
    CHECK(timer.restart() < .1);
}

TEST_CASE("timer time_out")
{
    bird::Timer timer;
    CHECK(!timer.time_out(.01));
    while(timer.elapsed() <.01);
    CHECK(timer.time_out(.01));
}

TEST_CASE("composite filter")
{
    bird::Complementary_Filter cf1 = bird::Complementary_Filter({-1,1},.5);
    cf1.update(-1,1);
    CHECK(cf1.value == 0);
    bird::Complementary_Filter cf2 = bird::Complementary_Filter({-1,1},.25);
    cf2.update(-1,1);
    CHECK(cf2.value == 0.5);
    bird::Complementary_Filter cf3 = bird::Complementary_Filter({-1,1},.9);
    cf3.update(-1,1);
    CHECK(cf3.value == -0.8);
}

TEST_CASE("low pass filter")
{
    bird::Low_Pass_Filter lpf1 = bird::Low_Pass_Filter({-1,1},.5);
    lpf1=.5;
    CHECK(lpf1.value == .5);
    lpf1+=.5;
    CHECK(lpf1.value == .5);
    lpf1+=1;
    CHECK(lpf1.value == .75);
    lpf1+=-.75;
    CHECK(lpf1.value == 0);
}