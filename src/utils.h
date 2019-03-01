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
        Timer()
        {
            gettimeofday(&start_time_, NULL);
        }
        Timer(double secs)
            :fixed_time (secs)
        {
        }
        double restart()
        {
            double secs = elapsed();
            start_time_ = current_time_;
        }
        double elapsed()
        {
            if (fixed_time) return fixed_time;
            gettimeofday(&current_time_, NULL);
            return (double) (current_time_.tv_usec - start_time_.tv_usec) / 1000000 +
                   (double) (current_time_.tv_sec - start_time_.tv_sec);
        }
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