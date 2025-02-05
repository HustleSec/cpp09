#ifndef RPN_HPP 
#define RPN_HPP 
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cstdlib>

class RPN {
public:
	RPN();
	~RPN();
    void rpn(std::string& input);
        
};

#endif