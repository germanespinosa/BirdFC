#pragma once
#include<vector>
#include <math.h>
namespace bird
{
    enum Rotation {clockwise = 1, counterclockwise = -1};
    
    struct Propeller
    {
    public:
        Propeller()
        {}
        Propeller(double angle, Rotation rotation)
            : pitch_ratio(cos(angle))
            , roll_ratio(sin(angle))
            , yaw_ratio (rotation)
            , longitudinal_ratio (pitch_ratio)
            , lateral_ratio (roll_ratio)
            , vertical_ratio (1)
        {}
        double roll_ratio;
        double pitch_ratio;
        double yaw_ratio;
        double lateral_ratio;      // Left - Right
        double longitudinal_ratio; // Backward - Forward
        double vertical_ratio;     // Down - Up
    };

    struct Configuration
    {
    public:
        Configuration (std::initializer_list<double> angles, Rotation rotation);
        void invert_propellers();
        static Configuration plus()
            {return Configuration({0,M_PI*.5,M_PI,M_PI*1.5}, Rotation::clockwise);}
        static Configuration x()
            {return Configuration({M_PI*.25,M_PI*.75,M_PI*1.25,M_PI*1.75}, Rotation::clockwise);}
        std::vector<Propeller> propellers;
        
    };
};