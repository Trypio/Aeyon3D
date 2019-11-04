//
//
//

#ifndef AEYON3D_VERTEXBUFFER_HPP
#define AEYON3D_VERTEXBUFFER_HPP

#include "glad/glad.h"
#include <vector>
#include "Types.hpp"

namespace aeyon
{
	class VertexBuffer
	{
	private:
		BufferUsage m_bufferUsageType;
		std::size_t m_size;

		GLuint m_vao;
		GLuint m_vbo;

		std::size_t sizeOfVertexType(VertexType type) const
		{
			switch (type)
			{
				case VertexType::Float: return sizeof(GLfloat);
				case VertexType::Int: return sizeof(GLint);
				default: return 0;
			}
		}

	public:
		explicit VertexBuffer(const std::vector<VertexAttribute>& attributes)
				: m_bufferUsageType(BufferUsage::Static), m_size(0), m_vao(0), m_vbo(0)
		{
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo);

			setVertexAttributes(attributes);
		}

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		
		VertexBuffer(VertexBuffer&& other) noexcept 
		: m_bufferUsageType(other.m_bufferUsageType), m_size(other.m_size), m_vao(other.m_vao), m_vbo(other.m_vbo)
		{
			other.m_size = 0;
			other.m_vao = 0;
			other.m_vbo = 0;
		}
		
		VertexBuffer& operator=(VertexBuffer&& other) noexcept
		{
			m_bufferUsageType = other.m_bufferUsageType;
			m_size = other.m_size;
			m_vao = other.m_vao;
			m_vbo = other.m_vbo;

			other.m_size = 0;
			other.m_vao = 0;
			other.m_vbo = 0;

			return *this;
		}
		
		~VertexBuffer()
		{
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(1, &m_vbo);
		}

		void reset(std::size_t size, BufferUsage usage = BufferUsage::Static)
		{
			m_size = size;
			m_bufferUsageType = usage;

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, static_cast<GLenum>(usage));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
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
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void setVertexAttributes(const std::vector<VertexAttribute>& attributes)
		{
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			std::size_t stride = 0;
			std::size_t offset = 0;

			for (const auto& attr : attributes)
			{
				stride += sizeOfVertexType(attr.type) * attr.count;
			}

			for (std::size_t i = 0; i < attributes.size(); i++)
			{
				const auto& attr = attributes[i];
				glVertexAttribPointer(i,
															attr.count,
															static_cast<GLenum>(attr.type),
															static_cast<GLboolean>(attr.normalized),
															stride,
															reinterpret_cast<void*>(offset));
				glEnableVertexAttribArray(i);
				offset += sizeOfVertexType(attr.type) * attr.count;
			}

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void* getNativeHandle()
		{
			return &m_vao;
		}
	};
}

#endif //AEYON3D_VERTEXBUFFER_HPP
