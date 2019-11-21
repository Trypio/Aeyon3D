//
//
//

#include "ECS/System.hpp"
#include "ECS/Entity.hpp"

namespace aeyon
{
	void System::registerWorld(World* world)
	{
		m_world = world;
	}


	const Signature& System::getSignatureAND() const
	{
		return m_signatureAND;
	}

	const Signature& System::getSignatureOR() const
	{
		return m_signatureOR;
	}

	void System::registerEntity(const Entity& entity)
	{
		m_entities.push_back(entity);
	}

	void System::unregisterEntity(const EntityID& entity)
	{
		auto removeIt = std::remove_if(
				m_entities.begin(),
				m_entities.end(),
				[&entity](const auto& e) { return e.getID() == entity; }
				);

		m_entities.erase(removeIt);
	}

	const std::vector<Entity>& System::getEntities() const
	{
		return m_entities;
	}
}