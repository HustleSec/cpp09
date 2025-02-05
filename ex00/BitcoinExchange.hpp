#ifndef BITCOINEXCHANGE_HPP 
#define BITCOINEXCHANGE_HPP 
#include <fstream>
#include <iostream>
#include <map>

class BitcoinExchange
{
	private:
		std::ifstream	*file;
		int				a;
		std::map<std::string , double>mp;
		std::map<std::string , double>mp_db;
	public:
		BitcoinExchange();
		BitcoinExchange(std::ifstream &input);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange& operator=(const BitcoinExchange& other);


		void	check_file();
		int		ft_isumber(char *ptr);
		void	ft_db();
		void	check_db(std::string date);
};

#endif