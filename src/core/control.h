#pragma once
#include "utils.h"

namespace bird
{
    struct Control_Set
    {
        Variable roll         = Variable ({-1,1});
        Variable pitch        = Variable ({-1,1});
        Variable yaw          = Variable ({-1,1});
        Variable lateral      = Variable ({-1,1}); // Left - Right
        Variable longitudinal = Variable ({-1,1}); // Backward - Forward
        Variable vertical     = Variable ({-1,1}); // Down - Up
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