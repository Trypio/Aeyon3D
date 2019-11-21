//
// Created by thors on 12.11.2019.
//

#ifndef AEYON3D_UUID_HPP
#define AEYON3D_UUID_HPP

#include "uuid.h"

namespace aeyon
{
	class UUID;
}

namespace std
{
	template<>
	struct hash<UUID>;
}

namespace aeyon
{
	class UUID
	{
	private:
		uuids::uuid m_uuid;

		explicit UUID(uuids::uuid uuid) : m_uuid(uuid)
		{}

	public:
		friend struct std::hash<UUID>;

		UUID() = default;

		static UUID generate()
		{
			return UUID(uuids::uuid_system_generator{}());
		}

		bool isNil() const
		{
			return m_uuid.is_nil();
		}

		friend bool operator==(const UUID& lhs, const UUID& rhs)
		{
			return lhs.m_uuid == rhs.m_uuid;
		}

		friend bool operator!=(const UUID& lhs, const UUID& rhs)
		{
			return lhs.m_uuid != rhs.m_uuid;
		}

		friend bool operator<(const UUID& lhs, const UUID& rhs)
		{
			return lhs.m_uuid < rhs.m_uuid;
		}
	};
}

namespace std
{
	template <>
	struct hash<aeyon::UUID>
	{
		size_t operator()(const aeyon::UUID& uuid) const
		{
			return std::hash<uuids::uuid>{}(uuid.m_uuid);
		}
	};
}

#endif //AEYON3D_UUID_HPP
