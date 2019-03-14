#include "screen.h"

bird::Screen::Screen()
    : bird::Actuator(bird::Actuator_Set::plus())
{
}

bool bird::Screen::update()
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
    bird::Screen s;
}