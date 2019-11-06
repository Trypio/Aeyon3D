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

		std::size_t sizeOfVertexType(VertexType type) const;

	public:
		explicit VertexBuffer(const std::vector<VertexAttribute>& attributes);
		VertexBuffer(const VertexBuffer& other);
		VertexBuffer& operator=(VertexBuffer other);
		VertexBuffer(VertexBuffer&& other) noexcept;
    ~VertexBuffer();

		friend void swap(VertexBuffer& first, VertexBuffer& second) noexcept;

		void reset(std::size_t size, BufferUsage usage = BufferUsage::Static);
    void write(void* data, std::size_t size, std::size_t offset);

    void setVertexAttributes(const std::vector<VertexAttribute>& attributes);

    std::size_t getSize() const;
		BufferUsage getBufferUsageType() const;

		void* getNativeHandle();
	};
}

#endif //AEYON3D_VERTEXBUFFER_HPP
