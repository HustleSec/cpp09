#include "BitcoinExchange.hpp"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <iostream>


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

void BitcoinExchange::chek_file()
{
	if (!this->file)
		throw std::logic_error("Error: file could not be open check for privilege of the file");

	std::string line;
	std::string value;
	std::string year;
	std::string month;
	std::string day;

	while (getline(*file, line))
	{
		int quote = 0;
		if (this->a == 0)
		{
			if (this->a == 0 && line != "date | value")
				std::cout << "Error: in date | value 1" << std::endl;
			this->a++;
		}
		else
		{
			quote = line.find("-");
			if (quote == -1)
			{
				std::cout << "Error: invalid date \n";
			}
			else
			{
				year = line.substr(0 , quote);
				line = line.substr(quote + 1, line.size());
			}

			quote = line.find("-");
			if (quote == -1)
				year = "";
			else
			{
				month = line.substr(0 , quote);
				line = line.substr(quote + 1, line.size());
			}

			quote = line.find("|");
			if (quote == -1)
			{
				std::cout << "Error: bad input => " << year << "-" << month << "-"<< day << std::endl;
				year = "";
				month = "";
			}
			else 
			{
				day = line.substr(0 , quote);
				value = line.substr(quote + 1, line.size());
				std::cout << year << "-" << month << "-"<< day << "=>" << std::endl;
			}

		}
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