#include "utils.h"

namespace bird
{
    
    struct Control_Set
    {
        Variable roll{0,0,{-1,1}};
        Variable pitch{0,0,{-1,1}};
        Variable yaw{0,0,{-1,1}};
        Variable lateral{0,0,{-1,1}};      // Left - Right
        Variable longitudinal{0,0,{-1,1}}; // Backward - Forward
        Variable vertical{0,0,{-1,1}};     // Down - Up
    };
    
    struct Control
    {
    public:
        virtual bool update() = 0;
        Control_Set &get_control_set();
    protected:
        Control_Set control_set_; 
    };
}