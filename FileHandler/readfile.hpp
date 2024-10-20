#ifndef READFILE_HPP
#define READFILE_HPP

#include <fstream>
#include <string>
#include <vector>

class ReadFile
{
public:
    ReadFile(const std::string &filemname);

    std::vector<std::string> readLines();

    void close();

private:
    std::ifstream file;
    std::string filename;
};
#endif