//
//
//

#ifndef AEYON3D_SCENE_HPP
#define AEYON3D_SCENE_HPP

#include "ECS/Entity.hpp"
#include <vector>

namespace aeyon
{
	class Scene
	{
	private:
		std::vector<Entity> m_entities;

	public:
		const std::vector<Entity>& getEntities() const
		{
			return m_entities;
		}

		void addEntity(const Entity& entity)
		{
			m_entities.push_back(entity);
		}

		void clear()
		{
			m_entities.clear();
		}
	};
}


#endif //AEYON3D_SCENE_HPP
