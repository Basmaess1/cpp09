#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

class BitcoinExchange
{

    private:
    std::map<std::string, double> databases;

    public:
    BitcoinExchange();
    ~BitcoinExchange();

    void loadDatabase(const std::string& filename);
    void processInput(const std::string& filename);

    bool isValidateDate(const std::string& date);
    bool isValidateValue(const std::string & value);
    
};