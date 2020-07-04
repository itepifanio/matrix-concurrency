#include "../include/handler.h"
#include <ctype.h>
#include <iostream>

bool isUnsigned(char number[])
{
    int i = 0;

    if (number[0] == '-')
        return false;
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i])){
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    std::cout << isdigit(atoi(argv[1])) << std::endl;
    std::cout << std::string(argv[1]) << std::endl;
    std::cout << std::string(argv[2]) << std::endl;

    if (argc == 3 && isUnsigned(argv[1]) && (std::string(argv[2]) == "C" || std::string(argv[2]) == "S"))
    {
        std::string size = std::string(argv[1]);
        std::string type = std::string(argv[2]);
        Handler h(size, type);
        h.execute();
    }
    else
    {
        std::cout << "Invalid args" << std::endl;
    }

    return 0;
}