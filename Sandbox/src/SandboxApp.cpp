#pragma once

#include <Running.h>

class Sandbox : public Running::Application
{
public:
	Sandbox() {}
	~Sandbox() {}

};

Running::Application* Running::CreateApplication()
{
	RUNNING_CLIENT_INFO("AHoj!");
	return new Sandbox();
}
