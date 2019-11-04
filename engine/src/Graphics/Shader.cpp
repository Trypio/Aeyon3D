//
//
//

#include "Graphics/Shader.hpp"
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include "Graphics/Shader.hpp"
#include "Graphics/ShaderParser.hpp"
#include "Util.hpp"

namespace aeyon
{

	aeyon::Shader::Shader(const std::string& sourceCode)
	{
		createPrograms(sourceCode);
	}

	void aeyon::Shader::createPrograms(const std::string& sourceCode)
	{
		ShaderParser parser(sourceCode);

		std::stringstream headerCode;

		headerCode << "#version 330 core\n";
		headerCode << "#extension GL_ARB_explicit_uniform_location : enable\n\n";

		m_properties["_M"] = {"_M", "mat4", 0, 1};
		m_properties["_M_Inv"] = {"_M_Inv", "mat4", 1, 1};
		m_properties["_V"] = {"_V", "mat4", 2, 1};
		m_properties["_P"] = {"_P", "mat4", 3, 1};
		m_properties["_VP"] = {"_VP", "mat4", 4, 1};
		m_properties["_MVP"] = {"_MVP", "mat4", 5, 1};
		m_properties["_MV_T_Inv"] = {"_MV_T_Inv", "mat4", 6, 1};
		m_properties["_AmbientColor"] = {"_AmbientColor", "vec4", 7, 1};
		m_properties["_LightPosition"] = {"_LightPosition", "vec4", 8, 8};
		m_properties["_LightColor"] = {"_LightColor", "vec4", 16, 8};
		m_properties["_AttenuationFactors"] = {"_AttenuationFactors", "vec4", 24, 8};
		m_properties["_TextureOffset"] = {"_TextureOffset", "vec2", 32, 1};
		m_properties["_TextureScale"] = {"_TextureScale", "vec2", 33, 1};
		m_properties["_WorldToLight"] = {"_WorldToLight", "mat4", 34, 1};
		m_properties["_LightToWorld"] = {"_LightToWorld", "mat4", 35, 1};

		GLuint propertyIndex = 36;

		m_name = parser.getName();



		for (const auto& property : parser.getProperties())
		{
			// TODO: Strip and parse possible array size of property.name
			std::size_t size = 1;

			m_properties[property.name] = {property.name, property.type, propertyIndex, size};

			propertyIndex++;
		}

		for (const auto& p : m_properties)
		{
			headerCode << "layout (location = " << p.second.location << ") uniform " << p.second.type << " " << p.second.name;
			if (p.second.size > 1)
			{
				headerCode << "[" << p.second.size << "]";
			}
			headerCode << ";\n";
		}

		headerCode << "\n";

		std::uint32_t passIndex = 0;
		for (const auto& pass : parser.getPasses())
		{
			std::string vertexCode, fragmentCode;

			vertexCode = headerCode.str() + pass.vertexCode;

			//util::dumpGLSL(m_name + std::to_string(passIndex) + ".vertex.glsl", vertexCode);

			fragmentCode = headerCode.str() + pass.fragmentCode;

			//util::dumpGLSL(m_name + std::to_string(passIndex) + ".fragment.glsl", fragmentCode);

			ShaderProgram prog;

			prog.compile(ShaderProgram::Type::Vertex, vertexCode);
			prog.compile(ShaderProgram::Type::Fragment, fragmentCode);

			prog.link();

			m_programs[passIndex++] = std::move(prog);
		}
	}

	const std::string& Shader::getName() const
	{
		return m_name;
	}

	ShaderProgram& Shader::getShaderProgram(std::size_t passIndex)
	{
		// TODO: 8 Bit pass index, 24 Bit options
		return m_programs[passIndex];
	}

	const std::unordered_map<std::string, Shader::Property>& Shader::getPropertyMap() const
	{
		return m_properties;
	}

}
