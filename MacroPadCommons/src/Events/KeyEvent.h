#pragma once

#include "mppch.h"

#include "MacroPadCommons.h"

namespace MacroPad {
	class CORE_DLL KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_keycode; }
	
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode) :
			m_keycode(keycode) {}

		int m_keycode;
	};

	class CORE_DLL KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeat_count) :
			KeyEvent(keycode), m_repeat_count(repeat_count) {}

		inline int GetRepeatCount() const { return m_repeat_count; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent : " << m_keycode << " (" << m_repeat_count << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_repeat_count;
	};

	class CORE_DLL KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode, int repeat_count) :
			KeyEvent(keycode) {}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent : " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class CORE_DLL KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}