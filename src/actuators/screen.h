#include <bird.h>

namespace bird 
{
    struct Screen : Actuator
    {
        Screen();
        bool update() override;
    };
}