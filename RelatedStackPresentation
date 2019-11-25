#include <iostream>
#include <cassert>

using namespace std;

template <typename T> //realizirame dvoinite kutii chrez shablona na strukturata elem
struct elem
{
	T inf; //informacionna chast
	elem* link; //adresna chast
};

template <typename T = int>
class stack
{
public:
	//kanonichno predstavqne
	stack(); //konstruktor po podrazbirane - suzdava prazen stek (start e raven na NULL)
	~stack();
	stack(const stack&);
	stack& operator=(const stack&);

	//osnovni operacii
	bool empty() const; //chlen-funkciq, opredelqshta dali neqvniqt stek e prazen
	void push(const T&); //ukazaniqt chrez formalniq parametur element se dobavq v neqvniq stek
	void pop(T&); //otstranqva element ot neqvniq stek, v sluchai che posledniqt ne e prazen i vrushta otstraneniqt element v ukazaniq formalen parametur
	void top(T&) const; //bez da otstranqva element ot neqvniq stek, v sluchai che posledniqt ne e prazen, namira vurha my i go zapisva v ukazaniq formalen parametur
	void print(); //chlen-funkciq, koqto izvejda na ekrana elementite na neqvniq stek
	int length(); //namira broq na elementite na neqvniq stek
private:
	elem<T>* start; //ukazatel kum vurha na steka
	void copyStack(const stack&); //pomoshtna chlen-funkciq, suzdavashta kopie na stek na drugo mqsto v dinamichnata pamet
	void deleteStack(); //pomoshtna chlen-funkciq, iztrivashta neqvniq stek
};

//kanonichno predstavqne na shablona na klasa
template <typename T>
stack<T>::stack()
{
	start = NULL;
}

template <typename T>
stack<T>::~stack()
{
	deleteStack();
}

template <typename T>
stack<T>::stack(const stack<T>& r)
{
	copyStack(r);
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& r)
{
	if (this != &r)
	{
		deleteStack();
		copyStack(r);
	}
	return *this;
}

//pomoshtna chlen-funkciq, koqto kopira r v neqvniq stek
template <typename T>
void stack<T>::copyStack(const stack<T>& r)
{
	if (r.start)
	{
		elem<T>* p = r.start, * q = NULL, * s = NULL;
		start = new elem<T>;
		assert(start != NULL);
		start->inf = p->inf;
		start->link = q;
		q = start;
		p = p->link;
		while (p)
		{
			s = new elem<T>;
			assert(s != NULL);
			s->inf = p->inf;
			q->link = s;
			q = s;
			p = p->link;
		}
		q->link = NULL;
	}
	else start = NULL;
}

//pomoshtna chlen-funkciq, koqto iztriva neqvniq stek
template <typename T>
void stack<T>::deleteStack()
{
	elem<T>* p;
	while (start)
	{
		p = start;
		start = start->link;
		delete p;
	}
}

//proverqva dali neqvniqt stek e prazen
template <typename T>
bool stack<T>::empty() const
{
	return start == NULL;
}

//vkluchva s v neqvniq stek
template <typename T>
void stack<T>::push(const T& s)
{
	elem<T>* p = start;
	start = new elem<T>;
	assert(start != NULL);
	start->inf = s;
	start->link = p;
}

//izkluchva element ot neqvniq stek i go zapisva v parametura s (operaciqta e vuzmojna, ako neqvniqt stek ne e prazen)
template <typename T>
void stack<T>::pop(T& s)
{
	if (start)
	{
		s = start->inf;
		elem<T>* p = start;
		start = start->link;
		delete p;
	}
	else
	{
		cout << "The stack is empty.\n";
		exit(1);
	}
}

//namira vurha na neqvniq stek i go zapisva v parametura s (operaciqta e vuzmojna, ako neqvniqt stek ne e prazen)
template <typename T>
void stack<T>::top(T& s) const
{
	if (start)
	{
		s = start->inf;
	}
	else
	{
		cout << "The stack is empty.\n";
		exit(1);
	}
}

//izvejda na ekrana elementie na neqvniq stek, kato predpolaga che za elementite ot tip T e definiran operator <<. Sled zavurshvane na izpulnenieto na funkciqta, neqvniqt stek stava prazen
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

//namira broq na elementite na neqvniq stek. Sled zavurshvane na izpulnenieto na funkciqta, neqvniqt stek stava prazen
template <typename T>
int stack<T>::length()
{
	int n = 0;
	T x;
	while (!empty())
	{
		pop(x);
		n++;
	}
	return n;
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
