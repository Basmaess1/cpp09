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

    double vectorTime = pm.sortVector();
    double dequeTime = pm.sortDeque();

    pm.printAfterVector();
    std::cout << "Time to process a range of "
              << ac - 1
              << " elements with std::vector : "
              << vectorTime
              << " us"
              << std::endl;

    std::cout << "Time to process a range of "
              << ac - 1
              << " elements with std::deque : "
              << dequeTime
              << " us"
              << std::endl;

}