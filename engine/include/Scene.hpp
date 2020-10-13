//
//
//

#ifndef AEYON3D_SCENE_HPP
#define AEYON3D_SCENE_HPP

#include "Actor.hpp"
#include <vector>

namespace aeyon
{
	class Scene
	{
	private:
		std::vector<Actor*> m_actors;

	public:
		const std::vector<Actor*>& getActors() const
		{
			return m_actors;
		}

		void addActor(Actor* actor)
		{
			m_actors.push_back(actor);
		}

		void clear()
		{
			m_actors.clear();
		}
	};
}


#endif //AEYON3D_SCENE_HPP
