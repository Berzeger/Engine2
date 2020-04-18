#include "pch.h"
#include "OpenGlVertexArray.h"

#include <glad/glad.h>

namespace Running
{

	static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Running::ShaderDataType::Float:
		case Running::ShaderDataType::Float2:
		case Running::ShaderDataType::Float3:
		case Running::ShaderDataType::Float4:
		case Running::ShaderDataType::Mat3:
		case Running::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Running::ShaderDataType::Int:
		case Running::ShaderDataType::Int2:
		case Running::ShaderDataType::Int3:
		case Running::ShaderDataType::Int4:
			return GL_INT;
		case Running::ShaderDataType::Bool:
			return GL_BOOL;
		}

		return 0;
	}

	OpenGlVertexArray::OpenGlVertexArray()
	{
		glCreateVertexArrays(1, &_rendererId);
	}

	OpenGlVertexArray::~OpenGlVertexArray()
	{
		glDeleteVertexArrays(1, &_rendererId);
	}
	
	void OpenGlVertexArray::Bind() const
	{
		glBindVertexArray(_rendererId);
	}

	void OpenGlVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGlVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		RUNNING_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		Bind();
		vertexBuffer->Bind();	

		uint32_t index = 0;
		const BufferLayout& layout = vertexBuffer->GetLayout();

		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGlBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		_vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGlVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();

		_indexBuffer = indexBuffer;
	}
}
