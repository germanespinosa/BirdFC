#include "../core/bird.h"

namespace bird 
{
    struct Std_Out : Actuator
    {
        Std_Out();
        bool update() override;
        Timer timer_;
    };
}