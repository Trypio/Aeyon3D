//
//
//

#ifndef AEYON3D_ENTITYSTORE_HPP
#define AEYON3D_ENTITYSTORE_HPP

#include "Entity.hpp"
#include "EntityHandleDetails.hpp"
#include <queue>
#include <memory>

namespace aeyon
{
	/**
 * Creates and manages the lifetime of ECS entities.
 */
	class EntityStore
	{
	private:
		/**
		 * 0 == Entity::Invalid.getID()
		 */
		Entity::ID m_entityCounter = 1;
		std::queue<Entity::ID> m_unusedIDs;
		std::unordered_map<Entity, std::shared_ptr<EntityHandleDetails>> m_handles;

		World* m_world;

	public:
		explicit EntityStore(World* world);

		/**
		 * Returns a new valid entity
		 */
		std::shared_ptr<EntityHandleDetails> createEntity();

		/**
		 * Marks the given entity as invalid.
		 *
		 * Note: The internal identifier of the entity may be reused in the future,
		 * so you should never operate on the Entity class itself outside the ECS implementation. Use EntityHandle
		 * for safely saving references to entities, since it is able to check if a specific entity is still valid.
		 */
		void destroyEntity(const Entity& entity);

		/**
		 * Get the info currently associated with the given entity
		 *
		 */
		std::shared_ptr<EntityHandleDetails> getEntityHandleInfo(const Entity& entity) const;

		World* getWorld();
	};
}


#endif
