#ifndef WRITEFILE
#define WRITEFILE

#include<fstream>
#include <fstream>
#include <iostream>

class WriteFile{
    //this is claas
    public:
    WriteFile(const std::string &filename);
    ~WriteFile();
    void writeLine(const std::string &line);

    //this is method
    //

    private :
    std:: string filename;
    std::ofstream file;

};

#endif