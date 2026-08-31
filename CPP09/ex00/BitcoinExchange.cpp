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
        std::string date = line.substr(0, pos);
        std::string rt = line.substr(pos + 1);
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
        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        std::stringstream ss(vl);

        double value;
        char extra;
        ss >> value;

        if (ss.fail())
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (ss >> extra)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if(value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if(value > 1000)
        {
            std::cerr << "Error: too large number." << std::endl;
            continue;
        }
        std::map<std::string, double>::iterator it = databases.upper_bound(date);
        if (it == databases.begin())
        {
            std::cerr << "Error: date is too early." << std::endl;
            continue;
        }
        --it;
        double result = value * it->second;
        std::cout << date << " => " << value
                << " = " << result << std::endl;
        // std::cout << "date = ["<< date <<"]"
        //           << ", value = ["<< vl <<"]"
        //           << std::endl;
    }
    file.close();

 }

bool BitcoinExchange::isValidDate(const std::string& date)
{
    if(date.length() != 10)
        return false;
    if(date[4] != '-' || date[7] != '-')
        return false;
    for(int i = 0; i < 10;i++)
    {
        if(i == 4 || i == 7)
            continue;
        if(date[i] < '0' || date[i] > '9')
            return false;
    }
    int year = std::atoi(date.substr(0,4).c_str());
    int month = std::atoi(date.substr(5,2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if(month < 1 || month > 12)
        return false;
    int days[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = days[month - 1];
    bool leapyear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if(leapyear)
        days[1] = 29;
    if (day < 1 || day > maxDay)
        return false;
    return true;
}


//  void BitcoinExchange::processInput(const std::string& filename)
//  {
//     std::string line;
//     std::ifstream file(filename.c_str());

//     if(!file.is_open())
//     {
//         throw std::runtime_error("could not open the input file");
//     }

//     std::getline(file, line);
//     while(std::getline(file, line))
//     {
//         std::size_t pos = line.find('|');
//         if(pos == std::string::npos)
//         {
//             std::cerr <<"Error: bad input => "<<line << std::endl;
//             continue ;
//         }
//         std::string date = line.substr(0, pos-1);
//         std::string vl = line.substr(pos + 2);
//         if (!isValidDate(date))
//         {
//             std::cerr << "Error: bad input => " << date << std::endl;
//             continue;
//         }

//         std::stringstream ss(vl);

//         double value;
//         ss >> value;
//         if (ss.fail())
//         {
//             std::cerr << "Error: bad input => " << line << std::endl;
//             continue;
//         }
//         if(value < 0)
//         {
//             std::cerr << "Error: not a positive number " << std::endl;
//             continue;
//         }
//         if(value > 1000)
//         {
//             std::cerr << "Error: too large number" << std::endl;
//             continue;
//         }
//         std::map<std::string, double>::iterator it = databases.lower_bound(date);
//         // if (it == databases.end())
//         // {
//         //     --it;
//         // }
//         // if (it->first != date)
//         // {
//             if (it == databases.begin())
//             {
//                 std::cerr << "Error: date is too early." << std::endl;
//                 continue;
//             }
//             --it;
//         // }
//         double result = value * it->second;
//         std::cout << date << " => " << value
//                 << " = " << result << std::endl;
//         // std::cout << "date = ["<< date <<"]"
//         //           << ", value = ["<< vl <<"]"
//         //           << std::endl;
//     }
//     file.close();

//  }