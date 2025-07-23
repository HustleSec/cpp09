#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include "RPN.hpp"

int ft_valid(std::string s)
{
    int i = 0;
    while (s[i])
    {
        if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '*' 
            || s[i] == '+' || s[i] == '-' || s[i] == '/' 
            || s[i] == ' '))
            return (0);
        i++;
    }
    return (1);
}

int main(int ac, char *av[]) {
	(void)ac;
    RPN rpn;
    std::string expression = av[1];
    if (!ft_valid(expression))
    {
        std::cout << "Error: invalid character\n";
        return (0);
    }
    rpn.rpn(expression);
    return 0;
}
