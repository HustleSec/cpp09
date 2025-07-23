#include "RPN.hpp"
#include <cstdlib>

RPN::RPN(){}

RPN::~RPN(){}

void	RPN::rpn(std::string &input)
{
	if (input.empty())
	{
		std::cout << "empty input" << std::endl;
		return ;
	}
	std::stack<double> stack;
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

			double b = stack.top(); stack.pop();
			double a = stack.top(); stack.pop();
			double result = 0.0;

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
			stack.push(result);
		} else 
		{
			char* end;
			double num = std::strtod(elem.c_str(), &end);
			if (*end == '\0') 
				stack.push(num);
			else 
			{
				std::cerr << "Error: Invalid token '" << elem << "'!" << std::endl;
				return;
			}
		}
	}

	if (stack.size() == 1) 
		std::cout << "Final result: " << stack.top() << std::endl;
	else
		std::cerr << "Error: Stack size is not 1 after processing!" << std::endl;
}