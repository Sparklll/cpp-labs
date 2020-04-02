#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class T>
struct Node
{
    Node *ptrPrev;
    Node *ptrNext;
    T data;

    Node(T data = T(), Node *ptrPrev = nullptr, Node *ptrNext = nullptr)
    {
        this->data = data;
        this->ptrPrev = ptrPrev;
        this->ptrNext = ptrNext;
    }
};

template<class T>
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    void insert(T data, int index);
    void removeAt(int index);
    void clear();
    int getSize();
    bool empty();
    T &back();
    T &front();

    T &operator[](const int index);

private:
    Node<T> *tail;
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    size = 0;
    head = nullptr;
    tail = nullptr;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template<class T>
void LinkedList<T>::push_front(T data)
{
    if (empty()) {
        head = new Node<T>(data);
        tail = head;
    } else {
        Node<T> *prevHead = head;
        Node<T> *newHead = new Node<T>(data, nullptr, prevHead);
        head = newHead;
        prevHead->ptrPrev = newHead;
    }

    size++;
}

template<class T>
void LinkedList<T>::push_back(T data)
{
    if (empty()) {
        tail = new Node<T>(data);
        head = tail;

    } else {
        Node<T> *prevTail = tail;
        Node<T> *newTail = new Node<T>(data, prevTail, nullptr);
        tail = newTail;
        prevTail->ptrNext = newTail;
    }
    size++;
}

template<class T>
void LinkedList<T>::pop_front()
{
    if (!empty()) {
        Node<T> *removableHead = head;
        head = removableHead->ptrNext;
        if (head != nullptr) {
            head->ptrPrev = nullptr;
        }

        delete removableHead;
        size--;
    }
}

template<class T>
void LinkedList<T>::pop_back()
{
    if (!empty()) {
        Node<T> *removableTail = tail;
        tail = removableTail->ptrPrev;
        if (tail != nullptr) {
            tail->ptrNext = nullptr;
        }

        delete removableTail;
        size--;
    }
}

template<class T>
void LinkedList<T>::insert(T data, int index)
{
    if (index >= 0 && index < getSize()) {
        Node<T> *indexNode;

        if (index <= (getSize() - 1) / 2) {
            indexNode = this->head;

            for (int i = 0; i < index; i++) {
                indexNode = indexNode->ptrNext;
            }
        } else {
            indexNode = this->tail;

            for (int i = getSize() - 1; i > index; i--) {
                indexNode = indexNode->ptrPrev;
            }
        }

        Node<T> *prevNode = indexNode->ptrPrev;
        Node<T> *newNode = new Node<T>(data, prevNode, indexNode);
        indexNode->ptrPrev = newNode;
        if (prevNode != nullptr) {
            prevNode->ptrNext = newNode;
        }

        if (index == 0) {
            head = newNode;
        } else if (index == getSize() - 1) {
            tail = newNode;
        }
        size++;
    }
}

template<class T>
void LinkedList<T>::removeAt(int index)
{
    if (index >= 0 && index < getSize()) {
        Node<T> *indexNode;

        if (index <= (getSize() - 1) / 2) {
            indexNode = this->head;

            for (int i = 0; i < index; i++) {
                indexNode = indexNode->ptrNext;
            }
        } else {
            indexNode = this->tail;

            for (int i = getSize() - 1; i > index; i--) {
                indexNode = indexNode->ptrPrev;
            }
        }

        Node<T> *prevNode = indexNode->ptrPrev;
        Node<T> *nextNode = indexNode->ptrNext;
        if (prevNode != nullptr) {
            prevNode->ptrNext = nextNode;
        }
        if (nextNode != nullptr) {
            nextNode->ptrPrev = prevNode;
        }

        if (index == 0) {
            head = nextNode;
        } else if (index == getSize() - 1) {
            tail = prevNode;
        }
        delete indexNode;
        size--;
    }
}

template<class T>
void LinkedList<T>::clear()
{
    while (size) {
        pop_front();
    }
}

template<class T>
int LinkedList<T>::getSize()
{
    return size;
}

template<class T>
bool LinkedList<T>::empty()
{
    return getSize() == 0;
}

template<class T>
T &LinkedList<T>::back()
{
    if (!empty()) {
        return tail->data;
    }
}

template<class T>
T &LinkedList<T>::front()
{
    if (!empty()) {
        return head->data;
    }
}

template<class T>
T &LinkedList<T>::operator[](const int index)
{
    Node<T> *indexNode;

    if (index >= 0 && index < getSize()) {
        if (index <= (getSize() - 1) / 2) {
            indexNode = this->head;

            for (int i = 0; i < index; i++) {
                indexNode = indexNode->ptrNext;
            }
        } else {
            indexNode = this->tail;

            for (int i = getSize() - 1; i > index; i--) {
                indexNode = indexNode->ptrPrev;
            }
        }
    }
    if (indexNode != nullptr) {
        return indexNode->data;
    }
}

#endif // LINKEDLIST_H
