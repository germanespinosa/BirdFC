#include"actuator.h"

namespace bird
{
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
    
}