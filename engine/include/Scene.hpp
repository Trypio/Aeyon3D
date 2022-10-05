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
        std::string m_name;
		std::vector<Actor> m_actors;

	public:
        Scene(const std::string& name) : m_name(name)
        {
        }

		const std::vector<Actor>& getActors() const
		{
			return m_actors;
		}

        std::vector<Actor>& getActors()
        {
            return m_actors;
        }


        // Instantiate
        void addActor(Actor actor)
        {
            m_actors.push_back(std::move(actor));
        }

        void addActors(std::vector<Actor> actors)
        {
            std::move(std::begin(actors), std::end(actors), std::back_inserter(m_actors));
            actors.clear();
        }

		void clear()
		{
			m_actors.clear();
		}
	};
}


#endif //AEYON3D_SCENE_HPP
