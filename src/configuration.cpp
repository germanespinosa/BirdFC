#include"configuration.h"

namespace bird
{
    Configuration::Configuration (std::initializer_list<double> angles, Rotation rotation)
    {
        for (double angle : angles)
        {
            propellers.push_back(Propeller(angle, rotation));
            rotation = rotation == Rotation::clockwise ? Rotation::counterclockwise : Rotation::clockwise;
        }
    }
    
    void Configuration::invert_propellers()
    { 
        for (Propeller &prop : propellers)
            prop.yaw_ratio = -prop.yaw_ratio ;
    }
    
}