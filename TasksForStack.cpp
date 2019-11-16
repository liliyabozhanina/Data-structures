#include <iostream>
#include <stack>
#include <cstring>
#include <cassert>

int precedence(char c)
{
    if (c == '*' || c == '/') {
        return 2;
    }
    else if (c == '+' || c == '-') {
        return 1;
    }
    return  0;
}


std::string infixToPostfix(const std::string& expr)
{
    std::string postfixNotation;
    std::stack<char> s;
    for (size_t i = 0, sz = expr.size(); i < sz; i++) {
        if(expr[i] == '(') {
            s.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (s.size() && s.top() != '(') {
                postfixNotation.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else if ((expr[i] >= 'a' &&  expr[i] <= 'z') ||
                 (expr[i] >= '0' && expr[i] <= '9')) {
            postfixNotation.push_back(expr[i]);
        }
        else {
            while(s.size() && precedence(s.top()) >= precedence(expr[i])) {
                postfixNotation.push_back(s.top());
                s.pop();
            }
            s.push(expr[i]);
        }
    }
    while(s.size()) {
        postfixNotation.push_back(s.top());
        s.pop();
    }
    return postfixNotation;
}

int calculateRPN(const std::string& expr)
{
    std::string toRPN = infixToPostfix(expr);
    std::stack<int> s;
    for (size_t i = 0, sz = toRPN.size(); i < sz; i++) {
        if (toRPN[i] >= '0' && toRPN[i] <= '9') {
            s.push(toRPN[i] - '0');
        }
        else {
            int right = s.top();
            s.pop();
            int left = s.top();
            s.pop();
            switch (toRPN[i]) {
                case '+': s.push(left + right);break;
                case '-': s.push(left - right);break;
                case '*': s.push(left * right);break;
                case '/': s.push(left / right);break;
            }
        }
    }
    return s.top();
}

bool isPalindrome(const std::string& word)
{
    bool isPali = true;
    std::stack<char> reverse;
    for (unsigned i = 0; i < word.size(); i++) {
        reverse.push(word[i]);
    }

    for (unsigned i = 0; i < word.size(); i++) {
        if(reverse.top() != word[i]) {
            isPali = false;
            break;
        }
        reverse.pop();
    }
    return isPali;
}

void copyAndRevStack()
{
    std::stack<unsigned> orig;
    for (unsigned i = 0; i < 10; i++) {
        orig.push(i);
    }

    std::stack<unsigned> tmp, cpy;

    //Copy a Stack
    while (!orig.empty()) {
        tmp.push(orig.top());
        orig.pop();
    }

    while(!tmp.empty()) {
        cpy.push(tmp.top());
        orig.push(tmp.top());
        tmp.pop();
    }

    std::cout << "Orig | Cpy" << std::endl;
    while(orig.size()) {
        std::cout << orig.top() << " | " << cpy.top() << std::endl;
        orig.pop();
        cpy.pop();
    }


    //Reverse a Stack
    std::cout << "Orig | Rev" << std::endl;
    for (unsigned i = 0; i < 10; i++) {
        orig.push(i);
    }

    while(!orig.empty()) {
        tmp.push(orig.top());
        orig.pop();
    }

    while(!tmp.empty()) {
        cpy.push(tmp.top());
        tmp.pop();
    }

    while(!cpy.empty()) {
        orig.push(cpy.top());
        cpy.pop();
    }

    std::cout << "Reversed:" << std::endl;
    while(orig.size()) {
        std::cout << orig.top() << std::endl;
        orig.pop();
    }
}


// Check for correct braces in an expression
const char* const openBraces = "([{";
const char* const closeBraces = ")]}";

bool isOpen(char c)
{
    return strchr(openBraces, c) != nullptr;
}

bool isClose(char c)
{
    return strchr(closeBraces, c) != nullptr;
}

bool isMatch(char open, char close)
{
    assert (isOpen(open) && isClose(close));

    int openPos = strchr(openBraces, open) - openBraces;
    int closePos = strchr(closeBraces, close) - closeBraces;
    return openPos == closePos;
}

bool isBalanced(const std::string& expr)
{
    std::stack<char> s;
    for (size_t i=0, sz = expr.size(); i < sz; i++) {
        if (isOpen(expr[i])) {
            s.push(expr[i]);
        }
        else if (isClose(expr[i])) {
            if (s.empty()) {
                return false;
            }
            if (!isMatch(s.top(), expr[i])) {
                return false;
            }
            s.pop();
        }
        // else -> any symbols other than braces are ignored
    }

    return (s.empty());
}

int main()
{
    copyAndRevStack();

    std::cout << infixToPostfix("a+b*c-d*e") << "\n";
    std::cout << infixToPostfix("(a+b)*c") << "\n";
    std::cout << calculateRPN("2*3+4*(5-6)") << "\n";

    std::cout << std::boolalpha
        << isPalindrome("aabbaa") << "\n";

    std::cout << std::boolalpha
        << isBalanced("(asd[asd{asdasd]}abb)") << " "
        << isBalanced("(asd[asd{asdasd}]abb)") << std::endl;
    return 0;
}
/*
Задача 1 Имплементирайте class stack (динамичен масив).

а) Направете typedef за типа на данни в стека

б) Private данни:

    int maxsiz -- капацитет на стека
    int tos -- индекс, където стека свършва (top of stack)
    Type* arr -- динамичникя масив, където ще са данните

в) Функции:

    Stack::Stack(int maxsiz = 100), Stack::~Stack(), Stack(const Stack& rhs)
    Stack& operator=(const Stack& rhs)
    bool Stack::Empty() const
    bool Stack::Full() const
    void Push(Type a)
    Type Pop()

Задача 2 а) Напишете програма, която прочита от файл низ от '(' и ')'. Да се провери дали този низ е правилно скобуван. Това означава, че:

    броя отварящи и затвярящи скоби е равен // '()(' не е ок
    по никое време няма повече затварящи от отварящи скоби // ')(' не е ок

Използвайте класа stack с Type=char

б) Низът е комбинация от "()", "[]" и "{}". Не се позволява преплитане на скоби: низът "[(])" не е балансиран. За да го оправим, трябва да "разплетем" скобите: "[]()". Формално:

    w е балансиран, ако е от само един тип затварящи/отварящи скоби, отговорарящи на условията в а)
    w е балансиран, ако е от вида w1w2, където w1 и w2 за балансирани. В горния пример "[]()" е балансирано, понеже w1="()" и w2="[]"
    w е балансиран, ако е от вида (w1), [w1] или {w1}, където w1 е балансиран.

Упътване: условието е дълго, но задачата е не много по-трудна от а)

Задача 3 а) Изведете на екрана някой низ, който да се получава от входния с добавяне на скоби и да е правилно скобуван. Низът е във формат, описан в задача 2 б)

б) Същото като а), но се иска минимален брой добавания на скоби. Забележете, че пише минимален, а не най-малък, т.е. може да има няколко решения. Изберете най-удобното за вас. */
