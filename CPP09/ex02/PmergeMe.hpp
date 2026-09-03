#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>

struct Pair
{
    int large;
    int small;
};

class PmergeMe
{
    private:
    std::vector<int> vec;
    std::deque<int> deq;

    void fordJohnsonVector(std::vector<int> &numbers);
    void binaryInsertVector(std::vector<int> &mainChain,
                            int value,
                            int limit);
    void fordJohnsonDeque(std::deque<int> &numbers);
    std::vector<std::size_t> makeJacobsthalOrder(std::size_t pendingCount) const;

    void binaryInsertDeque(std::deque<int> &mainChain,
        int value, int limit);
    
    public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();
    void addNumber(int number);
    void printVec()const;
    void printDeq()const;
    bool isValidNumber(const std::string& str) const;
    bool ParseNumber(const std::string& str, int &number) const;
    void printAfterVector() const;
    void sortVector();
    void sortDeque();
};