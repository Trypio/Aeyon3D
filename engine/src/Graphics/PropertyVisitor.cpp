//
// Created by thors on 25.07.2019.
//

#include "Graphics/PropertyVisitor.hpp"
#include "Color.hpp"
#include "Graphics/Texture.hpp"
#include <glm/gtc/type_ptr.hpp>


namespace aeyon
{
	PropertyVisitor::PropertyVisitor(GLuint location)
			: m_location(location)
	{
	}

	void PropertyVisitor::operator()(float f)
	{
		glUniform1f(m_location, f);
	}

	void PropertyVisitor::operator()(const Color& c)
	{
		glUniform4f(m_location, c.r, c.g, c.b, c.a);
	}

	void PropertyVisitor::operator()(const glm::vec2& v)
	{
		glUniform2f(m_location, v.x, v.y);
	}

	void PropertyVisitor::operator()(const glm::vec3& v)
	{
		glUniform3f(m_location, v.x, v.y, v.z);
	}

	void PropertyVisitor::operator()(const glm::vec4& v)
	{
		glUniform4f(m_location, v.x, v.y, v.z, v.w);
	}

	void PropertyVisitor::operator()(const glm::mat2& mat)
	{
		glUniformMatrix2fv(m_location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void PropertyVisitor::operator()(const glm::mat3& mat)
	{
		glUniformMatrix3fv(m_location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void PropertyVisitor::operator()(const glm::mat4& mat)
	{
		glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(mat));
	}


	void PropertyVisitor::operator()(const Resource<Texture>& tex)
	{
	}

	void PropertyVisitor::operator()(const std::vector<glm::vec2>& vs)
	{
		glUniform2fv(m_location, vs.size(), reinterpret_cast<const float*>(vs.data()));
	}

	void PropertyVisitor::operator()(const std::vector<glm::vec3>& vs)
	{
		glUniform3fv(m_location, vs.size(), reinterpret_cast<const float*>(vs.data()));
	}

	void PropertyVisitor::operator()(const std::vector<glm::vec4>& vs)
	{
		glUniform4fv(m_location, vs.size(), reinterpret_cast<const float*>(vs.data()));
	}

	void PropertyVisitor::operator()(const std::vector<glm::mat2>& mats)
	{
		glUniformMatrix2fv(m_location, mats.size(), GL_FALSE, reinterpret_cast<const float*>(mats.data()));
	}

	void PropertyVisitor::operator()(const std::vector<glm::mat3>& mats)
	{
		glUniformMatrix3fv(m_location, mats.size(), GL_FALSE, reinterpret_cast<const float*>(mats.data()));
	}

	void PropertyVisitor::operator()(const std::vector<glm::mat4>& mats)
	{
		glUniformMatrix4fv(m_location, mats.size(), GL_FALSE, reinterpret_cast<const float*>(mats.data()));
	}
}
