//
//
//

#ifndef AEYON3D_COLLISIONSYSTEM_HPP
#define AEYON3D_COLLISIONSYSTEM_HPP

#include <iostream>
#include "System.hpp"
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

		Scene* m_scene;

	public:
		CollisionSystem(Scene* scene)
		: m_scene(scene)
		{
		}

		void update() override
		{
			std::vector<Transform*> transforms;
			std::vector<BoxCollider*> colliders;

			for (auto actor : m_scene->getActors())
			{
				transforms.push_back(actor->getComponent<Transform>());
				colliders.push_back(actor->getComponent<BoxCollider>());
			}
		}
	};
}

#endif //AEYON3D_COLLISIONSYSTEM_HPP
