#include "../include/handler.h"
#include "../include/matrix.h"
#include <chrono>
#include <ctime>
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
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
    //c.print();
    c.writeMatrix(this->getMatrixFileName("C"));
}

std::string Handler::getMatrixFileName(std::string letter)
{
    return "./data/" + letter + this->matrixSize + "x" + this->matrixSize + ".txt";
}