//
//
//

#include "Graphics/Material.hpp"

namespace aeyon
{
	Material::Material(Resource<Shader> shader)
	: m_shader(std::move(shader))
	{
		GLuint currentTexIndex = 0;
		for (const auto& p : m_shader->getPropertyMap())
		{
			Parameter entry(p.second, 0.0f);

			if (entry.shaderProperty.type.find("sampler") == 0)
			{
				m_textureIndices[entry.shaderProperty.name] = currentTexIndex++;
			}

			m_parameters.insert(std::make_pair(entry.shaderProperty.name, entry));
		}
	}

	Resource<Shader> Material::getShader() const
	{
		return m_shader;
	}

	const std::unordered_map<std::string, Material::Parameter>& Material::getParameterMap() const
	{
		return m_parameters;
	}

	const std::unordered_map<std::string, GLuint>& Material::getTextureIndexMap() const
	{
		return m_textureIndices;
	}

	void Material::setTextureOffset(glm::vec2 offset)
	{
		m_textureOffset = offset;
	}

	const glm::vec2& Material::getTextureOffset() const
	{
		return m_textureOffset;
	}

	void Material::setTextureScale(glm::vec2 scale)
	{
		m_textureScale = scale;
	}

	const glm::vec2& Material::getTextureScale() const
	{
		return m_textureScale;
	}
}
