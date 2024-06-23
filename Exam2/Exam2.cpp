#include "Node.h"
#include <cstdlib> // За използване на std::rand()
#include <stdexcept>


//освобождаване на паметта, заета от елементите на списъка
//С тази функция, която приема указател към първия елемент на свързания списък, 
//можем да освободим паметта, заета от всички негови елементи. Ако lst е nullptr, 
//тя няма да прави нищо, както и е указано в условието.
inline void releaseList(Node* lst)
{
     while (lst != nullptr) cmake 
     {
        Node* temp = lst;
        lst = lst->next;
        delete temp;
    }
}

//генериране на произволен списък
//Тази функция създава свързан списък със случайно генерирани стойности в интервала [0, 99]. 
//Паметта за елементите се заделя чрез new, а при изключение от тип std::bad_alloc, коeто се 
//хвърля ако заделянето на памет не успее, функцията освобождава вече заделената памет 
//и препраща изключението нагоре.
inline Node* generateRandomList(size_t length)
{
    Node* first = nullptr;
    Node* current = nullptr;

    try {
        for (size_t i = 0; i < length; ++i) 
        {
            int randomValue = std::rand() % 100; // Генерираме случайно число в интервала [0,99]
            Node* newNode = new Node(randomValue);

            if (first == nullptr) 
            {
                first = newNode;
                current = first;
            } else {
                current->next = newNode;
                current = newNode;
            }
        }
    } catch (const std::bad_alloc&) {
        releaseList(first); // Почистваме заделената памет
        throw; // Препращаме изключението
    }
    return first;
}

//Тази функция премахва последователните повторения от свързания списък, като 
//освобождава паметта на дублиращите се елементи. Връща указател към първия елемент на променения списък.
inline Node* removeConsecutiveDuplicates(Node* lst)
{
    if (lst == nullptr) // Ако списъкът е празен, връщаме го както е
    {
        return lst;
    }

    Node* current = lst;
    while (current->next != nullptr) 
    {
        if (current->value == current->next->value) 
        {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }

    return lst;
}

//Тази функция слива два сортирани списъка в един сортиран списък, 
//като не заделя нова памет. Резултатът е указател към първия елемент на новия списък.
inline Node* mergeLists(Node* lst1, Node* lst2)
{
    Node temp;
    Node* current = &temp;

    while (lst1 != nullptr && lst2 != nullptr) 
    {
        if (lst1->value < lst2->value) 
        {
            current->next = lst1;
            lst1 = lst1->next;
        } else {
            current->next = lst2;
            lst2 = lst2->next;
        }
        current = current->next;
    }

    if (lst1 != nullptr) 
    {
        current->next = lst1;
    }
    if (lst2 != nullptr)
    {
        current->next = lst2;
    } 

    return temp.next;
}
