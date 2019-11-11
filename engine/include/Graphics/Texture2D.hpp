//
// Created by thors on 06.11.2019.
//

#ifndef AEYON3D_TEXTURE2D_HPP
#define AEYON3D_TEXTURE2D_HPP

#include "Types.hpp"
#include "Color.hpp"
#include "PixelFormat.hpp"
#include <vector>

namespace aeyon
{
	class Texture2D
	{
//	private:
//		PixelFormat m_pixelFormat;
//		FilterMode m_filterMode;
//		int m_width, m_height;
//		float m_anisoLevel;
//		WrapMode m_wrapU;
//		WrapMode m_wrapV;
//		Color m_borderColor;
//		bool m_isReadable;
//		GLuint m_glHandle;
//
//		std::vector<unsigned char> m_pixels;
//
//		void setParameteri(GLenum name, GLint value);
//		void setParameterf(GLenum name, GLfloat value);
//		void setParameterfv(GLenum name, const GLfloat* values);
//
//		void updateParameters();
//
//	public:
//		Texture2D(PixelFormat format, int width, int height);
//		Texture2D(const Texture2D& other);
//		Texture2D(Texture2D&& other) noexcept;
//		Texture2D& operator=(Texture2D rhs);
//		~Texture2D();
//
//		friend void swap(Texture2D& first, Texture2D& second) noexcept;
//
//		GLuint getNativeHandle();
//
//		void apply(bool releaseMemory = false);
//
//		void setPixelDataRaw(const unsigned char* data)
//		{
//			m_pixels.assign(data, data + m_width * m_height * m_pixelFormat.getSize());
//		}
//
//		void setFilterMode(FilterMode filterMode);
//		void setAnisoLevel(float anisoLevel);
//		void setWrapMode(WrapMode wrapMode);
//		void setWrapModeU(WrapMode wrapMode);
//		void setWrapModeV(WrapMode wrapMode);
//		void setWrapModeW(WrapMode wrapMode);
//		void setBorderColor(const Color& color);
//		void setReadable(bool isReadable);
//
//		Type getType() const;
//		PixelFormat getPixelFormat() const;
//		FilterMode getFilterMode() const;
//		int getWidth() const;
//		int getHeight() const;
//		int getDepth() const;
//		float getAnisoLevel() const;
//		WrapMode getWrapModeU() const;
//		WrapMode getWrapModeV() const;
//		WrapMode getWrapModeW() const;
//		Color getBorderColor() const;
//		bool isReadable() const;
	};
}

#endif //AEYON3D_TEXTURE2D_HPP
