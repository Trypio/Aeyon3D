//
// Created by thors on 28.07.2019.
//

#ifndef AEYON3D_AUDIOSYSTEM_HPP
#define AEYON3D_AUDIOSYSTEM_HPP

#include "System.hpp"
#include <AL/al.h>
#include "Audio/AudioSource.hpp"
#include "Transform.hpp"

namespace aeyon
{
	class AudioSystem : public System
	{
	private:
		// TODO: Create n buffers and assign them to the playing sounds
		ALuint m_buffer;
		bool m_bufferFilled = false;
		ALCdevice* m_device;
		ALCcontext* m_context;

		void checkError()
		{
			ALCenum error;
			if ((error = alGetError()) != AL_NO_ERROR)
			{
				if (m_buffer)
				  alDeleteBuffers(1, &m_buffer);

				throw std::runtime_error("An OpenAL error occured");
			}
		}

		ALenum toALFormat(int channels, int resolution) const
		{
			bool stereo = (channels > 1);

			switch (resolution)
			{
				case 16:
					if (stereo)
						return AL_FORMAT_STEREO16;
					else
						return AL_FORMAT_MONO16;
				case 8:
					if (stereo)
						return AL_FORMAT_STEREO8;
					else
						return AL_FORMAT_MONO8;
				default:
					return -1;
			}
		}

	public:
		AudioSystem()
		: m_buffer(0), m_device(nullptr), m_context(nullptr)
		{
			alGenBuffers(1, &m_buffer);
			checkError();
		}

		~AudioSystem() override
		{
			if (m_buffer)
				alDeleteBuffers(1, &m_buffer);
		}

		void update() override
		{
			System::update();
			for (auto& entity : getEntities())
			{
				auto transform = entity.getComponent<Transform>();
				auto source = entity.getComponent<AudioSource>();

				const auto& clip = source->getClip();

				if(m_bufferFilled)
				{
					source->setPosition(transform->getPosition());
					break;
				}

				alBufferData(m_buffer, toALFormat(clip->getChannels(), clip->getResolution()), clip->getBuffer().data(), clip->getBuffer().size(), clip->getFrequency());
				checkError();
				alSourcei(*static_cast<ALuint*>(source->getNativeHandle()), AL_BUFFER, m_buffer);
				checkError();
				alSourcePlay(*static_cast<ALuint*>(source->getNativeHandle()));
				checkError();
				m_bufferFilled = true;
			}
		}
	};
}

#endif //AEYON3D_AUDIOSYSTEM_HPP
