#include <iostream>
#include <stack>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool isNumber(const string& token)
{
	for (char c : token)
	{
		if (!isDigit(c))
		{
			return false;
		}
	}
	return true;
}

bool isOperation(const string& token)
{
	vector<string> operators = { "+", "-", "*", "/", "%", "&", "|", "^" };

	for (const auto& op : operators)
	{
		if (token == op)
		{
			return true;
		}
	}
	return false;
}

bool isBoolean(const string& token)
{
	return (token == "true" || token == "false");
}

int toInt(const string& token)
{
	stringstream ss(token);
	int num;
	ss >> num;
	return num;
}

bool toBoolean(int num)
{
	return (num != 0);
}

vector<string> tokenize(const string& expr)
{
	istringstream iss(expr);
	vector<std::string> tokens;
	string token;
	while (iss >> token)
	{
		tokens.push_back(token);
	}
	return tokens;
}

int calculate(int num1, int num2, char op, bool isBoolean = false)
{
	if (isBoolean) 
	{
		num1 = toBoolean(num1);
		num2 = toBoolean(num2);
	}

	switch (op)
	{
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '*':
		return num1 * num2;
	case '/':
		cout << "Num1: " << num1 << ", Num2: " << num2 << endl;

		if (num2 == 0)
		{
			throw runtime_error("ERROR: Division by zero is not allowed");
		}
		return num1 / num2;
	case '%':
		if (num2 == 0)
		{
			throw runtime_error("ERROR: Division by zero is not allowed");
		}
		return num1 % num2;
	case '&':
		return num1 & num2; 
	case '|':
		return num1 | num2; 
	case '^':
		return num1 ^ num2; 
	default:
		throw runtime_error("ERROR: Invalid operation");
	}
}

int calculatePostfixExpr(const vector<string>& tokens)
{
	stack<int> stack;
	int num1, num2;

	for (const auto& token : tokens)
	{
		if (isNumber(token))
		{
			stack.push(toInt(token));
		}
		else if (isBoolean(token))
		{
			stack.push(toBoolean(toInt(token)));
		}
		else
		{
			if (stack.size() < 2)
			{
				throw runtime_error("ERROR: Invalid expression");
			}

			num1 = stack.top(); stack.pop();
			num2 = stack.top(); stack.pop();

			if (token == "/" && num2 == 0)
			{
				throw runtime_error("ERROR: Division by zero");
			}
			stack.push(calculate(num1, num2, token[0], true));
		}
	}

	if (stack.size() != 1)
	{
		throw runtime_error("ERROR: Invalid expression");
	}
	return stack.top();
}

int main()
{
	string expression;
	cout << "Enter a postfix expression: ";
	getline(cin, expression);

	try
	{
		vector<string> tokens = tokenize(expression);
		int result = calculatePostfixExpr(tokens);
		cout << result << endl;
	}
	catch (const exception & e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
