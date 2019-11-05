//
//
//
#ifndef AEYON3D_RESOURCECACHE_HPP
#define AEYON3D_RESOURCECACHE_HPP

#include <cstdint>
#include <unordered_map>
#include <set>
#include <memory>
#include "Types.hpp"
#include "Resource.hpp"

namespace aeyon
{
	template<typename T, typename U>
	class ResourceCache
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<ResourceData<T>>> m_resources;
		std::set<ResourceID> m_usedIds;
		ResourceID m_idCounter;
		ResourceID getNewResourceID();

		virtual std::unique_ptr<T> create(const U& meta) = 0;

	public:
		ResourceCache();

		Resource<T> load(const std::string& name, const U& meta);
	};
}

namespace aeyon
{
	template <typename T, typename U>
	ResourceID aeyon::ResourceCache<T, U>::getNewResourceID()
	{
		auto it = m_usedIds.lower_bound(m_idCounter);
		while (it != m_usedIds.end() && *it == m_idCounter)
		{
			it++;
			m_idCounter++;
		}
		m_usedIds.insert(m_idCounter);
		return m_idCounter++;
	}


	template <typename T, typename U>
	ResourceCache<T, U>::ResourceCache() : m_idCounter(1)
	{
	}

	template <typename T, typename U>
	Resource<T> ResourceCache<T, U>::load(const std::string& name, const U& meta)
	{
		m_resources[name] = std::make_shared<ResourceData<T>>(name, std::move(create(meta)));

		// TODO: Save iterator
		return Resource<T>(m_resources[name]);
	}
}

#endif //AEYON3D_RESOURCECACHE_HPP
