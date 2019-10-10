#pragma once

#include "Running/Renderer/Buffer.h"

namespace Running
{
	class OpenGlVertexBuffer : public VertexBuffer
	{
	public:
		OpenGlVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGlVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t _rendererId;
	};

	class OpenGlIndexBuffer : public IndexBuffer
	{
	public:
		OpenGlIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGlIndexBuffer();

		virtual uint32_t GetCount() const override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t _rendererId;
		uint32_t _count;
	};
}
