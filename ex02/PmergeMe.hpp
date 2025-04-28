#ifndef PMERGE_ME_HPP 
#define PMERGE_ME_HPP 
#include <iostream>
#include <vector>
#include <utility>
#include  <algorithm>
#include <sys/time.h>
#include <iomanip>
#include <deque>

class PmergeMe {
	private:
		std::vector<std::pair<int,int> >	pairs;
		std::vector<int>					chain;
		std::vector<int> 					pend;
		std::vector<int> 					jacob;
		std::vector<int> 					comb;


		std::deque<std::pair<int, int> >	pairs_dq;
		std::deque<int> 				jacob_dq;
		std::deque<int> 				chain_dq;
		std::deque<int> 				pend_dq;
		std::deque<int>					comb_dq;
public:
	PmergeMe(char **av, int ac);
	int		check(char **av);
	int		check_double(int ac, char **av);
	void	sort_inside_pair();
	void 	helper_merge(int left, int right);
	void 	merge(int left, int mid, int right);
	void	generateJacobsthal(int n);
	void 	create();
	void	combination();

	int		check_double_dq(int ac, char **av);
	void	sort_inside_pair_dq();
	void	helper_merge_dq(int left, int right);
	void	merge_dq(int left, int mid, int right);
	void	create_dq();
	void 	generateJacobsthal_dq(int n);
	void	combination_dq();
	~PmergeMe();
};

#endif