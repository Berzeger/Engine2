#pragma once

#include "Running/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Running
{
	class OpenGlShader : public Shader
	{
	public:
		OpenGlShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGlShader();

		virtual void Bind() const override;
		virtual void Unbind() const override; 

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2 vec);
		void UploadUniformFloat3(const std::string& name, const glm::vec3 vec);
		void UploadUniformFloat4(const std::string& name, const glm::vec4 vec);

	private:
		// uniquely identifies the object inside OpenGL
		uint32_t _rendererId;
	};
}
