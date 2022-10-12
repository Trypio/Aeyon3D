//
//
//

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
				m_pixels(6)
	{
		glGenTextures(1, &m_glHandle);

		if (GLAD_GL_EXT_texture_filter_anisotropic)
		{
			GLfloat largest;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
			setAnisoLevel(largest);
		}
		else
		{
			setAnisoLevel(1.0f);
		}


		GLuint previousBoundTexture = 0;

		if (m_type == Type::Tex2D)
		{
			glGetIntegerv(GL_TEXTURE_BINDING_2D, reinterpret_cast<GLint*>(&previousBoundTexture));
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
			glGetIntegerv(GL_TEXTURE_BINDING_3D, reinterpret_cast<GLint*>(&previousBoundTexture));
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
			glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, reinterpret_cast<GLint*>(&previousBoundTexture));
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

		glBindTexture(static_cast<GLenum>(m_type), previousBoundTexture);
	}

	Texture::~Texture()
	{
		if (m_glHandle)
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

		GLuint previousBoundTexture = 0;

		if (m_type == Type::Tex2D)
		{
			glGetIntegerv(GL_TEXTURE_BINDING_2D, reinterpret_cast<GLint*>(&previousBoundTexture));
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
			glGetIntegerv(GL_TEXTURE_BINDING_3D, reinterpret_cast<GLint*>(&previousBoundTexture));
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
			glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, reinterpret_cast<GLint*>(&previousBoundTexture));
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

		glBindTexture(static_cast<GLenum>(m_type), previousBoundTexture);

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
