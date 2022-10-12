//
//
//

#ifndef AEYON3D_RESOURCEHANDLE_HPP
#define AEYON3D_RESOURCEHANDLE_HPP

#include <memory>
#include "UUID.hpp"

namespace aeyon
{
    template<typename T>
	class Resource
	{
    private:
        std::shared_ptr<T> m_data;
        UUID m_guid;

    public:
        Resource();
        explicit Resource(std::shared_ptr<T> data);

        explicit operator bool() const;

        template <typename U>
        friend bool operator==(const Resource<U>& lhs, const Resource<U>& rhs);
        template <typename U>
        friend bool operator!=(const Resource<U>& lhs, const Resource<U>& rhs);

        T* get();
		const T* get() const;
		T& operator*();
		const T& operator*() const;
		T* operator->();
		const T* operator->() const;
	};
}

template<typename T>
aeyon::Resource<T>::Resource() : m_data(nullptr)
{
}

template<typename T>
aeyon::Resource<T>::Resource(std::shared_ptr<T> data) : m_data(std::move(data)), m_guid(UUID::generate())
{
}

template<typename T>
T* aeyon::Resource<T>::get()
{
	return m_data.get();
}

template<typename T>
const T* aeyon::Resource<T>::get() const
{
	return m_data.get();
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

template<typename T>
aeyon::Resource<T>::operator bool() const
{
    return m_data;
}

template<typename T>
bool operator==(const aeyon::Resource<T>& lhs, const aeyon::Resource<T>& rhs)
{
    return lhs.m_data == rhs.m_data;
}

template<typename T>
bool operator!=(const aeyon::Resource<T>& lhs, const aeyon::Resource<T>& rhs)
{
    return !(rhs == lhs);
}


#endif //AEYON3D_RESOURCEHANDLE_HPP
