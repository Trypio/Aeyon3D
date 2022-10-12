#ifndef AEYON3D_PROPERTYVISITOR_HPP
#define AEYON3D_PROPERTYVISITOR_HPP

#include <vector>
#include <glm/glm.hpp>
#include "glad/glad.h"
#include "Resource.hpp"

namespace aeyon
{
	class Color;
	class Texture;

	class PropertyVisitor
	{
	private:
		GLuint m_location;

	public:
		explicit PropertyVisitor(GLuint location);

		void operator()(float f);
		void operator()(const Color& c);
		void operator()(const glm::vec2& v);
		void operator()(const glm::vec3& v);
		void operator()(const glm::vec4& v);
		void operator()(const glm::mat2& mat);
		void operator()(const glm::mat3& mat);
		void operator()(const glm::mat4& mat);
		void operator()(const Resource<Texture>& tex);
		void operator()(const std::vector<glm::vec2>& vs);
		void operator()(const std::vector<glm::vec3>& vs);
		void operator()(const std::vector<glm::vec4>& vs);
		void operator()(const std::vector<glm::mat2>& mats);
		void operator()(const std::vector<glm::mat3>& mats);
		void operator()(const std::vector<glm::mat4>& mats);
	};
}

#endif //AEYON3D_PROPERTYVISITOR_HPP
