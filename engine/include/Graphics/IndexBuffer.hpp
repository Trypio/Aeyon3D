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
		IndexBuffer()
				: m_bufferUsageType(BufferUsage::Static), m_size(0), m_ebo(0)
		{
			glGenBuffers(1, &m_ebo);
		}

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		IndexBuffer(IndexBuffer&& other) noexcept
				: m_bufferUsageType(other.m_bufferUsageType), m_size(other.m_size), m_ebo(other.m_ebo)
		{
			other.m_size = 0;
			other.m_ebo = 0;
		}

		IndexBuffer& operator=(IndexBuffer&& other) noexcept
		{
			m_bufferUsageType = other.m_bufferUsageType;
			m_size = other.m_size;
			m_ebo = other.m_ebo;

			other.m_size = 0;
			other.m_ebo = 0;

			return *this;
		}

		~IndexBuffer()
		{
			glDeleteBuffers(1, &m_ebo);
		}

		void reset(std::size_t size, BufferUsage usage = BufferUsage::Static)
		{
			m_size = size;
			m_bufferUsageType = usage;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, static_cast<GLenum>(usage));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		std::size_t getSize() const
		{
			return m_size;
		}

		BufferUsage getBufferUsageType() const
		{
			return m_bufferUsageType;
		}

		void write(std::size_t offset, std::size_t size, void* data)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void* getNativeHandle()
		{
			return &m_ebo;
		}
	};
}

#endif //AEYON3D_INDEXBUFFER_HPP
