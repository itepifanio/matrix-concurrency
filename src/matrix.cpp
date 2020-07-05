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
        std::string buffer; // buffer to safe the whole number of the txt
        while (myfile.get(c))
        {
            if (c != ' ' && c != '\n')
            {
                buffer.push_back(c);
            }

            if (c == ' ')
            {
                temp.push_back(std::stoi(buffer));
                buffer = "";
            }

            if (c == '\n')
            {
                buffer = "";
                this->matrix.push_back(temp);
                temp.clear();
            }
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
    unsigned int i, j, k;
    unsigned int matrixSize = a.matrix.size();

    this->loadMatrixWithZeros(matrixSize);

    for (i = 0; i < matrixSize; i++)
    {
        for (j = 0; j < matrixSize; j++)
        {
            for (k = 0; k < matrixSize; k++)
            {
                this->matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
            }
        }
    }
}

/** Interpreter the matrix as an array and do your thing */
void Matrix::multiplyWithThreads(Matrix a, Matrix b, int numThread, unsigned int numTotalThreads = 4)
{
    unsigned int matrixSize = a.matrix.size();
    // calculates the part that this current thread will multiply
    unsigned int numElements = (matrixSize * matrixSize);
    // Our matrixes are always divided by 4 so we don't really care about rest of this division
    unsigned int numOperations = numElements / numTotalThreads;

    unsigned int begin, end;

    begin = numOperations * numThread;
    end = (numOperations * (numThread + 1));

    for (unsigned int i = begin; i < end; ++i)
    {
        int row = i % matrixSize;
        int col = i / matrixSize;
        int r = 0;
        for (unsigned int k = 0; k < matrixSize; ++k)
        {
            r += a.matrix[row][k] * b.matrix[k][col];
        }
        this->matrix[row][col] = r;
    }
}

void Matrix::loadMatrixWithZeros(int size)
{
    std::vector<int> temp;
    unsigned int i, j;
    for (i = 0; i < (unsigned)size; i++)
    {
        for (j = 0; j < (unsigned)size; j++)
        {
            temp.push_back(0);
        }
        this->matrix.push_back(temp);
    }
}

void Matrix::writeMatrix(std::string filename)
{
    std::ofstream myfile;

    unsigned int i, j;
    unsigned int matrixSize = this->matrix.size();

    myfile.open(filename);

    myfile << (std::to_string(matrixSize) + " " + std::to_string(matrixSize)) << " \n";

    for (i = 0; i < matrixSize; i++)
    {
        for (j = 0; j < matrixSize; j++)
        {
            myfile << (std::to_string(this->matrix[i][j]) + " ");
        }
        myfile << "\n";
    }

    myfile.close();
}