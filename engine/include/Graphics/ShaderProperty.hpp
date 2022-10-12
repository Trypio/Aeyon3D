#ifndef AEYON3D_SHADERPROPERTY_HPP
#define AEYON3D_SHADERPROPERTY_HPP

#include <string>
#include <glad/glad.h>

namespace aeyon
{
    /**
     * OpenGL shader property
     */
	struct ShaderProperty
	{
		std::string name;
		std::string type;
		GLuint location;
		std::size_t size;
	};
}

#endif //AEYON3D_SHADERPROPERTY_HPP
