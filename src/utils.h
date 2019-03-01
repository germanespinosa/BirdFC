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
        double size()
            {return max-min;}
        double cap(double value)
            {return std::max(std::min(value,max),min);}
        bool between(double value)
            {return value<=max && value>=min;}
        double adjust(double value, Range  range)
            {return (value - range.min) / range.size() * size() + min;}
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
    struct Target
    {
    public:
        double value = 0;
        double change_speed = 0;
    };
}