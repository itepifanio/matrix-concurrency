#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <string>
#include <vector>

class Matrix{
    private:
        std::vector<int> matrix;
    public:
        void readFromFile(std::string filename);
};

#endif