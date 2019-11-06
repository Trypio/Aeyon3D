//
//
//
#ifndef AEYON3D_INDEXBUFFER_HPP
#define AEYON3D_INDEXBUFFER_HPP

#include "glad/glad.h"
#include "Types.hpp"

namespace aeyon
{
	class IndexBuffer
	{
		enum class BufferUsage : GLenum
		{
			Static = GL_STATIC_DRAW,
			Dynamic = GL_DYNAMIC_DRAW
		};

	private:
		BufferUsage m_bufferUsageType;
		std::size_t m_size;

		GLuint m_ebo;

	public:
		IndexBuffer();
		IndexBuffer(const IndexBuffer& other);
		IndexBuffer& operator=(IndexBuffer other);
		IndexBuffer(IndexBuffer&& other) noexcept;
		~IndexBuffer();

		friend void swap(IndexBuffer& first, IndexBuffer& second) noexcept;

		void reset(std::size_t size, BufferUsage usage = BufferUsage::Static);
    void write(void* data, std::size_t size, std::size_t offset);

		std::size_t getSize() const;
		BufferUsage getBufferUsageType() const;

		void* getNativeHandle();
	};
}

#endif //AEYON3D_INDEXBUFFER_HPP
