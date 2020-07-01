#include "../include/matrix.h"
#include <sys/types.h>
#include <iostream>
#include <dirent.h>

void read_directory(const std::string& name)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        std::cout << (dp->d_name) << std::endl;
        Matrix m;
        m.readFromFile(name + "/" + dp->d_name);
        m.print();
        break; // read only one
    }
    closedir(dirp);
}


int main() {
    std::string directory = "./data";
    read_directory(directory);
    //Matrix m;
    //m.readFromFile("./data/test.txt");
    //m.print();

    return 0;
}