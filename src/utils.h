#pragma once
#include<algorithm>
#include <sys/time.h>
namespace bird
{
    struct Range
    {
        public:
        Range(double min_value, double max_value)
            :min(min_value)
            ,max(max_value){}
        double min;
        double max;
        double size();
        double cap(double value);
        bool between(double value);
        double adjust(double value, Range  range);
    };
    struct Timer
    {
        Timer();
        Timer(double secs);
        double restart();
        double elapsed();
    private:
        timeval start_time_;
        timeval current_time_;
        double fixed_time = 0;
        
    };
    struct Variable
    {
    public:
        double value = 0;
        double change_speed = 0; //units per second
    };
}