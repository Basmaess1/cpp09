#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if(ac < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    PmergeMe pm;
    for(int i = 1; i < ac;i++)
    {
        int number;
        if(!pm.ParseNumber(av[i], number))
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        pm.addNumber(number);
    }

    std::cout<< "Before: ";
    pm.printVec();

    pm.sortVector();

    pm.printAfterVector();
    
    pm.sortDeque();

    std::cout << "Deque after: ";
    pm.printDeq();

}