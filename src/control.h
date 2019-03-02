#include "utils.h"

namespace bird
{
    
    struct Control_Set
    {
        Variable roll;
        Variable pitch;
        Variable yaw;
        Variable lateral;      // Left - Right
        Variable longitudinal; // Backward - Forward
        Variable vertical;     // Down - Up
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