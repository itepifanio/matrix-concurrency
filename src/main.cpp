#include <sys/types.h>
#include <iostream>
#include <dirent.h>
#include "../include/handler.h"

int main()
{
    Handler h("4", "S");
    h.execute();

    return 0;
}