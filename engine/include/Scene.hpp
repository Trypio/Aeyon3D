//
//
//

#ifndef AEYON3D_SCENE_HPP
#define AEYON3D_SCENE_HPP

#include "ECS/EntityHandle.hpp"
#include <vector>

namespace aeyon
{
	class Scene
	{
	private:
		std::vector<EntityHandle> m_entities;

	public:
		const std::vector<EntityHandle>& getEntities() const
		{
			return m_entities;
		}

		void addEntity(const EntityHandle& entity)
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
