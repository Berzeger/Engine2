#pragma once

#include "Running/Layer.h"

namespace Running
{
	class RUNNING_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnImGuiRender() override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float _time;
	};
}
