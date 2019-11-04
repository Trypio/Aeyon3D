//
//
//

#include "Time.hpp"

using ms = std::chrono::duration<float, std::milli>;

namespace aeyon
{
	Time::clock::time_point Time::m_now = Time::clock::now();
	Time::clock::time_point Time::m_last = m_now;
	float Time::m_deltaTime = 0.0f;

	void Time::update()
	{
		m_last = m_now;
		m_now = clock::now();
		m_deltaTime = std::chrono::duration_cast<ms>(m_now - m_last).count();
	}

	float Time::getDeltaTime()
	{
		return m_deltaTime;
	}
}