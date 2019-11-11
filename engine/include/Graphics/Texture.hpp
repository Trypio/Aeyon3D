//
//
//

#ifndef AEYON3D_TEXTURE_HPP
#define AEYON3D_TEXTURE_HPP

#include <glad/glad.h>
#include <string>
#include <vector>
#include "Color.hpp"
#include "PixelFormat.hpp"


namespace aeyon
{
	class Texture
	{
	public:
		enum class Type : GLenum
		{
			Tex2D = GL_TEXTURE_2D,
			Tex3D = GL_TEXTURE_3D,
			Cube = GL_TEXTURE_CUBE_MAP,
		};

		enum class FilterMode
		{
			Point,
			Bilinear,
			Trilinear
		};

		enum class WrapMode : GLint
		{
			Repeat = GL_REPEAT,
			Clamp = GL_CLAMP_TO_EDGE,
			ClampToBorder = GL_CLAMP_TO_BORDER,
			Mirror = GL_MIRRORED_REPEAT
		};

		enum class CubemapFace
		{
			PositiveX = 0,
			NegativeX,
			PositiveY,
			NegativeY,
			PositiveZ,
			NegativeZ
		};

	private:
		Type m_type;
		PixelFormat m_pixelFormat;
		FilterMode m_filterMode;
		int m_width, m_height, m_depth;
		float m_anisoLevel;
		WrapMode m_wrapU;
		WrapMode m_wrapV;
		WrapMode m_wrapW;
		Color m_borderColor;
		bool m_isReadable;
		GLuint m_glHandle;

		std::vector<std::vector<unsigned char>> m_pixels;

		void setParameteri(GLenum name, GLint value);
		void setParameterf(GLenum name, GLfloat value);
		void setParameterfv(GLenum name, const GLfloat* values);

		void updateParameters();

	public:
		Texture(Type type, PixelFormat format, int width, int height = 0, int depth = 0);

		Texture(const Texture& other) = delete;
		Texture(Texture&& other) noexcept = delete;
		Texture& operator=(const Texture& rhs) = delete;
		Texture& operator=(Texture&& rhs) noexcept = delete;

		~Texture();

		GLuint getNativeHandle() const;

		void apply(bool releaseMemory = false);

		void setPixelDataRaw(const unsigned char* data, std::size_t face = 0)
		{
			std::size_t len = 0;

			switch(m_type)
			{
				case Texture::Type::Tex2D:
					len = m_width * m_height * m_pixelFormat.getSize();
					break;
				case Texture::Type::Tex3D:
					len = m_width * m_height * m_depth * m_pixelFormat.getSize();
					break;
				case Texture::Type::Cube:
					len = m_width * m_height * m_pixelFormat.getSize();
					break;
			}

			m_pixels[face].assign(data, data + len);
		}

		void setFilterMode(FilterMode filterMode);
		void setAnisoLevel(float anisoLevel);
		void setWrapMode(WrapMode wrapMode);
		void setWrapModeU(WrapMode wrapMode);
		void setWrapModeV(WrapMode wrapMode);
		void setWrapModeW(WrapMode wrapMode);
		void setBorderColor(const Color& color);
		void setReadable(bool isReadable);

		Type getType() const;
		PixelFormat getPixelFormat() const;
		FilterMode getFilterMode() const;
		int getWidth() const;
		int getHeight() const;
		int getDepth() const;
		float getAnisoLevel() const;
		WrapMode getWrapModeU() const;
		WrapMode getWrapModeV() const;
		WrapMode getWrapModeW() const;
		Color getBorderColor() const;
		bool isReadable() const;
	};
}


#endif //AEYON3D_TEXTURE_HPP
