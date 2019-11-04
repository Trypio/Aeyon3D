//
//
//

#ifndef AEYON3D_SYSTEM_HPP
#define AEYON3D_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "EntityHandle.hpp"

namespace aeyon
{
	class World;

	/**
	 * A System adds behavior to all component types that are assigned to it. Use this class as a base class for your
	 * own systems and simply overwrite the desired methods (init, update, fixedUpdate, postUpdate) which are triggered
	 * by the game loop of the assigned World.
	 * At each call, getEntities() returns a list of entities which fulfill the component requirements stated
	 * by requireComponent<T>() and acceptComponent<T>().
	 */
	class System
	{
	protected:
		World* m_world = nullptr;
		Signature m_signatureAND;
		Signature m_signatureOR;
		std::vector<EntityHandle> m_entities;

	public:
		virtual ~System() = default;

		virtual void init() {};
		virtual void update() {};
		virtual void fixedUpdate() {}
		virtual void postUpdate() {}

		void registerWorld(World* world);

		void registerEntity(const EntityHandle& entity);
		void unregisterEntity(const Entity& entity);
    const std::vector<EntityHandle>& getEntities() const;

    /**
     * Adds a component type to the list of required components that an entity needs to have to be handled by this
     * system (AND-operation). Use acceptComponent() if the component type is only optional.
     * @tparam T The component type
     */
		template <typename T>
		void requireComponent()
		{
			m_signatureAND.set(GetComponentTypeID<T>(), true);
		}

		/**
		 * Adds a component type to the list of optional components that an entity might have to be handled by this
     * system (OR-operation). Use requireComponent() if you want to force an entity to have all given component types.
		 * @tparam T
		 */
		template <typename T>
		void acceptComponent()
		{
			m_signatureOR.set(GetComponentTypeID<T>(), true);
		}

		const Signature& getSignatureAND() const;
		const Signature& getSignatureOR() const;
	};
}


#endif //AEYON3D_SYSTEM_HPP
