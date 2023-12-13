#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <array>
#include <queue>
#include <sstream>
#include "expression.h"

using namespace std;

template<typename K, typename V>
struct KeyValue {
    K key;
    V value;
    KeyValue* next;
};

template<typename K, typename V>
class DynamicArray {
    KeyValue<K, V>* buckets[26];

    int convert(K key) {
        return key % 26;
    }

public:
    DynamicArray () {
        for (int i = 0; i < 26; i++) {
            buckets[i] = nullptr;
        }
    }
    void insert(K key, V value) {
        int index = convert(key);
        KeyValue<K, V>* newNode = new KeyValue<K, V>{key, value, nullptr};
        newNode->next = buckets[index];
        buckets[index] = newNode;
    }

    V find(K key) {
        int index = convert(key);
        KeyValue<K, V>* node = buckets[index];
        while (node) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        throw std::exception();
    }
};

struct Operation
{
  char symbol;
  char op;
  int priority;
  char associativity;
};

class OperationSet
{
  DynamicArray<char, Operation> operations;
  public:
  void add(Operation op) 
  {
    operations.insert(op.symbol, op);
  }

  bool contains(char symbol) 
  {
    try 
    {
      operations.find(symbol);
      return true;
    } catch (...) 
      {
        return false;
      }
  }

  Operation get(char symbol) 
  {
    return operations.find(symbol);
  }
};

std::vector<std::string> tokenize(const std::string& expr) 
{
  std::istringstream iss(expr);
  std::vector<std::string> tokens;
  std::string token;
  std::string previousToken;
  while (iss >> token) 
  {
    tokens.push_back(token);
    if ((!previousToken.empty() && isdigit(previousToken[0]) && isdigit(token[0])) ||
      (previousToken == token && token == "-")) 
    {
      throw incorrect_expression("Incorrect expression");
    }
    previousToken = token;
 }
  return tokens;
}
bool isOnlySpaces(const std::string& str)
{
  bool onlySpaces = true;
  for(char c : str)
  {
    if(c != ' ')
    {
      onlySpaces = false;
      break;
    }
  }
  return onlySpaces;
}

void validateExpression(const std::string& expr, OperationSet& opSet) 
{
    if (expr.empty()) 
    {
      throw incorrect_expression("Expression is empty");
    }

    int balance = 0;
    for (size_t i = 0; i < expr.size(); i++) 
    {
      char c = expr[i];
      if (c == '(') 
      {
        balance++;
      } else if (c == ')') 
      {
        balance--;
        if (balance < 0) 
        {
         throw incorrect_expression("Unbalanced parentheses in expression");
        }
      } else if (!isdigit(c) && c != ' ' && !opSet.contains(c)) 
        {
          throw incorrect_expression("Invalid character in expression");
        }

        if (i > 0 && opSet.contains(expr[i-1]) && opSet.contains(c)) 
        {
          throw incorrect_expression("Consecutive operators in expression");
        }
    }

    if (balance != 0) 
    {
      throw incorrect_expression("Unbalanced parentheses in expression");
    }

    if (opSet.contains(expr[0]) || opSet.contains(expr[expr.size()-1])) 
    {
      throw incorrect_expression("Expression starts or ends with an operator");
    }
}

void performOperation(std::stack<double>& values, std::stack<char>& operators, OperationSet& opSet) 
{
    double right = values.top(); values.pop();
    double left = values.top(); values.pop();
    char op = operators.top(); operators.pop();

    if (!opSet.contains(op)) 
    {
      throw incorrect_expression("Operation not found in the input file");
    }

    switch (opSet.get(op).op) 
    {
      case '+': values.push(left + right); break;
      case '-': values.push(left - right); break;
      case '*': values.push(left * right); break;
      case '/': 
          if (right != 0) 
          {
            values.push(left / right); 
          } else 
          {
            throw incorrect_expression("Division by zero is not allowed");
          }
          break;
    }
}

///
/// @brief Evaluates an expression.
///
/// @param expression
///   A null-terminated string that contains the expression.
/// @param ops
///   An input stream which contains the descriptions of all operations used in the expression.
///
/// @return The calculated value of the expression
///
double evaluate(const char* expression, std::istream& ops)
{
  if (expression == nullptr) 
  {
    throw incorrect_expression("Expression is null");
  }

  std::string expr(expression);

  if (expr.empty() || isOnlySpaces(expr)) 
  {
    return 0;
  }

  OperationSet opSet;
  char symbol;
  char op;
  int priority;
  char associativity;

  std::istringstream iss(expression);

  if (!(iss >> symbol >> op >> priority >> associativity)) 
  {
    throw std::invalid_argument("Invalid expression");
  }

  while (ops >> symbol >> op >> priority >> associativity) 
  {
    opSet.add({symbol, op, priority, associativity});
  }

  validateExpression(expr, opSet);

  std::vector<std::string> tokens = tokenize(expr);

  std::stack<double> values;
  std::stack<char> operators;

  for (const auto& token : tokens) 
  {
      if (opSet.contains(token[0])) 
      {
          if (token[0] == '(') 
          {
            operators.push(token[0]);
          }
          else if (token[0] == ')') 
          {
              while (!operators.empty() && operators.top() != '(') 
              {
                performOperation(values, operators, opSet);
              }
              if (!operators.empty()) 
              {
                operators.pop();
              }
          }
          else 
          {
              auto currentOperator = opSet.get(token[0]);
              while (!operators.empty() && operators.top() != '(') 
              {
                auto topOperator = opSet.get(operators.top());
                bool isLeftAssociative = currentOperator.associativity == 'L' && topOperator.priority >= currentOperator.priority;
                bool isRightAssociative = currentOperator.associativity == 'R' && topOperator.priority > currentOperator.priority;
                if (isLeftAssociative || isRightAssociative) 
                {
                  performOperation(values, operators, opSet);
                } else 
                  {
                    break;
                  }
              }
              operators.push(token[0]);
          }
      } else {
          try 
          {
            values.push(std::stod(token));
          } catch (const std::invalid_argument& ia) 
          {
            std::cerr << "Invalid argument: " << ia.what() << '\n';
          }
      }
  }

  while (!operators.empty()) 
  {
    performOperation(values, operators, opSet);
  }

  return values.top();
}