#include "Graphics/Texture.hpp"
#include <algorithm>
#include <cstring>
#include <stdexcept>

namespace aeyon
{
	void Texture::setParameteri(GLenum name, GLint value)
	{
		auto type = static_cast<GLenum>(m_type);
		glTexParameteri(type, name, value);
	}

	void Texture::setParameterf(GLenum name, GLfloat value)
	{
		auto type = static_cast<GLenum>(m_type);
		glTexParameterf(type, name, value);
	}

	void Texture::setParameterfv(GLenum name, const GLfloat* values)
	{
		auto type = static_cast<GLenum>(m_type);
		glTexParameterfv(type, name, values);
	}

	Texture::Texture(Type type, PixelFormat format, int width, int height, int depth)
			: m_glHandle(0),
				m_type(type),
				m_pixelFormat(std::move(format)),
				m_width(width), m_height(height), m_depth(depth),
				m_wrapU(WrapMode::Repeat), m_wrapV(WrapMode::Repeat), m_wrapW(WrapMode::Repeat),
				m_filterMode(FilterMode::Trilinear),
				m_borderColor(Color::Black),
				m_pixels(6),
                m_anisoLevel(1.0f),
                m_isReadable(true)
	{
		glGenTextures(1, &m_glHandle);

		if (GLAD_GL_EXT_texture_filter_anisotropic)
		{
			GLfloat largest;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
			setAnisoLevel(largest);
		}

		GLint previouslyBoundTexture = 0;
		if (m_type == Type::Tex2D)
		{
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &previouslyBoundTexture);
			glBindTexture(static_cast<GLenum>(m_type), m_glHandle);

			glTexImage2D(
					GL_TEXTURE_2D,
					0,
					m_pixelFormat.getGLInternalFormat(),
					m_width,
					m_height,
					0,
					m_pixelFormat.getGLFormat(),
					m_pixelFormat.getGLType(),
					nullptr
			);
		}
		else if (m_type == Type::Tex3D)
		{
			glGetIntegerv(GL_TEXTURE_BINDING_3D, &previouslyBoundTexture);
			glBindTexture(static_cast<GLenum>(m_type), m_glHandle);

			glTexImage3D(
					GL_TEXTURE_3D,
					0,
					m_pixelFormat.getGLInternalFormat(),
					m_width,
					m_height,
					m_depth,
					0,
					m_pixelFormat.getGLFormat(),
					m_pixelFormat.getGLType(),
					nullptr
			);
		}
		else if (m_type == Type::Cube)
		{
			glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &previouslyBoundTexture);
			glBindTexture(static_cast<GLenum>(m_type), m_glHandle);

			for (std::size_t face = 0; face < 6; face++)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
										 0,
										 m_pixelFormat.getGLInternalFormat(),
										 m_width,
										 m_height,
										 0,
										 m_pixelFormat.getGLFormat(),
										 m_pixelFormat.getGLType(),
										 nullptr
				);
			}
		}

		glBindTexture(static_cast<GLenum>(m_type), previouslyBoundTexture);
	}

    Texture::Texture(Texture&& other) noexcept
    : m_glHandle(other.m_glHandle),
    m_type(other.m_type),
    m_width(other.m_width), m_height(other.m_height), m_depth(other.m_depth),
    m_filterMode(other.m_filterMode),
    m_anisoLevel(other.m_anisoLevel),
    m_wrapU(other.m_wrapU), m_wrapV(other.m_wrapV), m_wrapW(other.m_wrapW),
    m_isReadable(other.m_isReadable),
    m_borderColor(other.m_borderColor),
      m_pixelFormat(std::move(other.m_pixelFormat)),
      m_pixels(std::move(other.m_pixels))
    {
        other.m_glHandle = 0;
    }

    Texture& Texture::operator=(Texture&& other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    void swap(Texture& first, Texture& second) noexcept
    {
        using std::swap;

        swap(first.m_glHandle, second.m_glHandle);
        swap(first.m_type, second.m_type);
        swap(first.m_width, second.m_width);
        swap(first.m_height, second.m_height);
        swap(first.m_depth, second.m_depth);
        swap(first.m_filterMode, second.m_filterMode);
        swap(first.m_anisoLevel, second.m_anisoLevel);
        swap(first.m_wrapU, second.m_wrapU);
        swap(first.m_wrapV, second.m_wrapV);
        swap(first.m_wrapW, second.m_wrapW);
        swap(first.m_isReadable, second.m_isReadable);
        swap(first.m_borderColor, second.m_borderColor);
        swap(first.m_pixelFormat, second.m_pixelFormat);
        swap(first.m_pixels, second.m_pixels);
    }

	Texture::~Texture()
	{
        glDeleteTextures(1, &m_glHandle);
	}

	std::any Texture::getNativeHandle()
	{
		return m_glHandle;
	}

	void Texture::apply(bool releaseMemory)
	{
		if (m_pixelFormat.getSize() == 0 && !m_pixels[0].empty())
		{
			throw std::runtime_error("Pixel format is not writable");
		}

		GLint previouslyBoundTexture = 0;
		if (m_type == Type::Tex2D)
		{
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &previouslyBoundTexture);
			glBindTexture(GL_TEXTURE_2D, m_glHandle);

			glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					0,
					0,
					m_pixels[0].empty() ?  0 : m_width,
					m_pixels[0].empty() ?  0 : m_height,
					m_pixelFormat.getGLFormat(),
					m_pixelFormat.getGLType(),
					m_pixels[0].empty() ? nullptr : m_pixels[0].data()
					);

			if (m_filterMode == FilterMode::Trilinear)
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}
		}
		else if (m_type == Type::Tex3D)
		{
			glGetIntegerv(GL_TEXTURE_BINDING_3D, &previouslyBoundTexture);
			glBindTexture(GL_TEXTURE_3D, m_glHandle);

			glTexSubImage3D(
					GL_TEXTURE_3D,
					0,
					0,
					0,
					0,
					m_pixels[0].empty() ?  0 : m_width,
					m_pixels[0].empty() ?  0 : m_height,
					m_pixels[0].empty() ?  0 : m_depth,
					m_pixelFormat.getGLFormat(),
					m_pixelFormat.getGLType(),
					m_pixels[0].empty() ? nullptr : m_pixels[0].data()
					);
		}
		else if (m_type == Type::Cube)
		{
			glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &previouslyBoundTexture);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_glHandle);

			for (std::size_t face = 0; face < 6; face++)
			{
				glTexSubImage2D(
						GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
						0,
						0,
						0,
						m_pixels[face].empty() ?  0 : m_width,
						m_pixels[face].empty() ?  0 : m_height,
						m_pixelFormat.getGLFormat(),
						m_pixelFormat.getGLType(),
						m_pixels[face].empty() ? nullptr : m_pixels[face].data()
						);
			}
		}

		updateParameters();

		glBindTexture(static_cast<GLenum>(m_type), previouslyBoundTexture);

		if (releaseMemory)
		{
			setReadable(false);
			for (auto& f : m_pixels)
			{
				std::vector<unsigned char>().swap(f);
			}
		}
	}

	void Texture::updateParameters()
	{
		switch (m_filterMode)
		{
			case FilterMode::Point:
				setParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				setParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				break;

			case FilterMode::Bilinear:
				setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				break;

			case FilterMode::Trilinear:
				setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				break;
		}

		if (GLAD_GL_EXT_texture_filter_anisotropic)
		{
			setParameterf(GL_TEXTURE_MAX_ANISOTROPY_EXT, m_anisoLevel);
		}

		setParameteri(GL_TEXTURE_WRAP_S, static_cast<GLint>(m_wrapU));
		setParameteri(GL_TEXTURE_WRAP_T, static_cast<GLint>(m_wrapV));
		setParameteri(GL_TEXTURE_WRAP_R, static_cast<GLint>(m_wrapW));

		GLfloat border[] = { m_borderColor.r, m_borderColor.g, m_borderColor.b, 1.0f };

		setParameterfv(GL_TEXTURE_BORDER_COLOR, border);
	}


	void Texture::setFilterMode(Texture::FilterMode filterMode)
	{
		m_filterMode = filterMode;
	}

	void Texture::setAnisoLevel(float anisoLevel)
	{
		m_anisoLevel = anisoLevel;
	}


	void Texture::setWrapMode(WrapMode wrapMode)
	{
		setWrapModeU(wrapMode);
		setWrapModeV(wrapMode);
		setWrapModeW(wrapMode);
	}

	void Texture::setWrapModeU(Texture::WrapMode wrapMode)
	{
		m_wrapU = wrapMode;
	}

	void Texture::setWrapModeV(Texture::WrapMode wrapMode)
	{
		m_wrapV = wrapMode;
	}

	void Texture::setWrapModeW(Texture::WrapMode wrapMode)
	{
		m_wrapW = wrapMode;
	}

	void Texture::setBorderColor(const Color& color)
	{
		m_borderColor = color;
	}

	void Texture::setReadable(bool isReadable)
	{
		m_isReadable = isReadable;
	}

	Texture::Type Texture::getType() const
	{
		return m_type;
	}

	PixelFormat Texture::getPixelFormat() const
	{
		return m_pixelFormat;
	}

	Texture::FilterMode Texture::getFilterMode() const
	{
		return m_filterMode;
	}

	int Texture::getWidth() const
	{
		return m_width;
	}

	int Texture::getHeight() const
	{
		return m_height;
	}

	int Texture::getDepth() const
	{
		return m_depth;
	}

	float Texture::getAnisoLevel() const
	{
		return m_anisoLevel;
	}


	Texture::WrapMode Texture::getWrapModeU() const
	{
		return m_wrapU;
	}

	Texture::WrapMode Texture::getWrapModeV() const
	{
		return m_wrapV;
	}

	Texture::WrapMode Texture::getWrapModeW() const
	{
		return m_wrapW;
	}

	Color Texture::getBorderColor() const
	{
		return m_borderColor;
	}

	bool Texture::isReadable() const
	{
		return m_isReadable;
	}
}
