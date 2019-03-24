#pragma once
#include<vector>
#include <math.h>
namespace bird
{
    enum Rotation {clockwise = 1, counterclockwise = -1};
    

    struct Output_Ratios
    {
        double roll;
        double pitch;
        double yaw;
        double lateral;      // Left - Right
        double longitudinal; // Backward - Forward
        double vertical;     // Down - Up
    };

    struct Propeller
    {
    public:
        Propeller()
        {}
        Propeller(double angle, Rotation rotation);
        Output_Ratios ratios;
        double output_value;
        double operator = (double v)
        {
            return output_value = v;
        }
        operator double ()
        {
            return output_value;
        }
    };

    struct Actuator_Set
    {
    public:
        Actuator_Set (std::initializer_list<double> angles, Rotation rotation);
        void invert_propellers();
        static Actuator_Set plus()
        {
            return Actuator_Set({0,M_PI*.5,M_PI,M_PI*1.5}, Rotation::clockwise);
        }
        static Actuator_Set x()
        {
            return Actuator_Set({M_PI*.25,M_PI*.75,M_PI*1.25,M_PI*1.75}, Rotation::clockwise);
        }
        std::vector<Propeller> propellers;
    };
    
    struct Actuator
    {
        Actuator(Actuator_Set actuator_set)
            : actuator_set_ (actuator_set){};
    public:
        virtual bool update() = 0;
        Actuator_Set &get_actuator_set();
    protected:
        Actuator_Set actuator_set_;
    };    
};