#pragma once
#include <iostream>
#include <stack>
#include <sstream>
class RPN
{
    private:
    std::stack<int> stack;
    public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    void calculate(const std::string &expression);
};