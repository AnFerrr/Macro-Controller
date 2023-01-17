#pragma once

#include "MacroPadCommons.h"

namespace MacroPad {
	class CORE_DLL MouseMovedEvent : public Event
	{
		MouseMovedEvent(const float x, const float y) :
			m_posex(x), m_posey(y) {}

		float GetX() const { return m_posex; }
		float GetY() const { return m_posey; }
	
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: " << m_posex << ", " << m_posey;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_posex, m_posey;
	};

	class CORE_DLL MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_x_offset(xOffset), m_y_offset(yOffset) {}

		float GetXOffset() const { return m_x_offset; }
		float GetYOffset() const { return m_y_offset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_x_offset << ", " << m_y_offset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_x_offset, m_y_offset;
	};

	class CORE_DLL MouseButtonEvent : public Event
	{
	public:
		unsigned int GetMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(const unsigned int button) :
			m_button(button) {};

		unsigned int m_button;
	};

	class CORE_DLL MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const unsigned int button) :
			MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent : " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class CORE_DLL MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const unsigned int button) :
			MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent : " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}