//
//
//

#include "Time.hpp"


namespace aeyon
{
	Time::clock::time_point Time::m_start = Time::clock::now();
	Time::clock::time_point Time::m_now = m_start;
	Time::clock::time_point Time::m_last = m_now;

	void Time::update()
	{
		m_last = m_now;
		m_now = clock::now();
	}

	float Time::getDeltaTime()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_now - m_last).count() / 1000.0f;
	}

	float Time::getTime()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_now - m_start).count() / 1000.0f;
	}
}