#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::~BitcoinExchange()
{

}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::string line;
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        throw std::runtime_error("could not open database file");
    }

    std::getline(file, line);
    while(std::getline(file, line))
    {
        std::size_t pos = line.find(',');

        if(pos == std::string::npos)
            continue;
        std::string date = line.substr(0, pos-1);//split only the date
        std::string rt = line.substr(pos + 2); //this for the rate
        //bc the rate is a string and the map except a double so we should convert it
        std::stringstream ss(rt);
        double rate;

        ss >> rate;
        databases[date] = rate;
        // std::cout << date << " -> " << rate << std::endl;
    }
    
    file.close();

}
 void BitcoinExchange::processInput(const std::string& filename)
 {
    std::string line;
    std::ifstream file(filename.c_str());

    if(!file.is_open())
    {
        throw std::runtime_error("could not open the input file");
    }

    std::getline(file, line);
    while(std::getline(file, line))
    {
        std::size_t pos = line.find('|');
        if(pos == std::string::npos)
        {
            std::cerr <<"Error: bad input => "<<line << std::endl;
            continue ;
        }
        std::string date = line.substr(0, pos-1);
        std::string vl = line.substr(pos + 2);

        std::stringstream ss(vl);

        double value;
        ss >> value;
        databases[date] = value;
        std::cout << "date = [" << date << "]"
                  << ", value = [" << vl << "]"
                  << std::endl;
    }
    file.close();

 }