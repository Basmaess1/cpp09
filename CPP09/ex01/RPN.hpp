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
    ~RPN();

    void calculate(const std::string &expression);
};