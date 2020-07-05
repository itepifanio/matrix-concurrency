#ifndef _HANDLER_H_
#define _HANDLER_H_
#include <string>

class Handler{
    private:
        std::string matrixSize;
        std::string type; // S (sequential), C (concurrency)
        std::string getMatrixFileName(std::string letter);
    public:
        Handler(std::string matrixSize, std::string type);
        void execute();
};

#endif