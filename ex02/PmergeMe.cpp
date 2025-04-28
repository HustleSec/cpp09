#include "PmergeMe.hpp"
#include <algorithm>
#include <iterator>
#include <ostream>

int PmergeMe::check_double(int ac, char **av)
{
    for (size_t i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].first == pairs[i].second)
            return (1);
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (j != i && (pairs[i].first == pairs[j].first || pairs[i].first == pairs[j].second ||
                pairs[i].second == pairs[j].first || pairs[i].second == pairs[j].second))
                return 1;
            if (ac - 1 > ((int)pairs.size() * 2))
            {
                if (j != i && (pairs[i].first == atoi(av[ac-1]) || pairs[i].second == atoi(av[ac-1])))
                    return (1);
            }
        }
    }
    return (0);
}

int PmergeMe::check_double_dq(int ac, char **av)
{
    for (size_t i = 0; i < pairs_dq.size(); i++)
    {
        if (pairs_dq[i].first == pairs_dq[i].second)
            return (1);
        for (size_t j = 0; j < pairs_dq.size(); j++)
        {
            if (j != i && (pairs_dq[i].first == pairs_dq[j].first || pairs_dq[i].first == pairs_dq[j].second ||
                pairs_dq[i].second == pairs_dq[j].first || pairs_dq[i].second == pairs_dq[j].second))
                return 1;
            if (ac - 1 > ((int)pairs_dq.size() * 2))
            {
                if (j != i && (pairs_dq[i].first == atoi(av[ac-1]) || pairs_dq[i].second == atoi(av[ac-1])))
                    return (1);
            }
        }
    }
    return (0);
}

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


void PmergeMe::sort_inside_pair_dq()
{
	for (int i = 0; i < (int)this->pairs_dq.size(); i ++)
	{
		if (this->pairs_dq[i].first < this->pairs_dq[i].second)
			std::swap(this->pairs_dq[i].first, this->pairs_dq[i].second);
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

void PmergeMe::merge_dq(int left, int mid, int right)
{
    std::deque<std::pair<int, int> > temp;
    int low = left;
    int high = mid + 1;

    while (low <= mid && high <= right)
    {
        if (pairs_dq[low] <= pairs_dq[high])
        {
            temp.push_back(pairs_dq[low]);
            low++;
        }
        else 
        {
            temp.push_back(pairs_dq[high]);
            high++;
        }
    }

    while (low <= mid) 
        temp.push_back(pairs_dq[low++]);

    while (high <= right) 
        temp.push_back(pairs_dq[high++]);

    for (int i = left; i <= right; i++)
        pairs_dq[i] = temp[i - left];
}



void PmergeMe::helper_merge_dq(int left, int right)
{
    if (right > left)
    {
        int mid = (left + right) / 2;
        this->helper_merge_dq(left, mid);
        this->helper_merge_dq(mid + 1, right);
        this->merge_dq(left, mid, right);
    }
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


void PmergeMe::create_dq()
{
    for (int i = 0; i < (int)pairs_dq.size(); i++)
    {
        this->chain_dq.push_back(pairs_dq[i].first);
        this->pend_dq.push_back(pairs_dq[i].second);
    }
    if (pend_dq.size() > 0)
        chain_dq.insert(chain_dq.begin(), pend_dq[0]);
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

void PmergeMe::generateJacobsthal_dq(int n)
{
    if (n <= 0)
        return ;

    jacob_dq.push_back(0);
    if (n == 1)
        return ;

    jacob_dq.push_back(1);
    int next = 0;
    for (int i = 2; i < n; ++i)
    {
        next = jacob_dq[i - 1] + 2 * jacob_dq[i - 2];
        jacob_dq.push_back(next);
    }
    return ;
}

void PmergeMe::combination()
{
    int first, last;

    for (int i = 0; i < ((int)jacob.size() - 1) && comb.size() < chain.size(); i++)
    {
        first = jacob[i];
        last = jacob[i + 1];
        comb.push_back(jacob[i + 1]);
        for (int j = last - 1; j > first; --j)
            comb.push_back(j);
    }
}

void PmergeMe::combination_dq()
{
    int first, last;

    for (int i = 0; i < ((int)jacob_dq.size() - 1) && comb_dq.size() < chain_dq.size(); i++)
    {
        first = jacob_dq[i];
        last = jacob_dq[i + 1];
        comb_dq.push_back(jacob_dq[i + 1]);
        for (int j = last - 1; j > first; --j)
            comb_dq.push_back(j);
    }
}


PmergeMe::PmergeMe(char **av, int ac)
{
    //  =========== vector ===========
    timeval start, end;

    gettimeofday(&start, NULL);
	
    if (this->check(av))
    {
        std::cout << "Before: " ;
        int j = 1;
        while (j < ac)
        {
            std::cout << av[j] << " ";
            j++;
        }
        std::cout << "\n";

        int i = 1;
        while (i + 1 < ac)
        {
            this->pairs.push_back(std::make_pair(atoi(av[i]), atoi(av[i + 1])));
			i += 2;
        }

        if (this->check_double(ac, av))
            return ;
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
        {
            std::vector<int>::iterator k;
            k = std::lower_bound(chain.begin(), chain.end(), atoi(av[ac - 1]));
            chain.insert(k, atoi(av[ac - 1]));
        }

        gettimeofday(&end, NULL);

        std::cout << "After:  " ;
        for (int i = 0; i < (int)chain.size(); i++)
            std::cout << chain[i] << " ";
        std::cout << "\n";

        long seconds = end.tv_sec - start.tv_sec;
        long useconds = end.tv_usec - start.tv_usec;
        double duration = seconds * 1e6 + useconds;
        duration = duration / 1e6;
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Time to process a range of 5 elements with std::vector : " << duration << " us" << "\n";
    }

    //================== dque ================
    timeval start1, end1;
    gettimeofday(&start1, NULL);

    if (this->check(av))
    {
        int i = 1;
        while (i + 1 < ac)
        {
            this->pairs_dq.push_back(std::make_pair(atoi(av[i]), atoi(av[i + 1])));
			i += 2;
        }

        if (this->check_double_dq(ac, av))
            return ;
		this->sort_inside_pair_dq();
		this->helper_merge_dq(0, this->pairs_dq.size() - 1);
        this->create_dq();
        this->generateJacobsthal_dq(ac - 1);
        if (this->jacob_dq.size() > 3)
        {
            this->jacob_dq.erase(jacob_dq.begin());
            this->jacob_dq.erase(jacob_dq.begin());
        }
       this->combination_dq();
       std::deque<int>::iterator it_dq;
       for (int i = 0; i < (int)comb.size(); i++)
       {
           if (comb_dq[i] >= 0 && comb_dq[i] - 1 < (int)pend_dq.size())
           {
                it_dq = std::lower_bound(chain_dq.begin(), chain_dq.end(), pend_dq[comb_dq[i] - 1]);
                chain_dq.insert(it_dq, pend_dq[comb_dq[i] - 1]);
           }
       }
        if ((int)chain_dq.size() < ac - 1)
        {
            int v = atoi(av[ac - 1]);

            std::deque<int>::iterator k_dq;
            k_dq = std::lower_bound(chain_dq.begin(), chain_dq.end(), v);
            chain_dq.insert(k_dq, v);
        }

        gettimeofday(&end1, NULL);

        long seconds1 = end1.tv_sec - start1.tv_sec;
        long useconds1 = end1.tv_usec - start1.tv_usec;
        double duration1 = seconds1 * 1e6 + useconds1;
        duration1 = duration1 / 1e6;
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Time to process a range of 5 elements with std::deque : " << duration1 << " us" << "\n";

        std::cout << "\n\n\n\n\n" << std::is_sorted(chain.begin(), chain.end()) << "   " << std::is_sorted(chain_dq.begin(), chain_dq.end()) << std::endl;
    }
	
}

PmergeMe::~PmergeMe()
{}