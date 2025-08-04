#include "handleconsoleoperations.h"
#include <iostream>

int main()
{
    HandleConsoleOperations console(std::cin, std::cout);
    console.Process();
    return 0;
}
