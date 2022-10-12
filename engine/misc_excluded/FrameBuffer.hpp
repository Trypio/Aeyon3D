//#ifndef AEYON3D_FRAMEBUFFER_HPP
//#define AEYON3D_FRAMEBUFFER_HPP
//
//#include <glad/glad.h>
//#include "Resource.hpp"
//#include "Texture.hpp"
//#include <variant>
//
//namespace aeyon
//{
//    /**
//     * Wrapper class for a generic* frame buffer object.
//     *
//     * *just the public interface yet due to convenience
//     */
//	class FrameBuffer
//	{
//	private:
//		GLuint m_fbo;
//
//		void attach(GLenum attachment, const Resource <Texture>& texture);
//
//	public:
//        using NativeHandle = std::variant<GLuint>;
//
//		FrameBuffer();
//		FrameBuffer(FrameBuffer&& other) noexcept;
//		FrameBuffer& operator=(FrameBuffer&& other) noexcept;
//		~FrameBuffer();
//
//		friend void swap(FrameBuffer& first, FrameBuffer& second) noexcept;
//
//		FrameBuffer copy(/*Rect src, Rect dst*/) const;
//
//		void attachColorTexture(Resource<Texture> texture, std::size_t index);
//		void attachDepthTexture(Resource<Texture> texture);
//		void attachStencilTexture(Resource<Texture> texture);
//
//		void detachColorTexture(std::size_t index);
//		void detachDepthTexture();
//		void detachStencilTexture();
//
//		void disableColorBuffers();
//
//		bool isComplete() const;
//
//		NativeHandle getNativeHandle();
//	};
//}
//
//#endif
