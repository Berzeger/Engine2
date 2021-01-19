#pragma once

#include <Running.h>

class ExampleLayer : public Running::Layer
{
public:
	ExampleLayer();
	virtual void OnUpdate(Running::Timestep dt) override;
	virtual void OnImGuiRender() override;

private:
	std::shared_ptr<Running::Shader> _shader;
	std::shared_ptr<Running::Shader> _flatColorShader;
	std::shared_ptr<Running::VertexArray> _triangleVertexArray;
	std::shared_ptr<Running::VertexArray> _squareVertexArray;

	Running::OrthographicCamera _camera;
	glm::vec3 _cameraPosition;
	float _cameraMoveSpeed = 10.0f;

	float _cameraRotation = 0.0f;
	float _cameraRotationSpeed = 200.0f;

	glm::vec3 _squarePosition;
	float _squareMoveSpeed = 10.0f;

	glm::vec4 _redSquareColor;
	glm::vec4 _blueSquareColor;
};