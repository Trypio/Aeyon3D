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



};

#endif //AEYON3D_TYPES_HPP
