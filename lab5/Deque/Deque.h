#ifndef DEQUE_H
#define DEQUE_H

#include <LinkedList.h>

template<class T>
class Deque : private LinkedList<T>
{
public:
    Deque();

    void insertFront(T data);
    void insertRear(T data);
    void deleteFront();
    void deleteRear();
    T &getFront();
    T &getRear();
    int size();
    bool isEmpty();
    void erase();

    T &operator[](const int index);
};

template<class T>
Deque<T>::Deque() : LinkedList<T>()
{}

template<class T>
void Deque<T>::insertFront(T data)
{
    LinkedList<T>::push_front(data);
}

template<class T>
void Deque<T>::insertRear(T data)
{
    LinkedList<T>::push_back(data);
}

template<class T>
void Deque<T>::deleteFront()
{
    LinkedList<T>::pop_front();
}

template<class T>
void Deque<T>::deleteRear()
{
    LinkedList<T>::pop_back();
}

template<class T>
void Deque<T>::erase()
{
    LinkedList<T>::clear();
}

template<class T>
T &Deque<T>::getFront()
{
    LinkedList<T>::front();
}

template<class T>
T &Deque<T>::getRear()
{
    LinkedList<T>::back();
}

template<class T>
int Deque<T>::size()
{
    LinkedList<T>::getSize();
}

template<class T>
bool Deque<T>::isEmpty()
{
    LinkedList<T>::empty();
}

template<class T>
T &Deque<T>::operator[](const int index)
{
    LinkedList<T>::operator[](index);
}

#endif // DEQUE_H
