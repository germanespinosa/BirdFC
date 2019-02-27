#include<time.h>
#include<algorithm>

struct Pid_Term 
{
public:
    double multiplier;
    double min;
    double max;
    double value;
};

struct Pid_Target
{
public:
    double value;
    double change_speed;
};
struct Pid_Set
{
public:
    Pid_Term proportional_term;
    Pid_Term derivative_term;
    Pid_Term integral_term;
    double value_error;
    double change_speed_error;
    double value;
    double change_speed;
};

struct Pid_Controller
{
public:
    Pid_Controller()
    {
    }
    Pid_Set &process(Pid_Set &request, Pid_Target target)
    {
        Pid_Set &response = request;
        response.value_error = target.value - request.value;
        response.change_speed_error = target.change_speed - request.change_speed;
        double proportional = response.value_error * request.proportional_term.multiplier;
        response.proportional_term.value = std::min(std::max(proportional,request.proportional_term.max),request.proportional_term.min);
        double derivative = response.change_speed_error * request.derivative_term.multiplier;
        response.derivative_term.value = std::min(std::max(derivative,request.derivative_term.max),request.derivative_term.min);
        double integral = response.value_error * request.integral_term.multiplier;
        response.integral_term.value += std::min(std::max(integral,request.integral_term.max),request.integral_term.min);
        response.value = response.proportional_term.value - response.derivative_term.value + response.integral_term.value;
        return response;
    }
};