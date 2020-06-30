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
        std::vector<int> temp;
        char c;
        int i = 0, j = 0;
        while (myfile.get(c))
        {
            if (c != ' ' && c != '\n')
            {
                temp.push_back(c - '0');
            }

            if (c == '\n')
            {
                this->matrix.push_back(temp);
                temp.clear();
                j++;
            }

            i++;
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}

void Matrix::print()
{
    for (unsigned int i = 0; i < this->matrix.size(); i++)
    {
        for (unsigned j = 0; j < this->matrix[i].size(); j++)
        {
            std::cout << this->matrix[i][j] << " ";
        }

        std::cout << std::endl;
    }
}