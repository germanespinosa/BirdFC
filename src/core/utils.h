#pragma once
#include<algorithm>
#include <sys/time.h>
#include <math.h>
namespace bird
{
    const double PI = M_PI;

    struct Range
    {
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
        bool time_out(double secs);
    private:
        timeval start_time_;
        timeval current_time_;
        double fixed_time = 0;
        
    };
    struct Variable
    {
    public:
        Variable (){}
        Variable (Range range)
            : range (range) {}
        double value = 0;
        double change_speed = 0;
        Range range{0,0};
        double operator = (double v)
        {
            value = v;
            return v; 
        }
        void adjust (double new_value, Range from_range)
        {
            value = range.adjust(new_value,from_range);
        }
        bool operator == ( double v)
        {
            return v == value;
        }
        bool operator == ( Variable v)
        {
            return v.value == value;
        }
    };
    struct Low_Pass_Filter : public Variable
    {
        Low_Pass_Filter (Range range, double update_rate)
            : Variable (range)
            , update_rate (update_rate) {};
        double update_rate = 0;
        double operator = (double v)
        {
            value = v;
            return v; 
        }
        double operator += (double v)
        {
            value = (v * update_rate) + (value * (1 - update_rate));
            return value; 
        }
        double operator += (Variable v)
        {
            return *(this) += v.value; 
        }
    };
    struct Complementary_Filter : public Variable
    {
        Complementary_Filter (Range range, double rate)
            : Variable (range)
            , rate (rate) {};
        double rate = 0;
        double update(double first, double second);
        double operator = (double v)
        {
            value = v;
            return v; 
        }
    };
    
}