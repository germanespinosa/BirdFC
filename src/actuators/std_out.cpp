#include "std_out.h"

bird::Std_Out::Std_Out()
    : bird::Actuator(bird::Actuator_Set::plus())
{
    timer_.restart();
}

bool bird::Std_Out::update()
{
    static int last_i=0;
    int i = timer_.elapsed();
    if (i!=last_i)
    {
        std::cout << i << " : ";
        for (bird::Propeller p : actuator_set_.propellers)
        {
            std::cout << p.output_value << "\t";
        }
        std::cout << "\n";
        last_i=i;
    }
    return true;
}
