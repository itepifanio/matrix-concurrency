#include "../include/handler.h"
#include "../include/matrix.h"
#include <string>
#include <thread>

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

    if (type == "C")
    {
        c.multiply(a, b);
    }
    else
    {
        const unsigned int numThreads = 4;
        std::thread threads[numThreads];

        c.loadMatrixWithZeros(a.matrix.size()); // workaround this should be done in a constructor, right?

        for (int i = 0; (unsigned) i < numThreads; ++i)
        {
            threads[i] = std::thread(&Matrix::multiplyWithThreads, &c, a, b, i, numThreads);
        }

        for (int i = 0; (unsigned) i < numThreads; i++)
        {
            threads[i].join();
        }
    }
    
    c.print();
}

std::string Handler::getMatrixFileName(std::string letter)
{
    return "./data/" + letter + this->matrixSize + "x" + this->matrixSize + ".txt";
}