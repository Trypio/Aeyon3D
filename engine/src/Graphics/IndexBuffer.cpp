#include "Graphics/IndexBuffer.hpp"

namespace aeyon
{
    IndexBuffer::IndexBuffer() : m_bufferUsageType(BufferUsage::Static), m_size(0), m_ebo(0)
    {
        glGenBuffers(1, &m_ebo);
    }

    IndexBuffer::IndexBuffer(const IndexBuffer& other)
            : m_bufferUsageType(other.m_bufferUsageType), m_size(other.m_size), m_ebo(0)
    {
        glGenBuffers(1, &m_ebo);

        if (m_size != 0)
        {
            GLint savedCRB;
            glGetIntegerv(GL_COPY_READ_BUFFER, &savedCRB);
            glBindBuffer(GL_COPY_READ_BUFFER, other.m_ebo);

            GLint savedCWB;
            glGetIntegerv(GL_COPY_WRITE_BUFFER, &savedCWB);
            glBindBuffer(GL_COPY_WRITE_BUFFER, m_ebo);

            glBufferData(GL_COPY_WRITE_BUFFER, m_size, nullptr, static_cast<GLenum>(m_bufferUsageType));
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_size);

            glBindBuffer(GL_COPY_WRITE_BUFFER, savedCWB);
            glBindBuffer(GL_COPY_READ_BUFFER, savedCRB);
        }
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer other)
    {
        swap(*this, other);

        return *this;
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
        : m_ebo(other.m_ebo), m_size(other.m_size), m_bufferUsageType(other.m_bufferUsageType)
    {
        other.m_ebo = 0;
        other.m_size = 0;
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_ebo);
    }

    void swap(IndexBuffer& first, IndexBuffer& second) noexcept
    {
        using std::swap;

        swap(first.m_bufferUsageType, second.m_bufferUsageType);
        swap(first.m_size, second.m_size);
        swap(first.m_ebo, second.m_ebo);
    }

    void IndexBuffer::reset(std::size_t size, IndexBuffer::BufferUsage usage)
    {
        m_size = size;
        m_bufferUsageType = usage;

        GLint saved;
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &saved);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, static_cast<GLenum>(usage));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, saved);
    }

    std::size_t IndexBuffer::getSize() const
    {
        return m_size;
    }

    IndexBuffer::BufferUsage IndexBuffer::getBufferUsageType() const
    {
        return m_bufferUsageType;
    }

    void IndexBuffer::write(void* data, std::size_t size, std::size_t offset)
    {
        GLint saved;
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &saved);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, saved);
    }

    std::any IndexBuffer::getNativeHandle()
    {
        return m_ebo;
    }
}
