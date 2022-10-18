#ifndef AEYON3D_VERTEXATTRIBUTE_HPP
#define AEYON3D_VERTEXATTRIBUTE_HPP

#include <glad/glad.h>
#include <vector>

namespace aeyon
{
    enum class VertexType : GLenum
    {
        Float = GL_FLOAT,
        Int = GL_INT
    };

    enum class VertexFormat
    {
        P1,
        P1N1,
        P1N1UV1,
        P1N1UV1T1B1
    };

    struct VertexAttribute
    {
        VertexType type;
        std::size_t count;
        bool normalized;

        static std::vector<VertexAttribute> fromVertexFormat(VertexFormat format)
        {
            if (format == VertexFormat::P1)
            {
                return {
                        { VertexType::Float, 3, false }
                };
            }
            else if (format == VertexFormat::P1N1)
            {
                return {
                        { VertexType::Float, 3, false },
                        { VertexType::Float, 3, false }
                };
            }
            else if (format == VertexFormat::P1N1UV1)
            {
                return {
                        { VertexType::Float, 3, false },
                        { VertexType::Float, 3, false },
                        { VertexType::Float, 2, false }
                };
            }
            else if (format == VertexFormat::P1N1UV1T1B1)
            {
                return {
                        { VertexType::Float, 3, false },
                        { VertexType::Float, 3, false },
                        { VertexType::Float, 2, false },
                        { VertexType::Float, 3, false },
                        { VertexType::Float, 3, false }
                };
            }
            else
            {
                return {};
            }
        }
    };
}

#endif //AEYON3D_VERTEXATTRIBUTE_HPP
