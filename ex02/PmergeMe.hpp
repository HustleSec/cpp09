#ifndef PMERGE_ME_HPP 
#define PMERGE_ME_HPP 
#include <iostream>
#include <vector>
#include <utility>
#include  <algorithm>

class PmergeMe {
	private:
		std::vector<std::pair<int,int> > pairs;
		std::vector<int> chain;
		std::vector<int> pend;
		std::vector<int> jacob;
		std::vector<int> comb;
public:
	PmergeMe(char **av, int ac);
	int		check(char **av);
	void	sort_inside_pair();
	void 	helper_merge(int left, int right);
	void 	merge(int left, int mid, int right);
	void	generateJacobsthal(int n);
	void 	create();
	void	combination();
	~PmergeMe();
};

#endif