#ifndef AEYON3D_SHADERPROGRAM_HPP
#define AEYON3D_SHADERPROGRAM_HPP

#include <glad/glad.h>
#include <string>
#include <any>

namespace aeyon
{
    /**
     * Represents an OpenGL Shader Program object.
     * The public interface is kept abstract in order to extract an abstract base class in the future.
     */
	class ShaderProgram
	{
	public:
		enum class Type : GLenum
		{
			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER
		};

        struct Status
        {
            bool success;
            std::string message;
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

		~ShaderProgram();

		Status compile(Type type, const std::string& src);
		Status link();
		std::any getNativeHandle();
	};
}

#endif //AEYON3D_SHADERPROGRAM_HPP
