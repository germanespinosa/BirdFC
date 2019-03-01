#include"utils.h"

namespace bird
{
    
    double Range::size()
    {
        return max-min;
    }
    double Range::cap(double value)
    {
        return std::max(std::min(value,max),min);
    }
    bool Range::between(double value)
    {
        return value<=max && value>=min;
    }
    double Range::adjust(double value, Range  range)
    {
        return (value - range.min) / range.size() * size() + min;
    }
    
    Timer::Timer()
    {
        gettimeofday(&start_time_, NULL);
    }
    Timer::Timer(double secs)
        :fixed_time (secs)
    {
    }
    double Timer::restart()
    {
        double secs = elapsed();
        start_time_ = current_time_;
    }
    double Timer::elapsed()
    {
        if (fixed_time) return fixed_time;
        gettimeofday(&current_time_, NULL);
        return (double) (current_time_.tv_usec - start_time_.tv_usec) / 1000000 +
               (double) (current_time_.tv_sec - start_time_.tv_sec);
    }
}