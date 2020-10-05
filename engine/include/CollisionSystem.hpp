//
//
//

#ifndef AEYON3D_COLLISIONSYSTEM_HPP
#define AEYON3D_COLLISIONSYSTEM_HPP

#include <iostream>
#include "ECS/System.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"

namespace aeyon
{
	class CollisionSystem : public System
	{
	private:
		struct Collision
		{
			BoxCollider* first;
			BoxCollider* second;
		};

	public:
		CollisionSystem()
		{
			requireComponent<Transform>();
			requireComponent<BoxCollider>();
		}

		void update() override
		{
			std::vector<Transform*> transforms;
			std::vector<BoxCollider*> colliders;

			for (const auto& entity : getEntities())
			{

				transforms.push_back(m_world->getComponent<Transform>(m_world->getComponentID<Transform>(entity)));
				colliders.push_back(m_world->getComponent<BoxCollider>(m_world->getComponentID<BoxCollider>(entity)));
			}
		}
	};
}

#endif //AEYON3D_COLLISIONSYSTEM_HPP
