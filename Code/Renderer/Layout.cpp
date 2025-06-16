#include "Renderer/Layout.h"

void BufferLayout::AddElement(const std::string &name, BufferDataType type)
{
    BufferElement element(name, type);
    element.m_Offset = m_Offset;

    m_Stride += GetSize(type);
    m_Offset += GetSize(type);

    m_Elements.Add(element);
}

unsigned int BufferLayout::GetComponents(BufferDataType type)
{
    switch (type)
    {
    case BufferDataType::Int:
        return 1;
    case BufferDataType::Int2:
        return 2;
    case BufferDataType::Int3:
        return 3;
    case BufferDataType::Int4:
        return 4;
    case BufferDataType::UInt:
        return 1;
    case BufferDataType::Float:
        return 1;
    case BufferDataType::Float2:
        return 2;
    case BufferDataType::Float3:
        return 3;
    case BufferDataType::Float4:
        return 4;
    case BufferDataType::Double:
        return 1;
    case BufferDataType::Bool:
        return 1;
    case BufferDataType::Mat3:
        return 3;
    case BufferDataType::Mat4:
        return 4;
    };

    return 0;
}

unsigned int BufferLayout::GetSize(BufferDataType type)
{
    switch (type)
    {
    case BufferDataType::Int:
        return 4;
    case BufferDataType::Int2:
        return 4 * 2;
    case BufferDataType::Int3:
        return 4 * 3;
    case BufferDataType::Int4:
        return 4 * 4;
    case BufferDataType::UInt:
        return 4;
    case BufferDataType::Float:
        return 4;
    case BufferDataType::Float2:
        return 4 * 2;
    case BufferDataType::Float3:
        return 4 * 3;
    case BufferDataType::Float4:
        return 4 * 4;
    case BufferDataType::Double:
        return 8;
    case BufferDataType::Bool:
        return 1;
    case BufferDataType::Mat3:
        return 4 * 3 * 3;
    case BufferDataType::Mat4:
        return 4 * 4 * 4;
    };

    return 0;
}
