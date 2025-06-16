#pragma once

#include <algorithm>
#include <string>
#include <variant>

class [[nodiscard]] Error
{
public:
    Error(const std::string &message)
        : m_Message(message) {}

    const std::string &GetMessage() const { return m_Message; }
    std::string GetMessage() { return m_Message; }

    operator std::string() const { return m_Message; }
    operator const char *() const { return m_Message.c_str(); }

private:
    std::string m_Message;
};

template <typename R, typename E = Error>
class [[nodiscard]] Result
{
public:
    Result(R result)
        : m_Value(std::move(result)) {}
    Result(E error)
        : m_Value(std::move(error)) {}

    static Result<R, E> Ok(R result) { return Result(result); }
    static Result<R, E> Error(E error) { return Result(error); }
    static Result<R, E> Error(const std::string &error) { return Result(E(error)); }

    bool IsOk() const { return std::holds_alternative<R>(m_Value); }
    bool IsError() const { return !IsOk(); }

    const R &GetValue() const { return std::get<R>(m_Value); }
    R &GetValue() { return std::get<R>(m_Value); }

    const E &GetError() const { return std::get<E>(m_Value); }
    E &GetError() { return std::get<E>(m_Value); }

private:
    std::variant<R, E> m_Value;
};

template <typename E>
class Result<void, E>
{
public:
    Result()
        : m_Value(std::monostate()) {}
    Result(E error)
        : m_Value(std::move(error)) {}

    static Result<void, E> Ok() { return Result(); }
    static Result<void, E> Error(E error) { return Result(error); }
    static Result<void, E> Error(const std::string &error) { return Result(E(error)); }

    bool IsOk() const { return std::holds_alternative<std::monostate>(m_Value); }
    bool IsError() const { return !IsOk(); }

    const E &GetError() const { return std::get<E>(m_Value); }
    E &GetError() { return std::get<E>(m_Value); }

private:
    std::variant<std::monostate, E> m_Value;
};
