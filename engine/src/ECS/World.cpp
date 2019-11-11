//
//
//

#include <ECS/World.hpp>

#include "ECS/World.hpp"
#include "ECS/System.hpp"

namespace aeyon
{
	void World::init()
	{
		for (auto& system : m_systems)
		{
			system->init();
		}
	}

	void World::update()
	{
		// TODO(taurheim) check to make sure that the world has called init
		eventSystem.update();

		for (auto& system : m_systems)
		{
			system->update();
		}
	}

	void World::fixedUpdate()
	{
		for (auto& system : m_systems)
		{
			system->fixedUpdate();
		}
	}

	void World::lateUpdate()
	{
		for (auto& system : m_systems)
		{
			system->postUpdate();
		}
	}

	EntityHandle World::createEntity()
	{
		auto infoPtr = m_entityStore.createEntity();

		m_entityMasks[infoPtr->entity] = Signature();

		return EntityHandle(infoPtr);
	}

	void World::destroyEntity(const Entity& entity)
	{
		// TODO: Find attached components and call destroy() (same problem as with copy())
		for (auto& map : m_entityMaps)
		{
			map.remove(entity);
		}

		m_entityMasks.erase(entity);

		m_entityStore.destroyEntity(entity);
	}

	void World::addSystem(std::unique_ptr<System> system)
	{
		system->registerWorld(this);

		for (const auto& p : m_entityMasks)
		{
			if ((system->getSignatureAND() & ~p.second).none() || (system->getSignatureOR() & p.second).any())
			{
				system->registerEntity(EntityHandle(m_entityStore.getEntityHandleInfo(p.first)));
			}
		}

		m_systems.push_back(std::move(system));
	}

	void World::addEntityToSystems(const Entity& entity, size_t typeID, const Signature& oldMask)
	{
		for (auto& system : m_systems)
		{
			if (!oldMask.test(typeID)) // Only continue if the bit wasn't already set in the old mask. TODO: This doesn't allow for duplicate component types
			{
				if (system->getSignatureOR().test(typeID))
				{
					// TODO: Shouldn't it be newMask and any() in the first comparison?
					// Check if any of the bits of the old mask is also set in the system's OR-mask. This would mean that the entity was already added to the system
					if ((oldMask & system->getSignatureOR()).none() && (oldMask & system->getSignatureAND()) != system->getSignatureAND())
					{
						auto infoPtr = m_entityStore.getEntityHandleInfo(entity);
						system->registerEntity(EntityHandle(infoPtr));
					}
				}
				else if (system->getSignatureAND().test(typeID))
				{
					// Check if all AND-bits of the new signature conform with the system mask
					Signature new_mask = oldMask;
					new_mask.set(typeID, true);

					if ((new_mask & system->getSignatureAND()) == system->getSignatureAND() && (oldMask & system->getSignatureAND()) != system->getSignatureAND() && (oldMask & system->getSignatureOR()).none())
					{
						auto infoPtr = m_entityStore.getEntityHandleInfo(entity);
						system->registerEntity(EntityHandle(infoPtr));
					}
				}
			}
		}
	}

	void World::removeEntityFromSystems(const Entity& entity, size_t typeID, const Signature& oldMask)
	{
		for (auto& system : m_systems)
		{
			if (oldMask.test(typeID)) // Only continue if the bit was set in the old mask. TODO: This doesn't allow for duplicate component types
			{
				// Check if the bit is part of the AND-mask. That means that the condition can't be fulfilled any longer.
				if (system->getSignatureAND().test(typeID))
				{
					// Check if the old mask was even fulfilling the systems AND-mask
					if ((oldMask & system->getSignatureAND()) == system->getSignatureAND())
					{
						system->unregisterEntity(entity);
					}
				}
				else if (system->getSignatureOR().test(typeID))
				{
					// Check if no OR-bits of the new signature conform with the system mask
					Signature new_mask = oldMask;
					new_mask.set(typeID, false);

					if ((new_mask & system->getSignatureAND()) != system->getSignatureAND() && (oldMask & system->getSignatureOR()).any() && (new_mask & system->getSignatureOR()).none())
					{
						system->unregisterEntity(entity);
					}
				}
			}
		}
	}

	World::World()
	: m_entityStore(this)
	{

	}
}

