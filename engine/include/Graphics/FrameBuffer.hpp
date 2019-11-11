//
//
//

#ifndef AEYON3D_FRAMEBUFFER_HPP
#define AEYON3D_FRAMEBUFFER_HPP

#include <glad/glad.h>
#include "Resource.hpp"
#include "Texture.hpp"

namespace aeyon
{
	class FrameBuffer
	{
	private:
		GLuint m_fbo;

		void attach(const Resource<Texture>& texture, GLenum attachment);

	public:
		FrameBuffer();
		FrameBuffer(FrameBuffer&& other) noexcept;
		FrameBuffer& operator=(FrameBuffer&& other) noexcept;
		~FrameBuffer();

		friend void swap(FrameBuffer& first, FrameBuffer& second) noexcept;

		FrameBuffer copy(/*Rect src, Rect dst*/) const;

		void attachColorTexture(Resource<Texture> texture, std::size_t index);
		void attachDepthTexture(Resource<Texture> texture);
		void attachStencilTexture(Resource<Texture> texture);

		void detachColorTexture(std::size_t index);
		void detachDepthTexture();
		void detachStencilTexture();

		void disableColorBuffers();

		bool isComplete() const;

		void* getNativeHandle();
	};
}

#endif
