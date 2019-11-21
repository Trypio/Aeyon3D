//
//
//

#ifndef AEYON3D_BASECOMPONENTSTORE_HPP
#define AEYON3D_BASECOMPONENTSTORE_HPP

#include "ComponentInstance.hpp"
#include "ComponentID.hpp"

namespace aeyon
{
	/**
	 * Base class of all component stores
	 */
	class ComponentStoreBase
	{
	public:
		virtual ~ComponentStoreBase() = default;

		virtual ComponentInstance copyComponent(const ComponentID& srcID) = 0;
		virtual void destroyComponent(const ComponentID& id) = 0;
	};
}

#endif
