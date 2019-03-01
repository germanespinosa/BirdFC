#include"utils.h"

namespace bird
{
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