////
////
////
//
//#include "Graphics/FrameBuffer.hpp"
//
//namespace aeyon
//{
//	FrameBuffer::FrameBuffer()
//	{
//		glGenFramebuffers(1, &m_fbo);
//	}
//
//	FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other) noexcept
//	{
//		swap(*this, other);
//
//		return *this;
//	}
//
//	FrameBuffer::FrameBuffer(FrameBuffer&& other) noexcept
//	: FrameBuffer()
//	{
//		swap(*this, other);
//	}
//
//	FrameBuffer::~FrameBuffer()
//	{
//		if (m_fbo)
//			glDeleteFramebuffers(1, &m_fbo);
//	}
//
//	void swap(FrameBuffer& first, FrameBuffer& second) noexcept
//	{
//		using std::swap;
//
//		swap(first.m_fbo, second.m_fbo);
//	}
//
//	FrameBuffer FrameBuffer::copy(/*Rect src, Rect dst*/) const
//	{
//		throw std::logic_error("Function not implemented");
//		FrameBuffer buffer;
////
////		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
////		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer.m_fbo);
////
////		glBlitFramebuffer(srcWidth, srcHeight, )
//
//	}
//
//	void FrameBuffer::attach(GLenum attachment, const Resource <Texture>& texture)
//	{
//		GLint stash;
//		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &stash);
//		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
//
//		switch (texture->getType())
//		{
//			case Texture::Type::Tex2D:
//				glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->getNativeHandle(), 0);
//				break;
//			default:
//				throw std::runtime_error("Passed unsupported texture type as frame buffer attachment");
//		}
//
//		glBindFramebuffer(GL_FRAMEBUFFER, stash);
//	}
//
//	void FrameBuffer::attachColorTexture(Resource<Texture> texture, std::size_t index)
//	{
//        attach(GL_COLOR_ATTACHMENT0 + index, texture);
//	}
//
//	void FrameBuffer::attachDepthTexture(Resource<Texture> texture)
//	{
//        attach(GL_DEPTH_ATTACHMENT, texture);
//	}
//
//	void FrameBuffer::attachStencilTexture(Resource<Texture> texture)
//	{
//        attach(GL_STENCIL_ATTACHMENT, texture);
//	}
//
//	void FrameBuffer::detachColorTexture(std::size_t index)
//	{
//
//	}
//
//	void FrameBuffer::detachDepthTexture()
//	{
//
//	}
//
//	void FrameBuffer::detachStencilTexture()
//	{
//
//	}
//
//	void FrameBuffer::disableColorBuffers()
//	{
//
//	}
//
//	bool FrameBuffer::isComplete() const
//	{
//		return false;
//	}
//
//	void* FrameBuffer::getNativeHandle()
//	{
//		return nullptr;
//	}
//}
