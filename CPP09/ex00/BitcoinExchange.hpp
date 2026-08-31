#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

class BitcoinExchange
{

    private:
    std::map<std::string, double> databases;
    bool isValidDate(const std::string& date);

    public:
    BitcoinExchange();
    ~BitcoinExchange();

    void loadDatabase(const std::string& filename);
    void processInput(const std::string& filename);

    bool isValidateValue(const std::string & value);
    
};