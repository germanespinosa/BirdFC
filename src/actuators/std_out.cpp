#include "std_out.h"

bird::Std_Out::Std_Out()
    : bird::Actuator(bird::Actuator_Set::plus())
{
}

bool bird::Std_Out::update()
{
    for (bird::Propeller p : actuator_set_.propellers)
    {
        std::cout << p.output_value << "\t";
    }
    std::cout << "\n";
    return true;
}
int main()
{
    bird::Std_Out s;
}