#pragma once

#include "Event.h"
#include <sstream>

namespace Running
{
	class RUNNING_API WindowResizeEvent : Event
	{
	public:
		WindowResizeEvent(unsigned width, unsigned height) :
			_width(width),
			_height(height)
		{
		}

		inline unsigned GetWidth() const { return _width; }
		inline unsigned GetHeight() const { return _height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowsResizeEvent: " << _width << ", " << _height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType.WindowResize)
		EVENT_CLASS_CATEGORY(EventCategory.EventCategoryApplication)

	private:
		unsigned _width;
		unsigned _height;
	};
}
