#pragma once

#include "Running/Events/KeyEvent.h"
#include "Running/Events/MouseEvent.h"
#include "Running/Events/ApplicationEvent.h"
#include "Running/Layer.h"

namespace Running
{
	class RUNNING_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnUpdate() override;
		void OnEvent(Event& e) override;
		void OnAttach() override;
		void OnDetach() override;

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		float _time;
	};
}
