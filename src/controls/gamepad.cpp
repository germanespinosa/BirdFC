#include "gamepad.h"


bird::Gamepad::Gamepad()
{
    Gamepad("/dev/input/event0");
}

bird::Gamepad::Gamepad(std::string device_path)
{
    device_handler_ = open(device_path.c_str(), O_RDONLY);
    signal(SIGINT, Gamepad::INThandler);
}

void bird::Gamepad::INThandler(int i)
{
    exit(0);
}
        
bool bird::Gamepad::update()
{
    struct input_event ev;
    read(device_handler_,&ev, sizeof(ev));
    if (ev.type == 3)
    {
        Range joystick_range{0,256};
        switch (ev.code)
        {
            case Game_Pad_Events_Codes_::yaw:
                control_set_.yaw.adjust(ev.value,joystick_range);
                break;
            case Game_Pad_Events_Codes_::roll:
                control_set_.roll.adjust(ev.value,joystick_range);
                break;
            case Game_Pad_Events_Codes_::pitch:
                control_set_.pitch.adjust(ev.value,joystick_range);
                break;
            case Game_Pad_Events_Codes_::vertical:
                control_set_.vertical.adjust(ev.value,-joystick_range);
                break;
        }
    }
}