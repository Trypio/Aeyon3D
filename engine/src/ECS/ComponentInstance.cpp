//
//
//

#include "ECS/ComponentInstance.hpp"

namespace aeyon
{
	const ComponentInstance ComponentInstance::Invalid;

	ComponentInstance::ComponentInstance(ComponentInstance::ID id) : m_id(id)
	{
	}

	ComponentInstance::ID ComponentInstance::getID() const
	{
		return m_id;
	}


	ComponentInstance::operator bool() const
	{
		return m_id != InvalidID;
	}

	bool operator==(const ComponentInstance& lhs, const ComponentInstance& rhs)
	{
		return lhs.m_id == rhs.m_id;
	}

	bool operator!=(const ComponentInstance& lhs, const ComponentInstance& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator<(const ComponentInstance& lhs, const ComponentInstance& rhs)
	{
		return lhs.m_id < rhs.m_id;
	}

	bool operator>(const ComponentInstance& lhs, const ComponentInstance& rhs)
	{
		return rhs < lhs;
	}

	bool operator<=(const ComponentInstance& lhs, const ComponentInstance& rhs)
	{
		return !(lhs > rhs);
	}

	bool operator>=(const ComponentInstance& lhs, const ComponentInstance& rhs)
	{
		return !(rhs < lhs);
	}
}