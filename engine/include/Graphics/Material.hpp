//
//
//

#ifndef AEYON3D_MATERIAL_HPP
#define AEYON3D_MATERIAL_HPP

#include "Shader.hpp"
#include "Resource.hpp"
#include <glm/glm.hpp>
#include "Color.hpp"
#include "Texture.hpp"
#include <variant>
#include <vector>
#include <stdexcept>

namespace aeyon
{
	class Material
	{
	public:
		using ParameterValue = std::variant<
				// Sclar Types
				float,
				Color,
				glm::vec2, glm::vec3, glm::vec4,
				glm::mat2, glm::mat3, glm::mat4,
				Resource<Texture>,
				// Array Types
				std::vector<glm::vec2>, std::vector<glm::vec3>, std::vector<glm::vec4>,
				std::vector<glm::mat2>, std::vector<glm::mat3>, std::vector<glm::mat4>
				>;

	private:
		struct Parameter
		{
			Parameter(ShaderProperty shaderProperty, ParameterValue value)
					: shaderProperty(std::move(shaderProperty)), value(std::move(value)) {}

			ShaderProperty shaderProperty;
			ParameterValue value;
		};

		Resource<Shader> m_shader;
		std::unordered_map<std::string, Parameter> m_parameters;
		std::unordered_map<std::string, GLuint> m_textureIndices;
		glm::vec2 m_textureOffset = glm::vec2(0.0f, 0.0f);
		glm::vec2 m_textureScale = glm::vec2(1.0f, 1.0f);

	public:
		explicit Material(Resource<Shader> shader);

		Resource<Shader> getShader() const;

		template<typename T>
		void setParameter(const std::string& name, T&& value)
		{
			auto it = m_parameters.find(name);
			if (it == m_parameters.end())
			{
				throw std::runtime_error(std::string("Material has no parameter named " + name));
			}

			it->second.value = std::forward<T>(value);
		}

		const std::unordered_map<std::string, Parameter>& getParameterMap() const;;
		const std::unordered_map<std::string, GLuint>& getTextureIndexMap() const;;

		void setTextureOffset(glm::vec2 offset);
		void setTextureScale(glm::vec2 scale);
		const glm::vec2& getTextureOffset() const;
		const glm::vec2& getTextureScale() const;
	};
}

#endif //AEYON3D_MATERIAL_HPP
