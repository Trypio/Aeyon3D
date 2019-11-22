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
		using clock = std::chrono::steady_clock;

		static clock::time_point m_start;
		static clock::time_point m_now;
		static clock::time_point m_last;

	public:
		/**
		 * Updates the internal timer state. Should be called exactly once at the beginning of each frame.
		 */
		static void update();

		/**
		 * Get elapsed time (in seconds) between the current and the last frame
		 */
		static float getDeltaTime();

		/**
		 * Get elapsed time (in seconds) since the start of the game
		 */
		static float getTime();
	};
}


#endif //AEYON3D_TIME_HPP
