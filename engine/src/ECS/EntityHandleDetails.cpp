//
//
//

#include "ECS/EntityHandleDetails.hpp"
#include "ECS/World.hpp"

namespace aeyon
{
	aeyon::EntityHandleDetails::EntityHandleDetails()
			: world(nullptr), entity(Entity::Invalid)
	{
	}

	EntityHandleDetails::EntityHandleDetails(World* world, const Entity& entity)
			: world(world), entity(entity)
	{
	}

	bool EntityHandleDetails::isValid() const
	{
		return world && entity != Entity::Invalid;
	}
}