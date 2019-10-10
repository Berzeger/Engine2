#pragma once

namespace Running
{
	enum class RendererApi
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererApi GetApi() { return s_rendererApi; }
	private:
		static RendererApi s_rendererApi;
	};
}
