//
//
//

#ifndef AEYON3D_AUDIOCLIP_HPP
#define AEYON3D_AUDIOCLIP_HPP

#include <vector>

namespace aeyon
{
	class AudioClip
	{
	private:
		int m_numSamples;
		int m_duration;
		int m_channels;
		int m_frequency;
		int m_resolution;
		std::vector<unsigned char> m_data;

	public:
		template <typename T>
		AudioClip(T&& data, int channels, int frequency, int resolution)
		: m_numSamples(static_cast<int>(data.size()) / channels / (resolution / 8)),
		m_duration(static_cast<int>(data.size()) / channels / (resolution / 8) / frequency),
		m_channels(channels), m_frequency(frequency), m_resolution(resolution), m_data(std::forward<T>(data))

		{
		}

		int getChannels() const
		{
			return m_channels;
		}

		int getFrequency() const
		{
			return m_frequency;
		}

		int getResolution() const
		{
			return m_resolution;
		}

		int getNumSamples() const
		{
			return m_numSamples;
		}

		int getDuration() const
		{
			return m_duration;
		}

		const std::vector<unsigned char>& getBuffer() const
		{
			return  m_data;
		}
	};
}

#endif //AEYON3D_AUDIOCLIP_HPP
