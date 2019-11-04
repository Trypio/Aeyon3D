//
//
//

#ifndef AEYON3D_TIME_HPP
#define AEYON3D_TIME_HPP

#include <chrono>

namespace aeyon
{
	class Time
	{
	private:
		using clock = std::chrono::high_resolution_clock;

		static clock::time_point m_now;
		static clock::time_point m_last;
		static float m_deltaTime;

	public:
		static void update();
		static float getDeltaTime();
	};
}


#endif //AEYON3D_TIME_HPP
