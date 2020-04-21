#pragma once
#include "Running/Core.h"
#include "Running/Events/Event.h"
#include "Running/Core/Timestep.h"

namespace Running
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep deltaTime) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

	private:
		std::string _debugName;
	};
}
