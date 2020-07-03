#include "../include/matrix.h"
#include <string>
#include <iostream>
#include <fstream>
#include <thread>

void Matrix::readFromFile(std::string filename)
{
    std::string line;
    std::ifstream myfile(filename);
    std::getline(myfile, line); // ignore file header

    if (myfile.is_open())
    {
        std::vector<int> temp;
        char c;
        int i = 0, j = 0;
        while (myfile.get(c))
        {
            if (c != ' ' && c != '\n')
            {
                temp.push_back(c - '0'); // workaround to convert to int
            }

            if (c == '\n')
            {
                this->matrix.push_back(temp);
                temp.clear();
                j++;
            }

            i++;
        }
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}

void Matrix::print()
{
    for (unsigned int i = 0; i < this->matrix.size(); i++)
    {
        for (unsigned j = 0; j < this->matrix.size(); j++)
        {
            std::cout << this->matrix[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

void Matrix::multiply(Matrix a, Matrix b)
{
    std::vector<int> temp;
    unsigned int i, j, k;
    for (i = 0; i < a.matrix.size(); i++)
    {
        for (j = 0; j < b.matrix.size(); j++)
        {
            temp.push_back(0);
        }
        this->matrix.push_back(temp);
    }

    for (i = 0; i < a.matrix.size(); i++)
    {
        for (j = 0; j < b.matrix.size(); j++)
        {
            for (k = 0; k < a.matrix.size(); k++)
            {
                this->matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
            }
        }
    }
}

/** Interpreter the matrix as an array and do your thing */
void Matrix::multiplyWithThreads(Matrix a, Matrix b, int numThread, unsigned int numTotalThreads = 4)
{
    std::cout << numThread << std::endl;
    unsigned int matrixSize = a.matrix.size();
    // calculates the part that this current thread will multiply
    unsigned int numElements = (matrixSize * matrixSize);
    // Our matrixes are always divided by 4 so we don't really care about rest of this division
    unsigned int numOperations = numElements / numTotalThreads;

    unsigned int begin, end;

    begin = numOperations * numThread;
    end = numOperations * numThread + 1;

    for (unsigned int i = begin; i < end; i++)
    {
        int row = i % matrixSize;
        int col = i / matrixSize;
        int r;
        for (unsigned int k = 0; i < matrixSize; ++i)
        {
            r += a.matrix[row][k] * b.matrix[i][col];
        }
        std::cout << r << std::endl;
        this->matrix[row][col] = r;
    }
}

void Matrix::loadInsideMatrix(int size)
{
    std::vector<int> temp;
    unsigned int i, j;
    for (i = 0; i < (unsigned) size; i++)
    {
        for (j = 0; j < (unsigned) size; j++)
        {
            temp.push_back(0);
        }
        this->matrix.push_back(temp);
    }
}