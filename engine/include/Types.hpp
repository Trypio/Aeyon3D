//
//
//

#ifndef AEYON3D_TYPES_HPP
#define AEYON3D_TYPES_HPP

#include <cstdint>
#include <bitset>
#include "glad/glad.h"


namespace aeyon
{
	constexpr std::size_t NumComponentTypes = 20;
	using Signature = std::bitset<NumComponentTypes>;

	constexpr std::size_t MaxNumberOfComponents = 1024;

	using ResourceID = std::uint32_t;

	enum class VertexFormat
	{
		P1,
		P1N1,
		P1N1UV1,
		P1N1UV1T1B1
	};

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

	using TIndex = GLuint;

};

#endif //AEYON3D_TYPES_HPP
