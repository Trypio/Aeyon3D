//
//
//

#ifndef AEYON3D_EVENTSYSTEM_HPP
#define AEYON3D_EVENTSYSTEM_HPP

#include <functional>
#include <vector>
#include <unordered_map>
#include "Event.hpp"
#include <typeindex>
#include <memory>

namespace aeyon
{
	/**
	 * A publisher/subscriber system that handles the propagation of events within the engine.
	 */
	class EventSystem
	{
	public:
		template <typename EventType>
		using Callback = std::function<void(const EventType&)>;

	private:
		class ICallbackWrapper
		{
		};

		template <typename EventType>
		class CallbackWrapper : public ICallbackWrapper
		{
		private:
			Callback<EventType> m_callback;

		public:
			explicit CallbackWrapper(Callback<EventType> callback)
					: m_callback(callback)
			{
			}

			void operator() (const EventType& event)
			{
				m_callback(event);
			}
		};

		using CallbackList = std::vector<std::unique_ptr<ICallbackWrapper>>;
		using CallbackTable = std::unordered_map<std::type_index, CallbackList>;

		CallbackTable m_callbackTable;

	public:
		void update();

		template <typename EventType, typename CallbackType>
		void subscribe(CallbackType callback)
		{
			CallbackList& callbackList = m_callbackTable[typeid(EventType)];
			callbackList.push_back(std::make_unique<CallbackWrapper<EventType>>(callback));
		}

		template <typename EventType>
		void publish(const EventType& event)
		{
			auto it = m_callbackTable.find(typeid(EventType));

			if (it == m_callbackTable.end())
			{
				return;
			}

			for (auto& wrapper : it->second)
			{
				(*static_cast<CallbackWrapper<EventType>*>(wrapper.get()))(event);
			}
		}
	};
}


#endif //AEYON3D_EVENTSYSTEM_HPP
