#include "Core/File.h"
#include "Core/Logger.h"

#include <fstream>
#include <string>

File::File(const std::string &path)
    : m_Path(path)
{
    m_Stream = std::fstream();
    m_Stream.open(path);
    if (m_Stream.fail())
    {
        LOG_ERROR("Failed to open file '{}'", path);
        return;
    }
}

File::~File()
{
    m_Stream.close();
}

std::string File::ReadAll()
{
    if (!m_Stream.is_open())
    {
        m_Stream.open(m_Path);
    }

    std::string output;

    std::string line;
    while (std::getline(m_Stream, line))
    {
        output += line + "\n";
    }

    return output;
}
