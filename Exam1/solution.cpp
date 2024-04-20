#include "solution.h"

#include <cassert>
#include <stdexcept>
#include <stack>
#include <string>

bool verify(const std::string& expression)
{
	if(expression.empty()) 
	{
		return true;
	}

	if (isOperation(expression.front()) || isOperation(expression.back()))
	{
        return false;
	}

	for (int i = 0; i < expression.size(); ++i) 
	{
		char current = expression[i];
        if (current == ' ') 
		{
            return false;
		}

        if (!isDigit(current) && !isOperation(current)) 
		{
            return false;
		}

		if (i < expression.size() - 1) 
		{
            char next = expression[i + 1];

            if (isOperation(current) && isOperation(next)) 
			{ 
                return false; 
			}
			
            if (isDigit(current) && isDigit(next)) 
			{
                return false; 
			}
        }
    }
return true;
}

std::string toRpn(const std::string& expression, Associativity associativity)
{
	if (!verify(expression))  
	{
        throw std::invalid_argument("Invalid expression.");
    }

    std::string rpn; 
    std::stack<char> operations; 

	for (char c : expression) 
	{
        if (isDigit(c)) 
		{
            rpn += c;
        } else if (isOperation(c)) 
		{
            while (!operations.empty() && isOperation(operations.top()) &&
                   ((associativity == Associativity::Left && priority(c) <= priority(operations.top())) ||
                   (associativity == Associativity::Right && priority(c) < priority(operations.top())))) 
			{
                rpn += operations.top();
                operations.pop();
            }
            operations.push(c);
        }
    }

	while (!operations.empty()) 
	{
        rpn += operations.top();
        operations.pop();
	}

return rpn;
}
