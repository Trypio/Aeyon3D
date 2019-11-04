//
//
//

#ifndef AEYON3D_RESOURCECACHE_HPP
#define AEYON3D_RESOURCECACHE_HPP

#include <cstdint>
#include <unordered_map>
#include <set>
#include <memory>
#include <iostream>

#include "Types.hpp"


namespace aeyon
{

	template <typename T>
	class Resource;

	template<typename T>
	class ResourceCache
	{
	private:
		std::unordered_map<ResourceID, std::unique_ptr<T>> m_resources;
		std::set<ResourceID> m_usedIds;
		ResourceID m_idCounter;

		ResourceID getNewResourceID();

	public:
		ResourceCache();

		virtual T* get(ResourceID id);
		virtual Resource<T> load(std::unique_ptr<T> resource);
	};
}


#include "Resource.hpp"

template <typename T>
aeyon::ResourceID aeyon::ResourceCache<T>::getNewResourceID()
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


template <typename T>
aeyon::ResourceCache<T>::ResourceCache() : m_idCounter(1)
{
}

template <typename T>
T* aeyon::ResourceCache<T>::get(ResourceID id)
{
	auto it = m_resources.find(id);

	if (it == m_resources.end())
	{
		std::cerr << "No resource with ID " << id << " has been found" << std::endl;
	}

	return it->second.get();
}

template <typename T>
aeyon::Resource<T> aeyon::ResourceCache<T>::load(std::unique_ptr<T> resource)
{
	ResourceID id = getNewResourceID();
	m_resources[id] = std::move(resource);

	return Resource<T>(id, this);
}

#endif //AEYON3D_RESOURCECACHE_HPP
