#include "PmergeMe.hpp"
#include <algorithm>
#include <cstdlib>

//check if there is any double return ;

int PmergeMe::check(char **av)
{
    int i = 1, j = 0;

    while (av && av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}


void PmergeMe::sort_inside_pair()
{
	for (int i = 0; i < (int)this->pairs.size(); i ++)
	{
		if (this->pairs[i].first < this->pairs[i].second)
		{
			std::swap(this->pairs[i].first, this->pairs[i].second);
		}
	}
}

void PmergeMe::merge(int left, int mid, int right)
{
    std::vector<std::pair<int,int> > temp;
    int low = left;
    int high = mid + 1;

    while (low <= mid && high <= right)
    {
        if (pairs[low] <= pairs[high])
        {
            temp.push_back(pairs[low]);
            low++;
        }
        else 
        {
            temp.push_back(pairs[high]);
            high++;
        }
    }

    while (low <= mid) 
        temp.push_back(pairs[low++]);

    while (high <= right) 
        temp.push_back(pairs[high++]);

    for (int i = left; i <= right; i++)
        pairs[i] = temp[i - left];
}

void PmergeMe::helper_merge(int left, int right)
{
    if (right > left)
    {
        int mid = (left + right) / 2;
        this->helper_merge(left, mid);
        this->helper_merge(mid + 1, right);
        this->merge(left, mid, right);
    }
}

void PmergeMe::create()
{
    for (int i = 0; i < (int)pairs.size(); i++)
    {
        this->chain.push_back(pairs[i].first);
        this->pend.push_back(pairs[i].second);
    }
    if (pend.size() > 0)
        chain.insert(chain.begin(), pend[0]);
}


void PmergeMe::generateJacobsthal(int n)
{
    if (n <= 0)
        return ;

    jacob.push_back(0);
    if (n == 1)
        return ;

    jacob.push_back(1);

    for (int i = 2; i < n; ++i)
    {
        int next = jacob[i - 1] + 2 * jacob[i - 2];
        jacob.push_back(next);
    }
    return ;
}

void PmergeMe::combination()
{
    int first, last, i = 0;

    while (i+1 < (int)jacob.size() - 1)
    {
        first = jacob[i];
        last = jacob[i + 1];

        comb.push_back(jacob[i + 1]);
        while (first < last - 1)
        {
            last--;
            comb.push_back(last);
        }
        i++;
    }
}

PmergeMe::PmergeMe(char **av, int ac)
{
	
    if (this->check(av))
    {
        int i = 1;
        while (i + 1 < ac)
        {
            this->pairs.push_back(std::make_pair(atoi(av[i]), atoi(av[i + 1])));
			i += 2;
        }
		this->sort_inside_pair();
		this->helper_merge(0, this->pairs.size() - 1);
        this->create();
        this->generateJacobsthal(ac - 1);
        if (this->jacob.size() > 3)
        {
            this->jacob.erase(jacob.begin());
            this->jacob.erase(jacob.begin());
        }
       this->combination();
       std::vector<int>::iterator it;
       for (int i = 0; i < (int)comb.size(); i++)
       {
           if (comb[i] >= 0 && comb[i] - 1 < (int)pend.size())
           {
                it = std::lower_bound(chain.begin(), chain.end(), pend[comb[i] - 1]);
                chain.insert(it, pend[comb[i] - 1]);
           }
       }
        if ((int)chain.size() < ac - 1)
            chain.insert(chain.begin(), atoi(av[ac - 1]));
        for (int i = 0; i < (int)chain.size(); i++)
            std::cout << chain[i] << std::endl;
    }
}


PmergeMe::~PmergeMe()
{}