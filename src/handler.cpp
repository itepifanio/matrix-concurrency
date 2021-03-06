#include "../include/handler.h"
#include "../include/matrix.h"
#include <chrono>
#include <string>
#include <thread>
#include <iostream>

Handler::Handler(std::string matrixSize, std::string type)
{
    this->matrixSize = matrixSize;
    this->type = type;
}

void Handler::execute()
{
    Matrix a, b, c;

    a.readFromFile(this->getMatrixFileName("A"));
    b.readFromFile(this->getMatrixFileName("B"));
    
    auto start = std::chrono::system_clock::now();
    
    if (type == "S")
    {
        c.multiply(std::ref(a), std::ref(b));
    }
    else
    {
        const unsigned int numThreads = 4;
        std::thread threads[numThreads];

        c.loadMatrixWithZeros(a.matrix.size()); // workaround this should be done in a constructor, right?

        for (int i = 0; (unsigned) i < numThreads; ++i)
        {
            threads[i] = std::thread(&Matrix::multiplyWithThreads, &c, std::ref(a), std::ref(b), i, numThreads);
        }

        for (int i = 0; (unsigned) i < numThreads; i++)
        {
            threads[i].join();
        }
    }
    
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << duration.count() << std::endl;
    c.writeMatrix(this->getMatrixFileName("C"));
}

std::string Handler::getMatrixFileName(std::string letter)
{
    return "./data/" + letter + this->matrixSize + "x" + this->matrixSize + ".txt";
}