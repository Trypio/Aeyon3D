//
//
//

#ifndef AEYON3D_COMPONENTINSTANCE_HPP
#define AEYON3D_COMPONENTINSTANCE_HPP

#include <unordered_map>
#include <cstddef>

namespace aeyon
{
	/**
	 * This class represents a unique component instance. It is only used inside the ECS implementation and should be
	 * always referenced in the context of a ComponentHandle when used outside of the ECS.
	 */
	class ComponentInstance
	{
	public:
		using ID = std::size_t;
		static const ComponentInstance Invalid;

	private:
		static const ID InvalidID = 0;
		ID m_id;

	public:
		ID getID() const;

		explicit ComponentInstance(ID id = InvalidID);

		explicit operator bool() const;

		friend bool operator==(const ComponentInstance& e1, const ComponentInstance& e2);
		friend bool operator!=(const ComponentInstance& e1, const ComponentInstance& e2);
		friend bool operator<(const ComponentInstance& e1, const ComponentInstance& e2);
		friend bool operator>(const ComponentInstance& e1, const ComponentInstance& e2);
		friend bool operator<=(const ComponentInstance& e1, const ComponentInstance& e2);
		friend bool operator>=(const ComponentInstance& e1, const ComponentInstance& e2);
	};
}

namespace std
{
	template<>
	struct hash<aeyon::ComponentInstance>
	{
		std::size_t operator()(const aeyon::ComponentInstance& c) const
		{
			return std::hash<aeyon::ComponentInstance::ID>()(c.getID());
		}
	};
}


#endif //AEYON3D_COMPONENTINSTANCE_HPP
