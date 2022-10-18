#ifndef AEYON3D_PIXELFORMAT_HPP
#define AEYON3D_PIXELFORMAT_HPP

#include <string>
#include <glad/glad.h>

namespace aeyon
{
    /**
     * Closely describes the pixel format of an image or texture.
     */
    class PixelFormat
    {
    private:
        std::string m_name;
        std::size_t m_numChannels;
        std::size_t m_channelSize;
        std::size_t m_size;
        GLint m_glInternalFormat;
        GLenum m_glFormat;
        GLenum m_glType;

    public:
        PixelFormat(std::string name, std::size_t numChannels, std::size_t channelSize,
                    GLint internalFormat, GLenum format, GLenum type)
                : m_name(std::move(name)), m_numChannels(numChannels), m_channelSize(channelSize),
                  m_glInternalFormat(internalFormat), m_glFormat(format), m_glType(type),
                  m_size(numChannels * channelSize)
        {
        }

        const std::string& getName() const
        {
            return m_name;
        }

        std::size_t getNumChannels() const
        {
            return m_numChannels;
        }

        std::size_t getChannelSize() const
        {
            return m_channelSize;
        }

        std::size_t getSize() const
        {
            return m_size;
        }

        GLint getGLInternalFormat() const
        {
            return m_glInternalFormat;
        }

        GLenum getGLFormat() const
        {
            return m_glFormat;
        }

        GLenum getGLType() const
        {
            return m_glType;
        }

        // Integer formats
        static const PixelFormat R8;
        static const PixelFormat R16;
        static const PixelFormat RGB8;
        static const PixelFormat sRGB8;
        static const PixelFormat RGBA8;
        static const PixelFormat sRGBA8;

        // Floating point formats
        static const PixelFormat R32F;
        static const PixelFormat RGB32F;
        static const PixelFormat RGBA32F;

        // Special formats
        static const PixelFormat Depth;
        static const PixelFormat DepthStencil;
    };
}

#endif //AEYON3D_PIXELFORMAT_HPP
