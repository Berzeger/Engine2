#pragma once

#include "Event.h"
#include "../EnumBitwiseOperations.h"
#include <sstream>

namespace Running
{
	// -----------------------------------------------
	class RUNNING_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return _keyCode; }

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)

	protected:
		KeyEvent(int keycode) :
			_keyCode(keycode)
		{}

		int _keyCode;
	};

	// -----------------------------------------------
	class RUNNING_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) :
			KeyEvent(keycode),
			_repeatCount(repeatCount) 
		{ }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _keyCode << " (" << _repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int _repeatCount;
	};

	// -----------------------------------------------
	class RUNNING_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) :
			KeyEvent(keycode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << _keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	private:
		int _repeatCount;
	};
}
