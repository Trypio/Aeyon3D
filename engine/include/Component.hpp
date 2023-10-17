//
// Created by thors on 05.10.2020.
//

#ifndef AEYON3D_COMPONENT_HPP
#define AEYON3D_COMPONENT_HPP

namespace aeyon
{
    class Actor;

	class Component
	{
    private:
        Actor* m_actor;
        bool m_isActive;
	public:
        explicit Component();
        void setActive(bool isActive);
        bool isActive() const;
        void setActor(Actor* actor);
        const Actor* getActor() const;
        Actor* getActor();
		virtual ~Component() = default;
	};
}

#endif //AEYON3D_COMPONENT_HPP
