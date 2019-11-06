//
//
//

#include "Graphics/VertexBuffer.hpp"

namespace aeyon
{
  std::size_t VertexBuffer::sizeOfVertexType(VertexType type) const
  {
    switch (type)
    {
      case VertexType::Float: return sizeof(GLfloat);
      case VertexType::Int: return sizeof(GLint);
      default: return 0;
    }
  }

  VertexBuffer::VertexBuffer(const std::vector<VertexAttribute>& attributes)
      : m_bufferUsageType(BufferUsage::Static), m_size(0), m_vao(0), m_vbo(0)
  {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    setVertexAttributes(attributes);
  }

  VertexBuffer::VertexBuffer(const aeyon::VertexBuffer& other)
  : m_bufferUsageType(other.m_bufferUsageType), m_size(other.m_size)
  {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    // TODO...
  }

  VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
      : m_bufferUsageType(other.m_bufferUsageType), m_size(other.m_size), m_vao(other.m_vao), m_vbo(other.m_vbo)
  {
    other.m_size = 0;
    other.m_vao = 0;
    other.m_vbo = 0;
  }

  VertexBuffer::~VertexBuffer()
  {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
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

  void VertexBuffer::setVertexAttributes(const std::vector<VertexAttribute>& attributes)
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

  std::size_t VertexBuffer::getSize() const
  {
    return m_size;
  }

  BufferUsage VertexBuffer::getBufferUsageType() const
  {
    return m_bufferUsageType;
  }

  void* VertexBuffer::getNativeHandle()
  {
    return &m_vao;
  }
}
