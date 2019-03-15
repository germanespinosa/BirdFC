#pragma once

#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../core/bird.h"

namespace bird
{
    struct Gamepad : Control
    {
    public:
        Gamepad();
        Gamepad(std::string device_path);
        static void INThandler(int i);
        bool update() override;
    private:
        int device_handler_;
        enum Game_Pad_Events_Codes_
        {
            yaw      = 0,
            vertical = 1,
            roll     = 2,
            pitch    = 5
        };
    };
}
