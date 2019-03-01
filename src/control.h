#include "utils.h"

namespace bird
{
    
    struct Control_Set
    {
        Value roll;
        Value pitch;
        Value yaw;
        Value lateral;      // Left - Right
        Value longitudinal; // Backward - Forward
        Value vertical;     // Down - Up
    };
    
    struct Control
    {
    public:
        virtual bool update() = 0;
        Control_Set &get_control_set();
    private:
        Control_Set control_set_; 
    };
}