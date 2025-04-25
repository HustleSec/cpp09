#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac > 1)
	{
		PmergeMe instance(av, ac);
	}
	return (0);
}