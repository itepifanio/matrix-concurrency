#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <string>
#include <vector>

class Matrix{
    public:
        void readFromFile(std::string filename);
        void print();
        std::vector<std::vector<int>> matrix;
};

#endif