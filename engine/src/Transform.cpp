//
//
//

#include "Transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <algorithm>


namespace aeyon
{
	void Transform::markAsChanged()
	{
		m_isLocalToWorldMatrixDirty = true;
		m_isWorldToLocalMatrixDirty = true;
	}

	Transform::Transform()
	: Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f))
	{
	}

	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: Transform(position, glm::quat(rotation), scale)
	{
	}

	Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
	: m_position(position), m_rotation(rotation), m_scale(scale),
		m_isLocalToWorldMatrixDirty(true), m_isWorldToLocalMatrixDirty(true), m_parent(nullptr)
	{
	}

	void Transform::setPosition(const glm::vec3& position)
	{
		m_position = position;
		markAsChanged();
	}

	void Transform::setLocalPosition(const glm::vec3& position)
	{
		if (m_parent)
		{
			setPosition(m_parent->getPosition() + position);
		}
		else
		{
			setPosition(position);
		}
	}

	void Transform::translate(const glm::vec3& translation)
	{
		translate(translation, Space::Self);
	}

	void Transform::translate(const glm::vec3& translation, Space relativeTo)
	{
		if (relativeTo == Space::Self)
		{
			setPosition(m_position + m_rotation * translation);
		}
		else if (relativeTo == Space::World)
		{
			setPosition(m_position + translation);
		}
	}

	void Transform::setRotation(const glm::quat& rotation)
	{
		m_rotation = rotation;
		markAsChanged();
	}

	void Transform::setRotationEuler(const glm::vec3& eulerAngles)
	{
		setRotation(glm::quat(glm::radians(eulerAngles)));
	}


	void Transform::setLocalRotation(const glm::quat& rotation)
	{
		if (m_parent)
		{
			setRotation(m_parent->getRotation() * rotation);
		}
		else
		{
			setRotation(rotation);
		}
	}

	void Transform::setLocalRotationEuler(const glm::vec3& eulerAngles)
	{
		setLocalRotation(glm::quat(glm::radians(eulerAngles)));
	}

	void Transform::rotate(const glm::vec3& eulerAngles)
	{
		rotate(eulerAngles, Space::Self);
	}

	void Transform::rotate(const glm::vec3& eulerAngles, Space relativeTo)
	{
		glm::quat rotation(glm::radians(eulerAngles));
		if (relativeTo == Space::Self)
		{
			setRotation(m_rotation * rotation);
		}
		else if (relativeTo == Space::World)
		{
			setRotation(rotation * m_rotation);
		}
	}


	void Transform::rotateAround(const glm::vec3& center, const glm::vec3& axis, float angle)
	{
		m_position -= center;
		m_position = glm::angleAxis(glm::radians(angle), axis) * m_position;
		m_position += center;
	}

	void Transform::setScale(const glm::vec3& scale)
	{
		m_scale = scale;
		markAsChanged();
	}


	void Transform::setLocalScale(const glm::vec3& scale)
	{
		if (m_parent)
		{
			setScale(m_scale * scale);
		}
		else
		{
			setScale(scale);
		}
	}


	void Transform::scale(const glm::vec3& scale)
	{
		setScale(m_scale * scale);
	}


	void Transform::lookAt(const glm::vec3& target)
	{
		lookAt(target, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Transform::lookAt(const glm::vec3& target, const glm::vec3& worldUp)
	{
		m_rotation = glm::conjugate(glm::toQuat(glm::lookAtLH(m_position, target, worldUp)));
	}

	glm::vec3 Transform::getPosition() const
	{
		return m_position;
	}

	glm::vec3 Transform::getLocalPosition() const
	{
		if (m_parent)
		{
			return m_parent->getPosition() + m_position;
		}
		else
		{
			return m_position;
		}
	}

	glm::quat Transform::getRotation() const
	{
		return m_rotation;
	}

	glm::quat Transform::getLocalRotation() const
	{
		if (m_parent)
		{
			return m_rotation * m_parent->getRotation();
		}
		else
		{
			return m_rotation;
		}
	}

	glm::vec3 Transform::getRotationEuler() const
	{
		return glm::degrees(glm::eulerAngles(m_rotation));
	}

	glm::vec3 Transform::getLocalRotationEuler() const
	{
		if (m_parent)
		{
			return glm::degrees(m_rotation * glm::eulerAngles(m_parent->getRotation()));
		}
		else
		{
			return glm::degrees(glm::eulerAngles(m_rotation));
		}
	}

	glm::vec3 Transform::getScale() const
	{
		return m_scale;
	}

	glm::vec3 Transform::getLocalScale() const
	{
		if (m_parent)
		{
			return m_parent->getScale() * m_scale;
		}
		else
		{
			return m_scale;
		}
	}

	glm::vec3 Transform::getForward() const
	{
		return glm::normalize(m_rotation * glm::vec3(0.0f, 0.0f, 1.0f));
	}

	glm::vec3 Transform::getRight() const
	{
		return glm::normalize(m_rotation * glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 Transform::getUp() const
	{
		return glm::normalize(m_rotation * glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::mat4x4 Transform::getLocalToWorldMatrix() const
	{
		if (m_isLocalToWorldMatrixDirty)
		{
			glm::vec3 eulerAngles = glm::radians(getRotationEuler());

			m_localToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, m_position.z));
			m_localToWorldMatrix *= glm::mat4_cast(glm::quat(glm::vec3(eulerAngles.x, eulerAngles.y, eulerAngles.z)));
			m_localToWorldMatrix = glm::scale(m_localToWorldMatrix, glm::vec3(m_scale.x, m_scale.y, m_scale.z));

			m_isLocalToWorldMatrixDirty = false;
		}

		return m_localToWorldMatrix;
	}

	glm::mat4x4 Transform::getWorldToLocalMatrix() const
	{
		if (m_isWorldToLocalMatrixDirty)
		{
			m_worldToLocalMatrix = glm::inverse(getLocalToWorldMatrix());
			m_isWorldToLocalMatrixDirty = false;
		}

		return m_worldToLocalMatrix;
	}


	void Transform::setParent(Transform* parent)
	{
		if (m_parent && m_parent != parent)
		{
			auto& oldParentChildren = m_parent->m_children;
			oldParentChildren.erase(std::remove(oldParentChildren.begin(), oldParentChildren.end(), this),
															oldParentChildren.end());

			m_parent = parent;

			if (m_parent)
			{
				m_parent->m_children.push_back(this);
			}
		}
	}

	Transform* Transform::getParent() const
	{
		return m_parent;
	}

	void Transform::detachChildren()
	{
		for (Transform* child : m_children)
		{
			child->m_parent = nullptr;
		}

		m_children.clear();
	}

	const std::vector<Transform*>& Transform::getChildren() const
	{
		return m_children;
	}
}