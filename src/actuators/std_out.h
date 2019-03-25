#include "../core/bird.h"

namespace bird 
{
    struct Std_Out : Actuator
    {
		Std_Out(Actuator_Set, double refresh_rate);
        Std_Out(double refresh_rate);
        bool update() override;
        Timer timer_;
        double refresh_rate_;
		Range range {-100,100};
    };
}