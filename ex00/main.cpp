#include "BitcoinExchange.hpp"

int main(int ac, char *av[])
{
	try 
	{
		if (ac == 2)
		{
			std::ifstream input(av[1]);
			BitcoinExchange s(input);
			s.chek_file();
		}
		else
			std::cerr << "Error: could not open file." << std::endl;
	}
	catch(std::exception & e)
	{
		std::cout << e.what() <<std::endl;
	}
	return (0);
}