//
//
//

#ifndef AEYON3D_ENTITYHANDLEDETAILS_HPP
#define AEYON3D_ENTITYHANDLEDETAILS_HPP

#include "Entity.hpp"

namespace aeyon
{
	class World;

/**
 * This class represents the common data between an EntityHandle its respective EntityStore. Thus, if the ECS
 * triggers a change on the enclosed entity, it will be delegated to all references of said entity.
 */
	struct EntityHandleDetails
	{
		World* world;
		Entity entity = Entity::Invalid;

		EntityHandleDetails();
		explicit EntityHandleDetails(World* world, const Entity& entity);

		bool isValid() const;
	};
}

#endif
