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
    if(this != &other)
        *this = other;
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
    if (value == 0)
        return false;

    number = static_cast<int>(value);
    return true;
}

void PmergeMe::makePairsVector()
{
    std::vector<Pair> pairs;

    std::size_t i = 0;

    while (i + 1 < vec.size())
    {
        Pair p;

        if (vec[i] < vec[i + 1])
        {
            p.small = vec[i];
            p.large = vec[i + 1];
        }
        else
        {
            p.small = vec[i + 1];
            p.large = vec[i];
        }
        pairs.push_back(p);

        i += 2;
    }
    // to print
    std::vector<Pair>::iterator it;

    for (it = pairs.begin(); it != pairs.end(); ++it)
    {
        std::cout << "(" << it->small
              << ", " << it->large << ") ";
    }
    std::cout << std::endl;
}

void PmergeMe::fordJohnsonVector(std::vector<int> &numbers)
{
    if (numbers.size() <= 1)
        return;

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

    /*
     * Put the large elements into a separate vector.
     */
    std::vector<int> largeElements;

    for (i = 0; i < pairs.size(); ++i)
        largeElements.push_back(pairs[i].large);

    /*
     * If numbers.size() is odd,
     * the last element has no pair.
     */
    bool hasStraggler = (numbers.size() % 2 != 0);

    int straggler = 0;

    if (hasStraggler)
        straggler = numbers[numbers.size() - 1];

    /*
     * Recursively sort the large elements.
     */
    fordJohnsonVector(largeElements);

    /*
     * Reorder our pairs according to the
     * sorted large elements.
     */
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

    /*
     * Main chain starts with the sorted large elements.
     */
    numbers.clear();

    for (i = 0; i < largeElements.size(); ++i)
        numbers.push_back(largeElements[i]);

    /*
     * Insert the small elements.
     *
     * For now, we simply insert them in order.
     * We will replace this part with the
     * Jacobsthal insertion later.
     */
    for (i = 0; i < sortedPairs.size(); ++i)
    {
        std::vector<int>::iterator pos = numbers.begin();

        while (pos != numbers.end() && *pos < sortedPairs[i].small)
            ++pos;

        numbers.insert(pos, sortedPairs[i].small);
    }

    /*
     * Insert the unpaired element.
     */
    if (hasStraggler)
    {
        std::vector<int>::iterator pos = numbers.begin();

        while (pos != numbers.end() && *pos < straggler)
            ++pos;

        numbers.insert(pos, straggler);
    }
}

// void PmergeMe::fordJohnsonVector(std::vector<Pair> &pairs)
// {
//     if (pairs.size() <= 1)
//         return;

//     std::vector<Pair> nextPairs;

//     std::size_t i = 0;

//     while (i + 1 < pairs.size())
//     {
//         Pair p;

//         if (pairs[i].large < pairs[i + 1].large)
//         {
//             p.small = pairs[i].large;
//             p.large = pairs[i + 1].large;
//         }
//         else
//         {
//             p.small = pairs[i + 1].large;
//             p.large = pairs[i].large;
//         }

//         nextPairs.push_back(p);
//         i += 2;
//     }

//     fordJohnsonVector(nextPairs);

//     std::vector<Pair> sortedPairs;

//     for (std::size_t j = 0; j < nextPairs.size(); ++j)
//     {
//         for (std::size_t k = 0; k < pairs.size(); ++k)
//         {
//             if (pairs[k].large == nextPairs[j].large)
//             {
//                 sortedPairs.push_back(pairs[k]);
//                 break;
//             }
//         }
//     }

//     if (pairs.size() % 2 != 0)
//     {
//         sortedPairs.push_back(pairs[pairs.size() - 1]);
//     }

//     pairs = sortedPairs;
// }

std::vector<std::size_t> PmergeMe::makeJacobsthalOrder(
    std::size_t count) const
{
    std::vector<std::size_t> order;

    std::size_t previous = 1;
    std::size_t current = 3;

    while (previous < count)
    {
        std::size_t end = current;

        if (end > count)
            end = count;

        for (std::size_t i = end; i > previous; --i)
            order.push_back(i);

        std::size_t next = current + 2 * previous;
        previous = current;
        current = next;
    }

    return order;
}
void PmergeMe::binaryInsertVector(std::vector<int> &mainChain,
                                   int value,
                                   int limit)
{
    std::vector<int>::iterator begin = mainChain.begin();
    std::vector<int>::iterator end = mainChain.end();

    if (limit != 2147483647)
    {
        end = mainChain.begin();

        while (end != mainChain.end() && *end != limit)
            ++end;
    }

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

void PmergeMe::sortVector()
{
    fordJohnsonVector(vec);
}
// void PmergeMe::sortVector()
// {
//     std::vector<Pair> pairs;

//     std::size_t i = 0;

//     while (i + 1 < vec.size())
//     {
//         Pair p;

//         if (vec[i] < vec[i + 1])
//         {
//             p.small = vec[i];
//             p.large = vec[i + 1];
//         }
//         else
//         {
//             p.small = vec[i + 1];
//             p.large = vec[i];
//         }

//         pairs.push_back(p);
//         i += 2;
//     }

//     fordJohnsonVector(vect);

//     std::vector<int> mainChain;

//     for (i = 0; i < pairs.size(); ++i)
//         mainChain.push_back(pairs[i].large);

//     if (!pairs.empty())
//         mainChain.insert(mainChain.begin(), pairs[0].small);

//     std::size_t pendingCount = 0;

//     if (pairs.size() > 1)
//         pendingCount = pairs.size() - 1;

//     std::vector<std::size_t> order =
//         makeJacobsthalOrder(pendingCount);

//     for (i = 0; i < order.size(); ++i)
//     {
//         std::size_t index = order[i];

//         binaryInsertVector(
//             mainChain,
//             pairs[index - 1].small,
//             pairs[index - 1].large
//         );
//     }

//     vec = mainChain;
// }

void PmergeMe::printAfterVector() const
{
    std::vector<int>::const_iterator it;

    std::cout << "After: ";

    for (it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";

    std::cout << std::endl;
}
