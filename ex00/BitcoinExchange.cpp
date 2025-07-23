#include "BitcoinExchange.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <map>


BitcoinExchange::BitcoinExchange()
{
	this->file = NULL;
	this->a = 0;
}

BitcoinExchange::BitcoinExchange(std::ifstream &input)
{
	this->file = &input;
	this->a = 0;
}

int BitcoinExchange::ft_isumber(std::string s)
{
	int i = 0;

	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

void	BitcoinExchange::ft_db()
{

	std::ifstream db("data.csv");
	if (!db)
		throw  std::logic_error("Error: could not open the database file");
	std::string l;
	getline(db, l);
	while (getline(db, l))
	{
		std::string db_date = l.substr(0, l.find(","));
		std::string val = l.substr(l.find(',') + 1, l.find('\n'));
		double va = std::strtod(val.c_str(), NULL);
		this->mp_db[db_date] = va;
	}
}

void	BitcoinExchange::check_db(std::string date)
{
	std::map<std::string , double>::iterator it_low;
	it_low = mp_db.lower_bound(date);
	if (it_low == mp_db.end() || it_low->first != date)
	{
		if (it_low != mp_db.begin())
		{
        	it_low--;
			std::cout << std::fixed << std::setprecision(0) << date << " => " << mp[date] << " = " << it_low->second * mp[date] << std::endl;
		}
		else
			std::cout << "bade date or invalid one\n";
	}
}

int count(std::string s)
{
	int i = 0, count = 0;

	while (s[i])
	{
		if (s[i] == '-')
			count++;
		i++;
	}
	if (count != 2)
		return (0);
	return (1);
}

int validate(std::string date)
{
    size_t pos1 = date.find('-');
    size_t pos2 = date.find('-', pos1 + 1);

    int year = std::stoi(date.substr(0, pos1));
    int month = std::stoi(date.substr(pos1 + 1, pos2 - pos1 - 1));
    int day = std::stoi(date.substr(pos2 + 1));

	int days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 != 0) 
        days[1] = 28;

    if (year < 2000 || year > 9999 || day < 1 || day > days[month - 1] || month < 1 || month > 12)
		return (0);

	return (1);
}


void BitcoinExchange::check_file()
{
	if (!this->file)
		throw std::logic_error("Error: file could not be open check for privilege of the file");
	
	this->ft_db();

	std::string line;
	getline(*file, line);
	if (line != "date | value")
		throw std::logic_error("Error: invalid date value\n");
	std::map<std::string, double > mp;
	while (getline(*file, line))
	{
		if (line.empty())
		{
			std::cout << "Error: emtpy line\n";
		}
		else if (line.find(" | ") != std::string::npos)
		{
			std::string date = line.substr(0, line.find(" |"));
			if (date.find(" ") != std::string::npos || date.find("	") != std::string::npos || !ft_isumber(date) || !count(date) || !validate(date))
			{
				std::cout << "Error: bad input => " << date << std::endl;
				continue;
			}
			std::string value = line.substr(line.find("| ") + 2, line.find("\n"));
			char *ptr = NULL;
			double v = std::strtod(value.c_str(), &ptr);
			size_t pos = value.find('.');
			if (pos != std::string::npos)
			{
				if (pos == 0 || pos == value.size() - 1)
				{
					std::cout << "not a valid number\n";
					continue ;
				}
			}
			if (v < 1)
			{
				std::cout << "Error: not a positive number." << std::endl;
				continue;
			}
			else if (ptr != NULL && ptr[0] != '\0')
			{
				std::cout << "Error: not a number or invalid character after the number\n";
				continue;
			}
			else if (v > 1000)
			{
				std::cout << "Error: too large a number." << std::endl;
				continue;
			}
			else if (value.find(" ") != std::string::npos || value.find("	") != std::string::npos)
			{
				std::cout << "Error: not a number or invalid character after the number\n";
				continue;
			}
			else
			{
				this->mp[date] = v;
				this->check_db(date);
			}
	 	}
		else
			std::cout << "Error: bad input => "<< line << std::endl;
	}
}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->file = other.file;
	}
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		this->file = other.file;
	}
	return (*this);
}