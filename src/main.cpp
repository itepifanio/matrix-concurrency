#include "../include/matrix.h"

int main() {
    Matrix m;
    m.readFromFile("./data/test.txt");
    m.print();

    return 0;
}