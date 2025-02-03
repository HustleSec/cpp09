#ifndef BITCOINEXCHANGE_HPP 
#define BITCOINEXCHANGE_HPP 
#include <fstream>
#include <iostream>

class BitcoinExchange
{
	private:
		std::ifstream	*file;
		int				a;
	public:
		BitcoinExchange();
		BitcoinExchange(std::ifstream &input);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange& operator=(const BitcoinExchange& other);


		void chek_file();
};

#endif