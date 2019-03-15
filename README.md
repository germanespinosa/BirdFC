# BirdFC
Bird is an Open Source flight controller for Raspberry PI hardware. 

Bird is built as an extensible framework, designed to adapt any drone configuration, providing a quick start for common parts and configuration.
Four propellers in "plus" and X, three propellers forward and backward, 6 and 8 propellers configurations are built in in the core but it is easibly extendible to new configurations with propellers in any direction and orientation. Common IMUs (like mpu9250) and pwm controllers (like pca8675) are already implemented, making its use simple and straight forward.

The flight controller provides a six degrees of freedom pid adjustable controller, with individual configurable parameters to tailor it to your specific device.


use:



int main()
{
    bird::Bird_Set parameters;

    parameters.roll.proportional.multiplier = rp;
    parameters.roll.integral.multiplier = rd;
    parameters.roll.derivative.multiplier = ri;

    parameters.pitch.proportional.multiplier = pp;
    parameters.pitch.integral.multiplier = pd;
    parameters.pitch.derivative.multiplier = pi;

    parameters.yaw.proportional.multiplier = yp;
    parameters.yaw.integral.multiplier = yd;
    parameters.yaw.derivative.multiplier = yi;

    parameters.vertical.proportional.multiplier = vp;
    parameters.vertical.integral.multiplier = vd;
    parameters.vertical.derivative.multiplier = vi;

    parameters.logitudinal.proportional.multiplier = lop;
    parameters.logitudinal.integral.multiplier = lod;
    parameters.logitudinal.derivative.multiplier = loi;

    parameters.lateral.proportional.multiplier = lap;
    parameters.lateral.integral.multiplier = lad;
    parameters.lateral.derivative.multiplier = lai;

    bird::Bird (bird::Mpu9250(), bird::Gamepad(), bird::Pca8675, parameters).run();
}