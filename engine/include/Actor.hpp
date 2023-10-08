//
// Created by thors on 05.10.2020.
//

#ifndef AEYON3D_ACTOR_HPP
#define AEYON3D_ACTOR_HPP

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>
#include <utility>
#include "Transform.hpp"

namespace aeyon
{
	class Actor
	{
	private:
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
		std::string m_name;
        bool m_isActive;

	public:
		Actor();
		explicit Actor(std::string name);
        Actor(const Actor& other);
        Actor(Actor&& other) noexcept;
        Actor& operator=(Actor other);

        friend void swap(Actor& first, Actor& second) noexcept;

        void setName(std::string name);
        void setActive(bool isActive);

        const std::string& getName() const;
        bool isActive() const;

        const Transform* getTransform() const;
        Transform* getTransform();

		template <typename T, typename... Args>
		T* addComponent(Args ...args)
		{
			return static_cast<T*>((m_components[typeid(T)] = std::make_unique<T>(this, std::forward<Args>(args)...)).get());
		}

		template <typename T>
		void removeComponent()
		{
			m_components.erase(typeid(T));
		}

		template <typename T>
		const T* getComponent() const
		{
			auto it = m_components.find(typeid(T));
			if (it == m_components.end())
			{
				return nullptr;
			}
			else
			{
				return static_cast<T*>(it->second.get());
			}
		}

		template <typename T>
		T* getComponent()
		{
			return const_cast<T*>(std::as_const(*this).getComponent<T>());
		}

		template <typename T>
		bool hasComponent() const
		{
			return m_components.find(typeid(T)) != m_components.end();
		}
	};
}

#endif //AEYON3D_ACTOR_HPP
