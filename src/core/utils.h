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
        double adjust(double value, Range range);
        Range operator-()
        {
            return {max,min};
        }
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
        Range range;
        double operator = (double v)
        {
            value = v;
            return v; 
        }
        void adjust (double new_value, Range from_range)
        {
            value = range.adjust(new_value,from_range);
            
        }
        
    };
}