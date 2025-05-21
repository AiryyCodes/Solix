#pragma once

#include <algorithm>
#include <initializer_list>
#include <vector>

template <typename T>
class List
{
public:
    List()
        : m_List() {}
    List(std::initializer_list<T> items)
        : m_List(items) {}

    void Add(const T &value) { m_List.push_back(value); }
    void AddAt(int index, const T &value) { m_List.insert(m_List.begin() + index, value); }

    T &Get(int index) { return m_List.at(index); }
    const T &Get(int index) const { return m_List.at(index); }

    void Remove(const T &value)
    {
        auto it = std::find(value);
        if (it == m_List.end())
            return;

        m_List.erase(it);
    }
    void RemoveAt(int index) { m_List.erase(m_List.begin() + index); }

    const T *GetData() const { return m_List.data(); }

    int GetSize() const { return sizeof(T) * m_List.size(); }
    int GetLength() const { return m_List.size(); }

    typename std::vector<T>::iterator begin() { return m_List.begin(); }
    typename std::vector<T>::iterator end() { return m_List.end(); }

    typename std::vector<T>::const_iterator begin() const { return m_List.begin(); }
    typename std::vector<T>::const_iterator end() const { return m_List.end(); }

private:
    std::vector<T> m_List;
};
