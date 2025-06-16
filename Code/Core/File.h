#pragma once

#include <fstream>
#include <string>

class File
{
public:
    File(const std::string &path);
    ~File();

    std::string ReadAll();

private:
    std::string m_Path;
    std::fstream m_Stream;
};
