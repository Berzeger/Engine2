#pragma once

#include "pch.h"

#include "Running/Events/Event.h"

namespace Running
{
	struct WindowProperties
	{
		std::string Title;
		unsigned Width;
		unsigned Height;

		WindowProperties(const std::string& title = "Running Engine", unsigned width = 1280, unsigned height = 720) :
			Title(title),
			Width(width),
			Height(height)
		{ }
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned GetWidth() const = 0;
		virtual unsigned GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());
	};
}
