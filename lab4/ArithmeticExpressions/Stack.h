#ifndef STACK_H
#define STACK_H

#include "List.h"

template<class T>
class Stack : private List<T>
{
public:
    Stack();
    ~Stack();
    void push(T data);
    void pop();
    void clear();
    T top();
    int getSize();
    bool empty();
};

template<class T>
Stack<T>::Stack() : List<T>()
{}

template<class T>
Stack<T>::~Stack()
{}

template<class T>
void Stack<T>::push(T data)
{
    List<T>::push_front(data);
}

template<class T>
void Stack<T>::pop()
{
    List<T>::pop_front();
}

template<class T>
void Stack<T>::clear()
{
    List<T>::clear();
}

template<class T>
T Stack<T>::top()
{
    return List<T>::operator[](0);
}

template<class T>
int Stack<T>::getSize()
{
    return List<T>::getSize();
}

template<class T>
bool Stack<T>::empty()
{
    return getSize() == 0;
}

#endif // STACK_H
