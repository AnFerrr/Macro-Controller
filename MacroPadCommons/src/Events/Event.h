#pragma once

#include "mppch.h"

#include <functional>
#include "MacroPadCommons.h"

namespace MacroPad {
	enum class EventType
	{
		None = 0,
		WindowClosed, WindowResized, WindowFocus, WindowLostFocused, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class CORE_DLL Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const = 0;

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) :
			m_event(event) {}

		template<typename T, typename F>
		bool Dispatch(EventFn<T> func)
		//bool Dispatch(const F& func) 
		{
			if (m_event.GetEventType() == T::GetStaticType())
			{
				//m_event.m_handled |= func(static_cast<T&>(m_event));
				m_event.m_handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}