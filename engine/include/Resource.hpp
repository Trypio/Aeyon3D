//
//
//

#ifndef AEYON3D_RESOURCEHANDLE_HPP
#define AEYON3D_RESOURCEHANDLE_HPP

#include <Types.hpp>
#include <memory>

namespace aeyon
{
	template <typename T>
	class ResourceCache;

	template<typename T>
	class Resource
	{
	private:
		ResourceID m_id;
		ResourceCache<T>* m_cache;

		std::shared_ptr<T> m_managedData;

	public:
		Resource();
		Resource(ResourceID id, ResourceCache<T>* m_cache);
		explicit Resource(std::shared_ptr<T> ptr);

		T* get();
		const T* get() const;
		T& operator*();
		const T& operator*() const;
		T* operator->();
		const T* operator->() const;
		bool isValid() const;
	};
}

#include "ResourceCache.hpp"

template <typename T>
aeyon::Resource<T>::Resource()
: m_id(0), m_cache(nullptr), m_managedData(nullptr)
{
}

template <typename T>
aeyon::Resource<T>::Resource(aeyon::ResourceID id, aeyon::ResourceCache<T>* m_cache)
: m_id(id), m_cache(m_cache), m_managedData(nullptr)
{
}

template <typename T>
aeyon::Resource<T>::Resource(std::shared_ptr<T> ptr)
: m_id(0), m_cache(nullptr), m_managedData(std::move(ptr))
{
}

template<typename T>
T* aeyon::Resource<T>::get()
{
	return m_cache ? m_cache->get(m_id) : m_managedData.get();
}

template<typename T>
const T* aeyon::Resource<T>::get() const
{
	return m_cache ? m_cache->get(m_id) : m_managedData.get();
}

template<typename T>
T& aeyon::Resource<T>::operator*()
{
	return *get();
}

template<typename T>
const T& aeyon::Resource<T>::operator*() const
{
	return *get();
}

template<typename T>
T* aeyon::Resource<T>::operator->()
{
	return get();
}

template<typename T>
const T* aeyon::Resource<T>::operator->() const
{
	return get();
}

template <typename T>
bool aeyon::Resource<T>::isValid() const
{
	return m_cache ? true : (m_managedData ? true : false);
}


#endif //AEYON3D_RESOURCEHANDLE_HPP
