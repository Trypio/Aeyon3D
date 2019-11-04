//
// Created by thors on 29.07.2019.
//

#ifndef AEYON3D_AUDIOSOURCE_HPP
#define AEYON3D_AUDIOSOURCE_HPP

#include "ECS/Component.hpp"
#include "Resource.hpp"
#include "AudioClip.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <glm/glm.hpp>

namespace aeyon
{
	class AudioSource : public Component<AudioSource>
	{
	private:
		Resource<AudioClip> m_clip;
		bool m_isLoop;
		float m_volume;
		glm::vec3 m_position;
		glm::vec3 m_velocity;
		bool m_isPlaying;

		ALuint m_source;

		void checkError()
		{
			ALCenum error;
			if((error = alGetError()) != AL_NO_ERROR)
			{
				if (m_source)
					alDeleteSources(1, &m_source);

				throw std::runtime_error("An OpenAL error occured");
			}
		}

	public:
		AudioSource()
		: m_source(0), m_isLoop(false), m_volume(1.0f), m_position(0.0f), m_velocity(0.0f),
		  m_isPlaying(false)
		{

			alGetError();

			alGenSources(1, &m_source);
			checkError();

			alSourcef(m_source, AL_PITCH, 1.0f);
			checkError();
			alSourcef(m_source, AL_GAIN, 1.0f);
			checkError();
			alSource3f(m_source, AL_POSITION, m_position.x, m_position.y, m_position.z);
			checkError();
			alSource3f(m_source, AL_VELOCITY, m_velocity.x, m_velocity.y, m_velocity.z);
			checkError();
			alSourcei(m_source, AL_LOOPING, m_isLoop ? AL_TRUE : AL_FALSE);
			checkError();
		}

		AudioSource(const AudioSource&) = delete;
		AudioSource& operator=(const AudioSource&) = delete;


		~AudioSource() override
		{
			if (m_source)
				alDeleteSources(1, &m_source);
		}

		void setPosition(const glm::vec3& pos)
		{
			alSource3f(m_source, AL_POSITION, pos.x, pos.y, pos.z);
			checkError();
			m_position = pos;
		}

		const glm::vec3& getPosition() const
		{
			return m_position;
		}

		const glm::vec3& getVelocity() const
		{
			return m_velocity;
		}

		void setVelocity(const glm::vec3& vel)
		{
			alSource3f(m_source, AL_VELOCITY, vel.x, vel.y, vel.z);
			checkError();
			m_velocity = vel;
		}

		void setClip(Resource<AudioClip> clip)
		{
			m_clip = std::move(clip);
		}

		const Resource<AudioClip>& getClip() const
		{
			return m_clip;
		}

		void* getNativeHandle()
		{
			return &m_source;
		}

		void play()
		{
			m_isPlaying = true;
		}

		bool isPlaying() const
		{
			return m_isPlaying;
		}

		void stop()
		{
			m_isPlaying = false;
		}
	};
}

#endif //AEYON3D_AUDIOSOURCE_HPP
