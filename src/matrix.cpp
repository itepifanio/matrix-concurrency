#include "../include/matrix.h"
#include <string>
#include <iostream>
#include <fstream>

void Matrix::readFromFile(std::string filename)
{
    std::string line;
    std::ifstream myfile(filename);
    if (myfile.is_open())
    {
        while (std::getline(myfile, line))
        {
            std::cout << line << '\n';
        }
        myfile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}