#pragma once

#include <optional>

template <typename T>
class Optional
{
public:
    Optional()
        : m_Optional(std::nullopt) {}
    Optional(T &&value)
        : m_Optional(std::move(value)) {}

    static Optional<T> Empty() { return Optional(); }

    bool IsEmpty() const { return !m_Optional.has_value(); }
    bool HasValue() const { return m_Optional.has_value(); }

    const T &GetValue() const { return m_Optional.value(); }
    T &GetValue() { return m_Optional.value(); }

private:
    std::optional<T> m_Optional;
};
