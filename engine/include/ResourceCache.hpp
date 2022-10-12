//
//
//
#ifndef AEYON3D_RESOURCECACHE_HPP
#define AEYON3D_RESOURCECACHE_HPP

#include <unordered_map>
#include "Resource.hpp"

namespace aeyon
{
	template<typename T, typename U>
	class ResourceCache
	{
	private:
		std::unordered_map<std::string, Resource<T>> m_resources;

		virtual std::unique_ptr<T> create(const U& metadata) = 0;

	public:
		Resource<T> load(const std::string& name, const U& metadata);
	};
}

namespace aeyon
{
	template <typename T, typename U>
	Resource<T> ResourceCache<T, U>::load(const std::string& name, const U& metadata)
	{
        auto it = m_resources.find(name);

        if (it == m_resources.end())
        {
            m_resources.emplace(name, create(metadata));
        }
        
		return m_resources[name];
	}
}

#endif //AEYON3D_RESOURCECACHE_HPP
