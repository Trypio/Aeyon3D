//
//
//

#ifndef AEYON3D_SHADERPROGRAM_HPP
#define AEYON3D_SHADERPROGRAM_HPP

#include "glad/glad.h"
#include <string>

namespace aeyon
{
	class ShaderProgram
	{
	public:
		enum class Type : GLenum
		{
			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER
		};

	private:
		GLuint m_vertexShader, m_fragmentShader;
		GLuint m_program;

	public:
		ShaderProgram();

		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		ShaderProgram(ShaderProgram&& src) noexcept;
		ShaderProgram& operator=(ShaderProgram&& rhs) noexcept;

		virtual ~ShaderProgram();

		void compile(Type type, const std::string& src);
		void link();
		GLuint get() const;
	};
}

#endif //AEYON3D_SHADERPROGRAM_HPP
