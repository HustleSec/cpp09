#include "BitcoinExchange.hpp"
#include <algorithm>
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

int BitcoinExchange::ft_isumber(char *ptr)
{
	int i;

	if (ptr[0] == '.')
	{
		i = 1;
		while (ptr && ptr[i] != '\0')
		{
			if (ptr[i] < '0' || ptr[i] > '9')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
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
	if (date != it_low->first || it_low == mp.end())
		it_low--;
	std::cout << date << " => " << mp[date] << " = " << it_low->second * mp[date] << std::endl;
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
			if (date.find(" ") != std::string::npos || date.find("	") != std::string::npos)
			{
				std::cout << "Error: bad input => " << date << std::endl;
				continue;
			}
			std::string value = line.substr(line.find("| ") + 2, line.find("\n"));
			char *ptr = NULL;
			double v = std::strtod(value.c_str(), &ptr);
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
			else if (v > INT_MAX)
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