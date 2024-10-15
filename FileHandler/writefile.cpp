#include<fstream>
#include "writefile.hpp"
#include <iostream>
#include <vector>

WriteFile::WriteFile(const std::string& filename) :filename(filename) {
    file.open(filename);
    if(!file.is_open()){
        std::cerr<<"Error: couldn't open file" <<filename <<std::endl;

    }
}

WriteFile::~WriteFile(){
    if(file.is_open()){
        file.close();
    }
}

void WriteFile::writeLine(const std::string& line) {
    if(!file.is_open()){
        std::cerr<<"Error File is not open for writing" <<std:: endl;
        return;
    }
    file<< line <<'\n';
}