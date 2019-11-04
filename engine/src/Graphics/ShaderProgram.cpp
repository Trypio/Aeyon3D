//
//
//

#include "Graphics/ShaderProgram.hpp"
#include <memory>
#include <iostream>

namespace aeyon
{
	ShaderProgram::ShaderProgram()
			: m_vertexShader(0), m_fragmentShader(0)
	{
		m_program = glCreateProgram();
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& src) noexcept
	: m_vertexShader(src.m_vertexShader), m_fragmentShader(src.m_fragmentShader), m_program(src.m_program)
	{
		src.m_vertexShader = 0;
		src.m_fragmentShader = 0;
		src.m_program = 0;
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs) noexcept
	{
		m_vertexShader = rhs.m_vertexShader;
		rhs.m_vertexShader = 0;
		m_fragmentShader = rhs.m_fragmentShader;
		rhs.m_fragmentShader = 0;
		m_program = rhs.m_program;
		rhs.m_program = 0;

		return *this;
	}

	ShaderProgram::~ShaderProgram()
	{
		if (m_vertexShader)
			glDeleteShader(m_vertexShader);

		if (m_fragmentShader)
			glDeleteShader(m_fragmentShader);

		if(m_program)
		  glDeleteProgram(m_program);
	}

	void ShaderProgram::compile(ShaderProgram::Type type, const std::string& src)
	{
		GLuint shader;
		GLint success;

		const char* code = src.c_str();

		shader = glCreateShader(static_cast<GLenum>(type));
		glShaderSource(shader, 1, &code, nullptr);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if(!success)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			auto infoLog = std::make_unique<GLchar[]>(static_cast<std::size_t>(infoLogLength));
			glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.get());

			// TODO: Throw exception
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog.get() << std::endl;
		}

		glAttachShader(m_program, shader);
		glDeleteShader(shader);
	}

	void ShaderProgram::link()
	{
		glLinkProgram(m_program);

		GLint success;
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);

		if (!success)
		{
			GLint infoLogLength;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

			auto infoLog = std::make_unique<GLchar[]>(static_cast<std::size_t>(infoLogLength));
			glGetProgramInfoLog(m_program, infoLogLength, nullptr, infoLog.get());

			// TODO: Throw exception
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog.get() << std::endl;
		}
	}

	GLuint ShaderProgram::get() const
	{
		return m_program;
	}
}