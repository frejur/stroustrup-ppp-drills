#include <iostream>
#include <limits>

void exit_on_return ()
{
    std::cout << "<PRESS ENTER TO EXIT>" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
