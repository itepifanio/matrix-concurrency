#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <string>
#include <vector>

class Matrix{
    public:
        void readFromFile(std::string filename);
        void print();
        std::vector<std::vector<int>> matrix;
        void multiply(Matrix a, Matrix b); // override multiplication operator sucks
        void multiplyWithThreads(Matrix a, Matrix b, int numThread, unsigned int numTotalThreads);
        void loadInsideMatrix(int size);
};

#endif