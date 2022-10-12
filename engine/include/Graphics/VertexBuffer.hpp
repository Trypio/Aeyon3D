#ifndef AEYON3D_VERTEXBUFFER_HPP
#define AEYON3D_VERTEXBUFFER_HPP

#include <glad/glad.h>
#include <vector>
#include <any>

namespace aeyon
{
    class VertexBuffer
    {
        enum class BufferUsage : GLenum
        {
            Static = GL_STATIC_DRAW,
            Dynamic = GL_DYNAMIC_DRAW
        };

        enum class VertexType : GLenum
        {
            Float = GL_FLOAT,
            Int = GL_INT
        };

        struct VertexAttribute
        {
            VertexType type;
            std::size_t count;
            bool normalized;
        };

    private:
        BufferUsage m_bufferUsageType;
        std::size_t m_size;
        std::vector<VertexAttribute> m_attributes;

        GLuint m_vao;
        GLuint m_vbo;

        std::size_t sizeOfVertexType(VertexType type) const;

    public:
        explicit VertexBuffer(std::vector<VertexAttribute> attributes);
        VertexBuffer(const VertexBuffer& other);
        VertexBuffer& operator=(VertexBuffer other);
        VertexBuffer(VertexBuffer&& other) noexcept;
        ~VertexBuffer();

        friend void swap(VertexBuffer& first, VertexBuffer& second) noexcept;

        void reset(std::size_t size, BufferUsage usage = BufferUsage::Static);
        void write(void* data, std::size_t size, std::size_t offset);

        void setVertexAttributes(std::vector<VertexAttribute> attributes);

        std::size_t getSize() const;
        BufferUsage getBufferUsageType() const;

        std::any getNativeHandle();
    };
}

#endif //AEYON3D_VERTEXBUFFER_HPP
