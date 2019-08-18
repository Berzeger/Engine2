#pragma once
#include "Running/Core.h"
#include "Running/Events/Event.h"

namespace Running
{
	class RUNNING_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

	private:
		std::string _debugName;
	};
}
