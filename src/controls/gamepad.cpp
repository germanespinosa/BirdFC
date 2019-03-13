#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../src/control.h"



namespace bird
{
    struct Gamepad : Control
    {
        Gamepad()
        {
            char devname[] = "/dev/input/event0";
            device = open(devname, O_RDONLY);
            signal(SIGINT, Gamepad::INThandler);
        }
        static void INThandler(int i){
                exit(0);
        }
        
        bool update() override
        {
            read(device,&ev, sizeof(ev));
            if(ev.type == 1 && ev.value == 1){
                    printf("Key: %i State: %i\n",ev.code,ev.value);
            }
            printf("Event: %i Code: %i State: %i\n",ev.type,ev.code, ev.value);
            if (ev.type == 3)
            {
                switch (ev.code)
                {
                    case Game_Pad_Events_Codes::yaw:
                        control_set_.yaw.adjust(ev.value,joystick_range);
                        break;
                    case Game_Pad_Events_Codes::roll:
                        control_set_.roll.adjust(ev.value,joystick_range);
                        break;
                    case Game_Pad_Events_Codes::pitch:
                        control_set_.pitch.adjust(ev.value,joystick_range);
                        break;
                    case Game_Pad_Events_Codes::vertical:
                        control_set_.vertical.adjust(ev.value,-joystick_range);
                        break;
                }
            }
            printf("roll: %f pitch: %f yaw: %f vertical: %f\n",control_set_.roll.value,control_set_.pitch.value, control_set_.yaw.value, control_set_.vertical.value);
        }
        struct input_event ev;
        int device;
        Range joystick_range{0,256};
        enum Game_Pad_Events_Codes
        {
            yaw   =0,
            vertical = 1,
            roll  =2,
            pitch = 5
        };
    };
}

int main()
{
    bird::Gamepad g;
    while(1)
    g.update();
}