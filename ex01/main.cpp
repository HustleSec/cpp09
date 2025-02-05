#include <cstdlib>
#include <iostream>
#include <stack>
#include "RPN.hpp"

int main(int ac, char *av[]) {
	(void)ac;
    RPN rpn;
    std::string expression = av[1];
    rpn.rpn(expression);
    return 0;
}
