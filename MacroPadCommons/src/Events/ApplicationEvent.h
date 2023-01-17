#pragma once

#include "MacroPadCommons.h"

namespace MacroPad {
	class CORE_DLL WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height) :
			m_width(width), m_height(height) {}

		inline unsigned int GetWidth() const { return m_width; }
		inline unsigned int GetHeight() const { return m_height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowsResizedEvent : " << m_width << " , " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_width, m_height;
	};

	class CORE_DLL WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() = default;

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowClosedEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CORE_DLL WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(unsigned int x, unsigned int y)
			: m_posx(x), m_posy(y) {}

		inline unsigned int GetX() const { return m_posx; }
		inline unsigned int GetY() const { return m_posy; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMovedEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_posx, m_posy;
	};

	class CORE_DLL WindowFocused : public Event
	{
		WindowFocused() = default;

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowFocusedEvent";
			return ss.str();
		}
	
		EVENT_CLASS_TYPE(WindowFocused)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CORE_DLL WindowLostFocus : public Event
	{
		WindowLostFocus() = default;

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowLostFocusEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowLostFocus)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}