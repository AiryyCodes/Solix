#pragma once

#include "Core/List.h"
#include <cstddef>
#include <string>

enum class BufferDataType
{
    Int,
    Int2,
    Int3,
    Int4,
    UInt,
    Float,
    Float2,
    Float3,
    Float4,
    Double,
    Bool,
    Mat3,
    Mat4,
};

class BufferElement
{
public:
    BufferElement(const std::string &name, BufferDataType type)
        : m_Name(name), m_Type(type) {}

    const std::string &GetName() const { return m_Name; }
    BufferDataType GetType() const { return m_Type; }

    size_t GetOffset() const { return m_Offset; }

    friend class BufferLayout;

private:
    std::string m_Name;
    BufferDataType m_Type;

    size_t m_Offset = 0;
};

class BufferLayout
{
public:
    void AddElement(const std::string &name, BufferDataType type);

    unsigned int GetComponents(BufferDataType type) const;
    unsigned int GetSize(BufferDataType type) const;

    const List<BufferElement> &GetElements() const { return m_Elements; }

    size_t GetStride() const { return m_Stride; }

private:
    List<BufferElement> m_Elements;

    unsigned int m_Stride = 0;
    size_t m_Offset = 0;
};
