#pragma once

namespace Running
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		// uniquely identifies the object inside OpenGL
		uint32_t _rendererId;
	};
}
