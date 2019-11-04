//
//
//

#ifndef AEYON3D_TRANSFORM_HPP
#define AEYON3D_TRANSFORM_HPP

#include "ECS/Component.hpp"
#include "Space.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

namespace aeyon
{
	class Transform : public Component<Transform>
	{
	private:
		glm::vec3 m_position;
		glm::quat m_rotation;
		glm::vec3 m_scale;

		mutable glm::mat4x4 m_localToWorldMatrix;
		mutable glm::mat4x4 m_worldToLocalMatrix;
		mutable bool m_isLocalToWorldMatrixDirty;
		mutable bool m_isWorldToLocalMatrixDirty;

		Transform* m_parent;
		std::vector<Transform*> m_children;

		void markAsChanged();

	public:
		Transform();
		Transform(const glm::vec3& position, const glm::vec3& rotationEuler, const glm::vec3& scale);
		Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);

		void setPosition(const glm::vec3& position);
		void setLocalPosition(const glm::vec3& position);
		void translate(const glm::vec3& translation);
		void translate(const glm::vec3& translation, Space relativeTo);

		void setRotation(const glm::quat& rotation);
		void setRotationEuler(const glm::vec3& eulerAngles);
		void setLocalRotation(const glm::quat& rotation);
		void setLocalRotationEuler(const glm::vec3& eulerAngles);
		void rotate(const glm::vec3& eulerAngles);
		void rotate(const glm::vec3& eulerAngles, Space relativeTo);
		void rotateAround(const glm::vec3& center, const glm::vec3& axis, float angle);

		void setScale(const glm::vec3& scale);
		void setLocalScale(const glm::vec3& scale);
		void scale(const glm::vec3& scale);

		void lookAt(const glm::vec3& target);
		void lookAt(const glm::vec3& target, const glm::vec3& worldUp);

		glm::vec3 getPosition() const;
		glm::vec3 getLocalPosition() const;

		glm::quat getRotation() const;
		glm::quat getLocalRotation() const;
		glm::vec3 getRotationEuler() const;
		glm::vec3 getLocalRotationEuler() const;

		glm::vec3 getScale() const;
		glm::vec3 getLocalScale() const;

		glm::vec3 getForward() const;
		glm::vec3 getRight() const;
		glm::vec3 getUp() const;

		glm::mat4x4 getLocalToWorldMatrix() const;
		glm::mat4x4 getWorldToLocalMatrix() const;

		void setParent(Transform* parent);
		Transform* getParent() const;
		void detachChildren();
		const std::vector<Transform*>& getChildren() const;
	};
}


#endif //AEYON3D_TRANSFORM_HPP
