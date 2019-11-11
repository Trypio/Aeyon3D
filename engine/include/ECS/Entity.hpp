//
//
//

#ifndef AEYON3D_ENTITY_HPP
#define AEYON3D_ENTITY_HPP

#include <unordered_map>

namespace aeyon
{
	/**
	 * This class represents a unique entity instance. It is only used inside the ECS implementation and should be
	 * always referenced in the context of an EntityHandle when used outside of the ECS.
	 */
	class Entity
	{
	public:
		using ID = std::size_t;
		static const Entity Invalid;

	private:
		static const ID InvalidID = 0;
		ID m_id;

	public:
		ID getID() const;

		explicit Entity(ID id = InvalidID);

		explicit operator bool() const;

		friend bool operator==(const Entity& e1, const Entity& e2);
		friend bool operator!=(const Entity& e1, const Entity& e2);
		friend bool operator<(const Entity& e1, const Entity& e2);
		friend bool operator>(const Entity& e1, const Entity& e2);
		friend bool operator<=(const Entity& e1, const Entity& e2);
		friend bool operator>=(const Entity& e1, const Entity& e2);
	};
}

namespace std
{
	template <>
	struct hash<aeyon::Entity>
	{
		std::size_t operator()(const aeyon::Entity& e) const
		{
			return std::hash<aeyon::Entity::ID>()(e.getID());
		}
	};
}

#endif
