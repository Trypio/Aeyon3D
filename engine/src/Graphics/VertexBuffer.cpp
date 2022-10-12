#include "Graphics/VertexBuffer.hpp"

namespace aeyon
{
    std::size_t VertexBuffer::sizeOfVertexType(VertexType type) const
    {
        switch (type)
        {
            case VertexType::Float:
                return sizeof(GLfloat);
            case VertexType::Int:
                return sizeof(GLint);
        }
    }

    VertexBuffer::VertexBuffer(std::vector<VertexAttribute> attributes)
            : m_attributes(std::move(attributes)), m_bufferUsageType(BufferUsage::Static),
            m_size(0), m_vao(0), m_vbo(0)
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        setVertexAttributes(attributes);
    }

    VertexBuffer::VertexBuffer(const aeyon::VertexBuffer& other)
            : m_attributes(other.m_attributes), m_bufferUsageType(other.m_bufferUsageType),
            m_size(other.m_size), m_vao(0), m_vbo(0)
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        if (m_size != 0)
        {
            GLint savedCRB;
            glGetIntegerv(GL_COPY_READ_BUFFER, &savedCRB);
            glBindBuffer(GL_COPY_READ_BUFFER, other.m_vbo);

            GLint savedCWB;
            glGetIntegerv(GL_COPY_WRITE_BUFFER, &savedCWB);
            glBindBuffer(GL_COPY_WRITE_BUFFER, m_vbo);

            glBufferData(GL_COPY_WRITE_BUFFER, m_size, nullptr, static_cast<GLenum>(m_bufferUsageType));
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_size);

            glBindBuffer(GL_COPY_WRITE_BUFFER, savedCWB);
            glBindBuffer(GL_COPY_READ_BUFFER, savedCRB);

            setVertexAttributes(m_attributes);
        }
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer other)
    {
        swap(*this, other);

        return *this;
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
        : m_attributes(std::move(other.m_attributes)), m_bufferUsageType(other.m_bufferUsageType),
        m_vao(other.m_vao), m_vbo(other.m_vbo), m_size(other.m_size)
    {
        other.m_vao = 0;
        other.m_vbo = 0;
        other.m_size = 0;
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }

    void swap(VertexBuffer& first, VertexBuffer& second) noexcept
    {
        using std::swap;

        swap(first.m_vao, second.m_vao);
        swap(first.m_vbo, second.m_vbo);
        swap(first.m_size, second.m_size);
        swap(first.m_bufferUsageType, second.m_bufferUsageType);
        swap(first.m_attributes, second.m_attributes);
    }

    void VertexBuffer::setVertexAttributes(std::vector<VertexAttribute> attributes)
    {
        m_attributes = std::move(attributes);

        GLint savedVAO;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &savedVAO);
        glBindVertexArray(m_vao);

        GLint savedVBO;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &savedVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        std::size_t stride = 0;
        std::size_t offset = 0;

        for (const auto& attr: m_attributes)
        {
            stride += sizeOfVertexType(attr.type) * attr.count;
        }

        for (std::size_t i = 0; i < m_attributes.size(); i++)
        {
            const auto& attr = m_attributes[i];
            glVertexAttribPointer(i,
                                  attr.count,
                                  static_cast<GLenum>(attr.type),
                                  static_cast<GLboolean>(attr.normalized),
                                  stride,
                                  reinterpret_cast<void*>(offset));
            glEnableVertexAttribArray(i);
            offset += sizeOfVertexType(attr.type) * attr.count;
        }

        glBindBuffer(GL_ARRAY_BUFFER, savedVBO);
        glBindVertexArray(savedVAO);
    }

    void VertexBuffer::reset(std::size_t size, BufferUsage usage)
    {
        m_size = size;
        m_bufferUsageType = usage;

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, static_cast<GLenum>(usage));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::write(void* data, std::size_t size, std::size_t offset)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    std::size_t VertexBuffer::getSize() const
    {
        return m_size;
    }

    VertexBuffer::BufferUsage VertexBuffer::getBufferUsageType() const
    {
        return m_bufferUsageType;
    }

    std::any VertexBuffer::getNativeHandle()
    {
        return m_vao;
    }
}
