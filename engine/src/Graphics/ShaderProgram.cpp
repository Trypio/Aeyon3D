#include "Graphics/ShaderProgram.hpp"
#include <memory>

namespace aeyon
{
	ShaderProgram::ShaderProgram()
			: m_program(0), m_vertexShader(0), m_fragmentShader(0)
	{
		m_program = glCreateProgram();
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& src) noexcept
	: m_program(src.m_program), m_vertexShader(src.m_vertexShader), m_fragmentShader(src.m_fragmentShader)
	{
        src.m_program = 0;
		src.m_vertexShader = 0;
		src.m_fragmentShader = 0;
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs) noexcept
	{
        m_program = rhs.m_program;
        rhs.m_program = 0;
		m_vertexShader = rhs.m_vertexShader;
		rhs.m_vertexShader = 0;
		m_fragmentShader = rhs.m_fragmentShader;
		rhs.m_fragmentShader = 0;

		return *this;
	}

	ShaderProgram::~ShaderProgram()
	{
        glDeleteShader(m_vertexShader);
        glDeleteShader(m_fragmentShader);
        glDeleteProgram(m_program);
	}

	ShaderProgram::Status ShaderProgram::compile(ShaderProgram::Type type, const std::string& src)
	{
		GLuint shader;
		GLint success;

		const char* code = src.c_str();

		shader = glCreateShader(static_cast<GLenum>(type));
		glShaderSource(shader, 1, &code, nullptr);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        Status status = { true, ""};

		if(!success)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

            status.success = false;
            status.message.resize(infoLogLength);
			glGetShaderInfoLog(shader, infoLogLength, nullptr, &status.message[0]);
		}

		glAttachShader(m_program, shader);
		glDeleteShader(shader);

        return status;
	}

	ShaderProgram::Status ShaderProgram::link()
	{
		glLinkProgram(m_program);

		GLint success;
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);

        Status status = {true, ""};

		if (!success)
		{
			GLint infoLogLength;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

			status.success = false;
            status.message.resize(infoLogLength);
			glGetProgramInfoLog(m_program, infoLogLength, nullptr, &status.message[0]);
		}

        return status;
	}

	std::any ShaderProgram::getNativeHandle()
	{
		return m_program;
	}
}
