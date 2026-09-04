#include "RPN.hpp"

RPN::RPN()
{

}

RPN::RPN(const RPN& other)
{
    *this = other;
}
RPN& RPN::operator=(const RPN& other)
{
    if(this != &other)
        *this = other;
    return *this;
}
RPN::~RPN()
{

}

void RPN::calculate(const std::string &expression)
{
    std::stringstream ss(expression);
    std::string token;
    while( ss >> token)
    {
        if(token.size() == 1 && token[0] >= '0' && token[0] <= '9')
        {
            int number = token[0] - '0';
            stack.push(number);
        }
        // std::cout << "token= " << token << std::endl;
        else if( token == "+" || token == "-" || token == "/" || token == "*")
        {
            if(stack.size() < 2)
            {
                std::cerr << "Error" << std::endl;
                return ;
            }
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();

            int result;
            if (token == "+")
                result = left + right;
            else if(token == "-")
                result = left - right;
            else if(token == "*")
                result = left * right;
            else
            {
                if(right == 0)
                {
                    std::cerr << "Error" << std::endl;
                    return ;
                }
                result = left / right;
            }
            stack.push(result);
        }
        else
        {
            std::cerr << "Error" << std::endl;
            return ;
        }
    }
    if( stack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        return ;
    }
    std::cout << stack.top() << std::endl;

}
