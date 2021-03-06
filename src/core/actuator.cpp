#include"actuator.h"

namespace bird
{
	Propeller::Propeller (Output_Ratios ratios)
		: ratios(ratios)
	{}
	
    
	Actuator_Set::Actuator_Set (std::vector<Propeller> propellers)
		: propellers ( propellers ) 
	{}
	
    Propeller::Propeller(double angle, Rotation rotation)
        : ratios ({sin(angle),cos(angle),(double)rotation, sin(angle), cos(angle), 1})
    {}
    
    
    Actuator_Set::Actuator_Set (std::initializer_list<double> angles, Rotation rotation)
    {
        for (double angle : angles)
        {
            propellers.push_back(Propeller(angle, rotation));
            rotation = rotation == Rotation::clockwise ? Rotation::counterclockwise : Rotation::clockwise;
        }
    }
    
    void Actuator_Set::invert_propellers()
    { 
        for (Propeller &prop : propellers)
            prop.ratios.yaw = -prop.ratios.yaw ;
    }

    Actuator_Set &Actuator::get_actuator_set()
    {
        return actuator_set_;
    }    
}