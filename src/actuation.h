#pragma once
#include<vector>
#include <math.h>
namespace bird
{
    enum Rotation {clockwise = 1, counterclockwise = -1};
    

    struct Output_Ratios
    {
        double roll_ratio;
        double pitch_ratio;
        double yaw_ratio;
        double lateral_ratio;      // Left - Right
        double longitudinal_ratio; // Backward - Forward
        double vertical_ratio;     // Down - Up
    };

    struct Propeller
    {
    public:
        Propeller()
        {}
        Propeller(double angle, Rotation rotation)
            : ratios ({sin(angle),cos(angle),(double)rotation, sin(angle), cos(angle), 1})
        {}
        Output_Ratios ratios;
        double output_value;
    };

    struct Actuation
    {
    public:
        Actuation (std::initializer_list<double> angles, Rotation rotation);
        void invert_propellers();
        static Actuation plus()
            {return Actuation({0,M_PI*.5,M_PI,M_PI*1.5}, Rotation::clockwise);}
        static Actuation x()
            {return Actuation({M_PI*.25,M_PI*.75,M_PI*1.25,M_PI*1.75}, Rotation::clockwise);}
        
        void update()
        {
            
        }
        
        std::vector<Propeller> propellers;
    };
};