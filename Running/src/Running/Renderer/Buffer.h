#pragma once

namespace Running
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float: return sizeof(float);
			case ShaderDataType::Float2: return 2 * sizeof(float);
			case ShaderDataType::Float3: return 3 * sizeof(float);
			case ShaderDataType::Float4: return 4 * sizeof(float);
			case ShaderDataType::Mat3: return 3 * 3 * sizeof(float);
			case ShaderDataType::Mat4: return 4 * 4 * sizeof(float);
			case ShaderDataType::Int: return sizeof(int);
			case ShaderDataType::Int2: return 2 * sizeof(int);
			case ShaderDataType::Int3: return 3 * sizeof(int);
			case ShaderDataType::Int4: return 4 * sizeof(int);
			case ShaderDataType::Bool: return sizeof(bool);
		}

		RUNNING_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;

		BufferElement(const std::string& name, ShaderDataType type) :
			Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0)
		{

		}
	};

	class BufferLayout
	{
	public:
		inline const std::vector<BufferElement>& GetElements() const { return _elements; }

	private:
		std::vector<BufferElement> _elements;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};
}
