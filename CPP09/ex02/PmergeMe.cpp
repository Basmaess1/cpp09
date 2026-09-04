#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}
PmergeMe::PmergeMe(const PmergeMe& other)
{
    *this = other;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        vec = other.vec;
        deq = other.deq;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{

}

void PmergeMe::addNumber(int number)
{
    vec.push_back(number);
    deq.push_back(number);
}

void PmergeMe::printVec()const
{
    std::vector<int>::const_iterator it;
    for(it = vec.begin(); it!= vec.end();++it)
        std::cout<< *it << " ";
    std::cout << std::endl;
}

void PmergeMe::printDeq() const
{
    std::deque<int>::const_iterator it;
    for(it = deq.begin(); it != deq.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

bool PmergeMe::isValidNumber(const std::string& str) const
{
    if(str.empty())
        return false;
    for(size_t i = 0; i < str.length(); i++)
    {
        if(!std::isdigit(str[i]))
            return false;
    }
    return true;
}

bool PmergeMe::ParseNumber(const std::string& str, int &number) const
{
    if(!isValidNumber(str))
        return false;
    long value = 0;
    for(size_t i = 0; i < str.length(); i++)
    {
        value = value * 10 + str[i] - '0';
        if(value > 2147483647)
            return false;
    }
    number = static_cast<int>(value);
    return true;
}

void PmergeMe::fordJohnsonVector(std::vector<int> &numbers)
{
    if (numbers.size() <= 1)
        return;
    bool hasStraggler = (numbers.size() % 2 != 0);
    int straggler = 0;

    if (hasStraggler)
        straggler = numbers[numbers.size() - 1];

    std::vector<Pair> pairs;
    std::size_t i = 0;

    while (i + 1 < numbers.size())
    {
        Pair p;
        if (numbers[i] < numbers[i + 1])
        {
            p.small = numbers[i];
            p.large = numbers[i + 1];
        }
        else
        {
            p.small = numbers[i + 1];
            p.large = numbers[i];
        }
        pairs.push_back(p);
        i += 2;
    }
    std::vector<int> largeElements;

    for (i = 0; i < pairs.size(); ++i)
        largeElements.push_back(pairs[i].large);
    fordJohnsonVector(largeElements);
    std::vector<Pair> sortedPairs;

    for (i = 0; i < largeElements.size(); ++i)
    {
        for (std::size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].large == largeElements[i])
            {
                sortedPairs.push_back(pairs[j]);
                break;
            }
        }
    }
    std::vector<int> mainChain;
    for (i = 0; i < largeElements.size(); ++i)
        mainChain.push_back(largeElements[i]);

    if (!sortedPairs.empty())
        mainChain.insert(
            mainChain.begin(),
            sortedPairs[0].small
        );

    std::size_t pendingCount = 0;
    if (sortedPairs.size() > 1)
        pendingCount = sortedPairs.size() - 1;
    std::vector<std::size_t> order =
        makeJacobsthalOrder(pendingCount);
    for (i = 0; i < order.size(); ++i)
    {
        std::size_t index = order[i];
        binaryInsertVector(
            mainChain,
            sortedPairs[index - 1].small,
            sortedPairs[index - 1].large
        );
    }
    if (hasStraggler)
    {
        std::vector<int>::iterator begin = mainChain.begin();
        std::vector<int>::iterator end = mainChain.end();
        while (begin < end)
        {
            std::vector<int>::iterator middle =
                begin + (end - begin) / 2;

            if (*middle < straggler)
                begin = middle + 1;
            else
                end = middle;
        }
        mainChain.insert(begin, straggler);
    }
    numbers = mainChain;
}
std::vector<std::size_t> PmergeMe::makeJacobsthalOrder(std::size_t pendingCount) const
{
    std::vector<std::size_t> order;

    std::size_t previous = 1;
    std::size_t current = 3;

    std::size_t start = 2;

    while (start <= pendingCount + 1)
    {
        std::size_t end = current;

        if (end > pendingCount + 1)
            end = pendingCount + 1;

        for (std::size_t i = end; i >= start; --i)
            order.push_back(i);

        start = current + 1;
        std::size_t next = current + 2 * previous;
        previous = current;
        current = next;
    }
    return order;
}

void PmergeMe::binaryInsertVector(std::vector<int> &mainChain, int value, int limit)
{
    std::vector<int>::iterator begin = mainChain.begin();
    std::vector<int>::iterator end = mainChain.begin();

    while (end != mainChain.end() && *end != limit)
        ++end;
    while (begin < end)
    {
        std::vector<int>::iterator middle =
            begin + (end - begin) / 2;

        if (*middle < value)
            begin = middle + 1;
        else
            end = middle;
    }
    mainChain.insert(begin, value);
}

double PmergeMe::sortVector()
{
    clock_t start = clock();

    fordJohnsonVector(vec);

    clock_t end = clock();

    return static_cast<double>(end - start)
        / CLOCKS_PER_SEC * 1000000;
}

void PmergeMe::printAfterVector() const
{
    std::vector<int>::const_iterator it;

    std::cout << "After: ";

    for (it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";

    std::cout << std::endl;
}

// deque

void PmergeMe::fordJohnsonDeque(std::deque<int> &numbers)
{
    if (numbers.size() <= 1)
        return;

    bool hasStraggler = (numbers.size() % 2 != 0);
    int straggler = 0;

    if (hasStraggler)
        straggler = numbers[numbers.size() - 1];

    std::deque<Pair> pairs;

    std::size_t i = 0;

    while (i + 1 < numbers.size())
    {
        Pair p;

        if (numbers[i] < numbers[i + 1])
        {
            p.small = numbers[i];
            p.large = numbers[i + 1];
        }
        else
        {
            p.small = numbers[i + 1];
            p.large = numbers[i];
        }

        pairs.push_back(p);
        i += 2;
    }
    std::deque<int> largeElements;

    for (i = 0; i < pairs.size(); ++i)
        largeElements.push_back(pairs[i].large);
    fordJohnsonDeque(largeElements);
    std::deque<Pair> sortedPairs;

    for (i = 0; i < largeElements.size(); ++i)
    {
        for (std::size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].large == largeElements[i])
            {
                sortedPairs.push_back(pairs[j]);
                break;
            }
        }
    }
    std::deque<int> mainChain;

    for (i = 0; i < largeElements.size(); ++i)
        mainChain.push_back(largeElements[i]);
    if (!sortedPairs.empty())
        mainChain.insert(
            mainChain.begin(),
            sortedPairs[0].small
        );
    std::size_t pendingCount = 0;

    if (sortedPairs.size() > 1)
        pendingCount = sortedPairs.size() - 1;

    std::vector<std::size_t> order =
        makeJacobsthalOrder(pendingCount);

    for (i = 0; i < order.size(); ++i)
    {
        std::size_t index = order[i];

        binaryInsertDeque(
            mainChain,
            sortedPairs[index - 1].small,
            sortedPairs[index - 1].large
        );
    }
    if (hasStraggler)
    {
        std::deque<int>::iterator begin = mainChain.begin();
        std::deque<int>::iterator end = mainChain.end();

        while (begin < end)
        {
            std::deque<int>::iterator middle =
                begin + (end - begin) / 2;

            if (*middle < straggler)
                begin = middle + 1;
            else
                end = middle;
        }
        mainChain.insert(begin, straggler);
    }
    numbers = mainChain;
}

void PmergeMe::binaryInsertDeque(
    std::deque<int> &mainChain,
    int value,
    int limit)
{
    std::deque<int>::iterator begin = mainChain.begin();
    std::deque<int>::iterator end = mainChain.begin();

    // Search only before the partner.
    while (end != mainChain.end() && *end != limit)
        ++end;

    // Binary search.
    while (begin < end)
    {
        std::deque<int>::iterator middle =
            begin + (end - begin) / 2;

        if (*middle < value)
            begin = middle + 1;
        else
            end = middle;
    }

    mainChain.insert(begin, value);
}
double PmergeMe::sortDeque()
{
    clock_t start = clock();

    fordJohnsonDeque(deq);

    clock_t end = clock();

    return static_cast<double>(end - start)
        / CLOCKS_PER_SEC * 1000000;
}
