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
	Transform::Transform() :
    m_localPosition(0.0f), m_localRotation(glm::vec3(0.0f)), m_localScale(1.0f),
    m_position(0.0f), m_rotation(glm::vec3(0.0f)), m_scale(1.0f),
    m_localEulerAngles(0.0f), m_eulerAngles(0.0f),
    m_forward(glm::vec3(0.0f, 0.0f, 1.0f)),
    m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_right(glm::vec3(1.0f, 0.0f, 0.0f)),
    m_parent(nullptr),
    m_localToWorldMatrix(1.0f), m_worldToLocalMatrix(1.0f)
    {
	}

    void Transform::recalculateDirections()
    {
        m_forward = glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f) * m_rotation);
        m_up = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f) * m_rotation);
        m_right = glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f) * m_rotation);
    }

    void Transform::setPosition(const glm::vec3& position)
    {
        setLocalPosition((m_parent ? m_parent->getWorldToLocalMatrix() : glm::mat4x4(1.0f))
                         * glm::vec4(position, 1.0f));
    }

	void Transform::setLocalPosition(const glm::vec3& localPosition)
	{
        m_localPosition = localPosition;
        applyLocalChanges();
	}

	void Transform::translate(const glm::vec3& translation)
	{
		translate(translation, Space::Local);
	}

	void Transform::translate(const glm::vec3& translation, Space relativeTo)
	{
		if (relativeTo == Space::Local)
		{
			setLocalPosition(m_localPosition + translation);
		}
		else if (relativeTo == Space::World)
		{
			setPosition(m_position + translation);
		}
	}

	void Transform::setRotation(const glm::quat& rotation)
	{
        setLocalRotation((m_parent ? glm::inverse(m_parent->getRotation()) : glm::identity<glm::quat>()) * rotation);
	}

    void Transform::setRotation(const glm::vec3& eulerAngles)
    {
        setRotation(glm::quat(glm::radians(eulerAngles)));
    }

    void Transform::setLocalRotation(const glm::quat& rotation)
	{
        m_localRotation = rotation;
        applyLocalChanges();
	}

    void Transform::setLocalRotation(const glm::vec3& eulerAngles)
    {
        setLocalRotation(glm::quat(glm::radians(eulerAngles)));
    }

    void Transform::rotate(const glm::vec3& eulerAngles)
	{
		rotate(eulerAngles, Space::Local);
	}

	void Transform::rotate(const glm::vec3& eulerAngles, Space relativeTo)
	{
		glm::quat rotation(glm::radians(eulerAngles));
		if (relativeTo == Space::Local)
		{
            setLocalRotation(m_localRotation * rotation);
		}
		else if (relativeTo == Space::World)
		{
			setRotation(rotation * m_rotation);
		}
	}

    void Transform::rotate(const glm::vec3& axis, float angle)
    {
        // TODO
    }

    void Transform::rotate(const glm::vec3& axis, float angle, Space relativeTo)
    {
        // TODO
    }

    void Transform::rotateAround(const glm::vec3& center, const glm::vec3& axis, float angle)
	{
        glm::vec3 pos = m_position - center;
		pos = glm::angleAxis(glm::radians(angle), axis) * pos;
		pos += center;
        setPosition(pos);
	}

    void Transform::setLocalScale(const glm::vec3& localScale)
	{
        m_localScale = localScale;
        applyLocalChanges();
	}

	void Transform::scale(const glm::vec3& scaling)
	{
        setLocalScale(m_localScale * scaling);
	}

	void Transform::lookAt(const glm::vec3& target)
	{
		lookAt(target, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Transform::lookAt(const glm::vec3& target, const glm::vec3& worldUp)
	{
        setRotation(glm::conjugate(glm::toQuat(glm::lookAtLH(m_position, target, worldUp))));
	}

	const glm::vec3& Transform::getPosition() const
    {
		return m_position;
	}

	const glm::vec3& Transform::getLocalPosition() const
    {
        return m_localPosition;
	}

	const glm::quat& Transform::getRotation() const
    {
		return m_rotation;
	}

	const glm::quat& Transform::getLocalRotation() const
    {
        return m_localRotation;
	}

    const glm::vec3& Transform::getEulerAngles() const
    {
        return m_eulerAngles;
    }

    const glm::vec3& Transform::getLocalEulerAngles() const
    {
        return m_localEulerAngles;
    }

    const glm::vec3& Transform::getScale() const
    {
        return m_scale;
    }

    const glm::vec3& Transform::getLocalScale() const
    {
        return m_localScale;
	}

	const glm::vec3& Transform::getForward() const
    {
		return m_forward;
	}

	const glm::vec3& Transform::getRight() const
    {
		return m_right;
	}

	const glm::vec3& Transform::getUp() const
    {
		return m_up;
	}

    void Transform::recalculateMatrices()
    {
        m_localToWorldMatrix = glm::translate(glm::mat4(1.0f), m_localPosition);
        m_localToWorldMatrix *= glm::mat4_cast(m_localRotation);
        m_localToWorldMatrix = glm::scale(m_localToWorldMatrix, m_localScale);

        m_localToWorldMatrix *= m_parent ? m_parent->getLocalToWorldMatrix() : glm::mat4x4(1.0f);

        m_worldToLocalMatrix = glm::inverse(m_localToWorldMatrix);
    }

    const glm::mat4x4& Transform::getLocalToWorldMatrix() const
    {
		return m_localToWorldMatrix;
	}

	const glm::mat4x4& Transform::getWorldToLocalMatrix() const
    {
		return m_worldToLocalMatrix;
	}

    void Transform::applyLocalChanges()
    {
        recalculateMatrices();
        m_position = m_localToWorldMatrix[3];
        m_rotation = m_localToWorldMatrix;
        m_eulerAngles = glm::degrees(glm::eulerAngles(m_rotation));
        m_localEulerAngles = glm::degrees(glm::eulerAngles(m_localRotation));
        m_scale = m_parent ? m_parent->getScale() * m_localScale : m_localScale;
        recalculateDirections();

        for (auto child : m_children)
        {
            assert(child != this);
            child->applyLocalChanges();
        }
    }

	void Transform::setParent(Transform* parent)
	{
		if (m_parent != parent)
		{
			if (m_parent != nullptr)
			{
				auto& oldParentChildren = m_parent->m_children;
				oldParentChildren.erase(std::remove(oldParentChildren.begin(), oldParentChildren.end(), this),
																oldParentChildren.end());
			}

			if (parent != nullptr)
			{
				parent->m_children.push_back(this);
			}

            m_parent = parent;
            m_localRotation = glm::inverse(parent->getRotation()) * m_rotation;
            m_localPosition = m_position - parent->getPosition();
            m_localScale /= parent->getLocalScale();
            applyLocalChanges();
        }
	}

    Transform* Transform::getParent() const
    {
        return m_parent;
    }

    const std::vector<Transform*>& Transform::getChildren() const
    {
        return m_children;
    }
}
