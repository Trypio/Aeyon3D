//
//
//

#include "Graphics/IndexBuffer.hpp"

namespace aeyon
{
  IndexBuffer::IndexBuffer() : m_bufferUsageType(BufferUsage::Static), m_size(0)
  {
    glGenBuffers(1, &m_ebo);
  }

  IndexBuffer::IndexBuffer(const IndexBuffer& other)
  : m_bufferUsageType(other.m_bufferUsageType), m_size(other.m_size)
  {
    glGenBuffers(1, &m_ebo);

    if (m_size != 0)
    {
      glBindBuffer(GL_COPY_READ_BUFFER, other.m_ebo);
      glBindBuffer(GL_COPY_WRITE_BUFFER, m_ebo);

      glBufferData(GL_COPY_WRITE_BUFFER, m_size, nullptr, static_cast<GLenum>(m_bufferUsageType));
      glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_size);

      glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
      glBindBuffer(GL_COPY_READ_BUFFER, 0);
    }
  }

  IndexBuffer& IndexBuffer::operator=(IndexBuffer other)
  {
    swap(*this, other);

    return *this;
  }

  IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
      : IndexBuffer()
  {
    swap(*this, other);
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

    GLuint prev;
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, reinterpret_cast<GLint*>(&prev));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, static_cast<GLenum>(usage));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prev);
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
		GLuint prev;
		glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, reinterpret_cast<GLint*>(&prev));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prev);
  }

  void* IndexBuffer::getNativeHandle()
  {
    return &m_ebo;
  }
}
