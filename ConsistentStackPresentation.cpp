#include <iostream>
#include <cassert>

using namespace std;

const int MAXSIZE = 20;

template <typename T = int>
class stack
{
public:
	//kanonichno predstavqne
	stack(int = MAXSIZE); //konstruktor suzdavasht stek, razpolojen v dinamichnata pamet s ukazaniq chrez parametura razmer
	~stack(); //destruktor, razrushavasht neqvniq stek
	stack(const stack<T>&); //konstruktor za prisvoqvane, realizirasht kopiraneto na ukazaniq chrez parametura stek v neqvniq stek 
	stack <T>& operator=(const stack<T>&); //operatorna funkciq za prisvoqvane
	
	//osnovni operacii
	bool empty() const; //chlen-funkciq, opredelqshta dali neqvniq stek e prazen
	bool full() const; //chlen-funkciq, opredelqshta dali neqvniq stek e pulen
	void push(const T&); //ukazaniqt chrez formaniq parametur element se dobavq v neqvniq stek
	void pop(T&); //otstranqva element ot neqvniq stek, ako posledniq ne e prazen i vrushta otstraneniq element v ukazaniq formalen parametur
	void top(T&) const; //bez da otstranqva element, namira vurha na neqvniq stek, ako posledniqt ne e prazen i go zapisva v ukazaniq formalen parametur
	void print(); //izvejda na ekrana elementite na neqvniq stek
private:
	int stack_size; //maksimalen razmer na steka
	int stack_top; //vruh na steka
	T* arr; //nositel na steka
	void copyStack(const stack<T>&); //pomoshtna chlen-funkciq, suzdavashta kopie na stek na drugo mqsto v pametta
	void deleteStack(); //pomoshtna chlen-funkciq, razrushavashta neqvniq stek
};

//parametrichen konstruktor
template <typename T>
stack<T>::stack(int size)
{
	if (size <= 0)
		stack_size = MAXSIZE;
	else stack_size = size;
	arr = new T[stack_size];
	assert(arr != NULL);
	stack_top = -1;
}

//destruktor
template <typename T>
stack<T>::~stack()
{
	deleteStack();
}

//konstruktor za prisvoqvane 
template <typename T>
stack<T>::stack(const stack<T>& s)
{
	copyStack(s);
}

//operatorna funkciq za prisvoqvane
template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& st)
{
	if (this != &st)
	{
		deleteStack();
		copyStack(st);
	}
	return *this;
}

//pomoshtna chlen-funkciq, koqto kopira st v neqvniq stek
template <typename T>
void stack<T>::copyStack(const stack<T>& st)
{
	stack_size = st.stack_size;
	stack_top = st.stack_top;
	arr = new T[stack_size];
	assert(arr != NULL);
	for (int i = 0; i <= stack_top; i++)
		arr[i] = st.arr[i];
}

//pomoshtna chlen-funkciq, koqto iztriva neqvniq stek
template <typename T>
void stack<T>::deleteStack()
{
	delete[] arr;
}

//proverqva dali neqvniq stek e prazen
template <typename T>
bool stack<T>::empty() const
{
	return stack_top == -1;
}

//proverqva dali neqvniq stek e pulen
template <typename T>
bool stack<T>::full() const
{
	return stack_top == stack_size-1;
}

//namira vurha na neqvniq stek, ako posledniqt ne e prazen i go zapisva vuv formalniq parametur x
template <typename T>
void stack<T>::top(T& x) const
{
	if (!empty())
		x = arr[stack_top];
	else
	{
		cout << "The stack is empty.\n";
		exit(1);
	}
}

//vkluchva x v neqvniq stek, ako posledniqt ne e pulen
template <typename T>
void stack<T>::push(const T& x)
{
	if (!full())
	{
		stack_top++;
		arr[stack_top] = x;
	}
    else
	{
		cout << "The stack is full.\n";
		exit(1);
	}
}

//izkluchva element ot neqvniq stek, ako posledniqt ne e prazen i go zapisva v x
template <typename T>
void stack<T>::pop(T& x)
{
	if (!empty())
	{
		x = arr[stack_top];
		stack_top--;
	}
	else
	{
		cout << "The stack is empty.\n";
		exit(1);
	}
}

//izvejda na ekrana elementite na neqvniq stek kato go razrushava
template <typename T>
void stack<T>::print()
{
	T x;
	while (!empty())
	{
		pop(x);
		cout << x << " ";
	}
	cout << endl;
}

int main()
{
	stack<> st(3);
	st.push(10);
	st.push(20);
	st.push(30);
	stack<int> st1 = st, st2;
	st2 = st1;
	st2.print();
	return 0;
}
