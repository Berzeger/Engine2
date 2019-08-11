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
	return new Sandbox();
}
