//
//
//

#include "ECS/World.hpp"
#include "ECS/System.hpp"
#include "ECS/Entity.hpp"

namespace aeyon
{
	World::World() = default;
	World::~World() = default;

	void World::start()
	{
		for (auto& system : m_systems)
		{
			system->start();
		}
	}

	void World::update()
	{
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

	Entity World::createEntity()
	{
		auto id = EntityID::generate();

		m_entityMasks[id] = Signature();

		return Entity(id, this);
	}

	void World::destroyEntity(const EntityID& entityID)
	{
		for (std::size_t i = 0; i < m_ecRegisters.size(); i++)
		{
			auto& map = m_ecRegisters[i];
			const auto componentID = map.getComponentID(entityID);
			map.eraseEntityID(entityID);
			m_componentStores[i]->destroyComponent(componentID);
		}

		m_entityMasks.erase(entityID);
	}

	void World::addSystem(std::unique_ptr<System> system)
	{
		system->registerWorld(this);

		for (const auto& p : m_entityMasks)
		{
			if ((system->getSignatureAND() & ~p.second).none() || (system->getSignatureOR() & p.second).any())
			{
				system->registerEntity(Entity());
			}
		}

		m_systems.push_back(std::move(system));
	}

	void World::addEntityToSystems(const EntityID& entityID, size_t typeID, const Signature& oldMask)
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
						system->registerEntity(Entity(entityID, this));
					}
				}
				else if (system->getSignatureAND().test(typeID))
				{
					// Check if all AND-bits of the new signature conform with the system mask
					Signature new_mask = oldMask;
					new_mask.set(typeID, true);

					if ((new_mask & system->getSignatureAND()) == system->getSignatureAND() && (oldMask & system->getSignatureAND()) != system->getSignatureAND() && (oldMask & system->getSignatureOR()).none())
					{
						system->registerEntity(Entity(entityID, this));
					}
				}
			}
		}
	}

	void World::removeEntityFromSystems(const EntityID& entityID, size_t typeID, const Signature& oldMask)
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
						system->unregisterEntity(entityID);
					}
				}
				else if (system->getSignatureOR().test(typeID))
				{
					// Check if no OR-bits of the new signature conform with the system mask
					Signature new_mask = oldMask;
					new_mask.set(typeID, false);

					if ((new_mask & system->getSignatureAND()) != system->getSignatureAND() && (oldMask & system->getSignatureOR()).any() && (new_mask & system->getSignatureOR()).none())
					{
						system->unregisterEntity(entityID);
					}
				}
			}
		}
	}

	bool World::isEntityIDValid(const EntityID& entityID) const
	{
		const auto it = m_entityMasks.find(entityID);

		return it != m_entityMasks.end();
	}
}

