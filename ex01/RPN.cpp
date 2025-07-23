#include "RPN.hpp"
#include <climits>

RPN::RPN(){}

RPN::~RPN(){}

void	RPN::rpn(std::string &input)
{
	if (input.empty())
	{
		std::cout << "empty input" << std::endl;
		return ;
	}
	std::stack<int> stack;
	std::stringstream ss(input);
	std::string elem;
	
	while (ss >> elem)
	{
		if (elem == "+" || elem == "-" || elem == "*" || elem == "/")
		{
			if (stack.size() < 2)
			{
				std::cerr << "Error: Not enough operands in stack for operation!" << std::endl;
				return;
			}

			long long b = stack.top(); stack.pop();
			long long a = stack.top(); stack.pop();
			
			long long result = 0;

			if (elem == "+")
				result = a + b;
			else if (elem == "-")
				result = a - b;
			else if (elem == "*")
				result = a * b;
			else if (elem == "/")
			{
				if (b == 0) 
				{
					std::cerr << "Error: Division by zero!" << std::endl;
					return;
				}
				result = a / b;
			}
			if (result > INT_MAX || result < INT_MIN) 
			{
				std::cerr << "Error: Integer overflow in addition!" << std::endl;
				return;
			}
			stack.push(result);
		} 
		else
			stack.push(std::stoi(elem));
	}

	if (stack.size() == 1) 
	{
		if ((long long)stack.top() > INT_MAX || (long long)stack.top() < INT_MIN) 
		{
			std::cerr << "Error: Integer overflow in addition!" << std::endl;
			return;
		}
		std::cout << stack.top() << std::endl;
	}
	else
		std::cerr << "Error: Stack size is not 1 after processing!" << std::endl;
}