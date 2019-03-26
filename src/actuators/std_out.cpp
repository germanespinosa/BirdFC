#include "std_out.h"

namespace bird
{

	Std_Out::Std_Out(Actuator_Set actuator_set, double refresh_rate)
		: Actuator(actuator_set)
		, refresh_rate_(refresh_rate)
	{
		timer_.restart();
	}

	Std_Out::Std_Out(double refresh_rate)
		: Actuator(Actuator_Set::plus())
		, refresh_rate_(refresh_rate)
	{
		timer_.restart();
	}

	bool Std_Out::update()
	{
		static int counter=0;
		if (timer_.time_out(refresh_rate_))
		{
			timer_.restart();
			
			std::cout << counter++ << " : ";
			for (Propeller p : actuator_set_.propellers)
			{
				std::cout << p * 180 / PI << "\t";
			}
			std::cout << "\n";
		}
		return true;
	}
}