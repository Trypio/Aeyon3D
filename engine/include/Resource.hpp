//
//
//

#ifndef AEYON3D_RESOURCEHANDLE_HPP
#define AEYON3D_RESOURCEHANDLE_HPP

#include <Types.hpp>
#include <memory>
#include <stdexcept>

namespace aeyon
{
	template <typename T>
	struct ResourceData
	{
		std::string name;
		std::unique_ptr<T> resource;
		bool isValid;

		ResourceData() : name(""), resource(nullptr), isValid(false)
		{
		}

		ResourceData(std::string name, std::unique_ptr<T> resource)
		: name(std::move(name)), resource(std::move(resource)), isValid(true)
		{
		}
	};

    // TODO:
    /*
     * ResourceMetadata
     *
     * Resource<Texture> tex = new Resource<Texture>(path, new TextureMetadata(...));
     *
     * ... oder später TextureMetadata von AssetManager laden lassen
     * Resource<Texture> tex = new Resource<Texture>(path);
     *
     * Resource<T> um async flag erweitern
     *
     */

	template<typename T>
	class Resource
	{
	private:
		std::shared_ptr<ResourceData<T>> m_data;

	public:
		Resource() : m_data(std::make_shared<ResourceData<T>>()) {}
		explicit Resource(std::shared_ptr<ResourceData<T>> data) : m_data(data) {}

		T* get();
		const T* get() const;
		T& operator*();
		const T& operator*() const;
		T* operator->();
		const T* operator->() const;
		bool isValid() const;
	};
}

template<typename T>
T* aeyon::Resource<T>::get()
{
	if (!m_data->isValid)
	{
		throw std::runtime_error("Resource is invalid!");
	}

	return m_data->resource.get();
}

template<typename T>
const T* aeyon::Resource<T>::get() const
{
	if (!m_data->isValid)
	{
		throw std::runtime_error("Resource is invalid!");
	}

	return m_data->resource.get();
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
	return m_data->isValid;
}


#endif //AEYON3D_RESOURCEHANDLE_HPP
