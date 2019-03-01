#include "utils.h"

namespace bird
{
    
    struct Control_Set
    {
        Target roll;
        Target pitch;
        Target yaw;
        Target lateral;      // Left - Right
        Target longitudinal; // Backward - Forward
        Target vertical;     // Down - Up
    };
    
    struct Control
    {
    public:
        virtual bool update() = 0;
        Control_Set &get_control_set()
        {
            return control_set_;
        }
    private:
        Control_Set control_set_; 
    };
}