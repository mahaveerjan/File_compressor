#include "readfile.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

ReadFile::ReadFile(const std::string& filename) :filename(filename) {// yep gott the intialization list concept
    file.open(filename);
    if(!file.is_open()){
        std::cerr <<"Error could not open file" << filename << std::endl;
    }
}

std:: vector <std:: string > ReadFile::readLines(){ // in this function we are reading the file into vetor(study vector also) 
    std:: vector<std::string> lines;
    std:: string line;

    while(std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

void ReadFile::close(){
    if(file.is_open()){
        file.close();
    }
}