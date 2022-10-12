#include "Graphics/PixelFormat.hpp"

namespace aeyon
{
	const PixelFormat PixelFormat::R8 = PixelFormat("R8", 1, 1, GL_R8, GL_RED, GL_UNSIGNED_BYTE);
	const PixelFormat PixelFormat::R16 = PixelFormat("R16", 1, 2, GL_R16, GL_RED, GL_UNSIGNED_SHORT);
	const PixelFormat PixelFormat::RGB8 = PixelFormat("RGB8", 3, 1, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE);
	const PixelFormat PixelFormat::sRGB8 = PixelFormat("sRGB8", 3, 1, GL_SRGB8, GL_RGB, GL_UNSIGNED_BYTE);
	const PixelFormat PixelFormat::RGBA8 = PixelFormat("RGBA8", 4, 1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	const PixelFormat PixelFormat::sRGBA8 = PixelFormat("sRGBA8", 4, 1, GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE);

	// Floating point formats
	const PixelFormat PixelFormat::R32F = PixelFormat("R32F", 1, 4, GL_R32F, GL_RED, GL_FLOAT);
	const PixelFormat PixelFormat::RGB32F = PixelFormat("RGB32F", 3, 4, GL_RGB32F, GL_RGB, GL_FLOAT);
	const PixelFormat PixelFormat::RGBA32F = PixelFormat("RGBA32F", 4, 4, GL_RGBA32F, GL_RGBA, GL_FLOAT);

	// Special formats
	const PixelFormat PixelFormat::Depth = PixelFormat("Depth", 0, 0, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT);
	const PixelFormat PixelFormat::DepthStencil = PixelFormat("DepthStencil", 0, 0, GL_DEPTH_STENCIL, GL_DEPTH_STENCIL, GL_FLOAT);
}
