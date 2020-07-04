#include <sys/types.h>
#include <iostream>
#include <dirent.h>
#include <thread>
#include "../include/matrix.h"

void read_directory(const std::string &name)
{
    DIR *dirp = opendir(name.c_str());
    struct dirent *dp;

    while ((dp = readdir(dirp)) != NULL)
    {
        std::string filename = dp->d_name;

        if (dp->d_name[0] == 'A')
        {
            Matrix a, b, c;
            std::cout << name + "/" + filename << std::endl;
            //a.readFromFile(name + "/" + filename); // read matrix A
            //b.readFromFile(name + "/" + filename.replace(0,1, "B")); // read matrix b
            a.readFromFile("./data/A4x4.txt");
            b.readFromFile("./data/B4x4.txt");
            c.multiply(a, b);
            //c.print();
        }
    }

    closedir(dirp);
}

int main()
{
    //std::string directory = "./data";
    //read_directory(directory);
    //Matrix m;
    //m.readFromFile("./data/test.txt");
    //m.print();

    // multithreading
    Matrix a, b, c;
    a.readFromFile("./data/A4x4.txt");
    b.readFromFile("./data/B4x4.txt");

    const unsigned int numThreads = 4;
    std::thread threads[numThreads];
    
    c.loadInsideMatrix(a.matrix.size()); // workaround

    for (int i = 0; (unsigned) i < numThreads; ++i)
    {
        threads[i] = std::thread(&Matrix::multiplyWithThreads, &c, a, b, i, numThreads);
    }

    for (int i = 0; (unsigned) i < numThreads; i++)
    {
        threads[i].join();
    }

    c.print();

    return 0;
}