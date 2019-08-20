#pragma once

#include <Running.h>

class ExampleLayer : public Running::Layer
{
public:
	ExampleLayer() :
		Layer("Example")
	{
	}
};

class Sandbox : public Running::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Running::ImGuiLayer());
	}

	~Sandbox() {}
};

Running::Application* Running::CreateApplication()
{
	return new Sandbox();
}
