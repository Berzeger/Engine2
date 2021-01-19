#pragma once

#include "ExampleLayer.h"
#include <Running/EntryPoint.h>

class Sandbox : public Running::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Running::Application* Running::CreateApplication()
{
	return new Sandbox();
}
