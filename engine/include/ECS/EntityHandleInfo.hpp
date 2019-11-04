//
//
//

#ifndef AEYON3D_ENTITYHANDLEINFO_HPP
#define AEYON3D_ENTITYHANDLEINFO_HPP

#include "Entity.hpp"

namespace aeyon
{
/**
 * This class represents the common data between an EntityHandle its respective EntityStore. Thus, if the ECS
 * triggers a change on the enclosed entity, it will be delegated to all references of said entity.
 */
	struct EntityHandleInfo
	{
		Entity entity = Entity::Invalid;
		bool isValid = false;

		explicit  EntityHandleInfo(const Entity& entity)
		: entity(entity), isValid(entity != Entity::Invalid)
		{
		}
	};
}

#endif
