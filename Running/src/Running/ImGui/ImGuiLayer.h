#pragma once

#include "Running/Layer.h"

namespace Running
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnUpdate() override;
		void OnEvent(Event& e) override;
		void OnAttach() override;
		void OnDetach() override;
	};
}
