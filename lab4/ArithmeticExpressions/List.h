#ifndef LIST_H
#define LIST_H

template<class T>
class List
{
public:
    List();
    ~List();

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    void insert(T data, int index);
    void removeAt(int index);
    void clear();
    int getSize();
    T &operator[](const int index);

private:
    class Node
    {
    public:
        Node *pNext;
        T data;

        Node(T data = T(), Node *pNext = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
        }
    };
    int size;
    Node *head;
};

template<class T>
List<T>::List()
{
    size = 0;
    head = nullptr;
}

template<class T>
List<T>::~List()
{
    clear();
}

template<class T>
void List<T>::push_front(T data)
{
    head = new Node(data, head);
    size++;
}

template<class T>
void List<T>::push_back(T data)
{
    if (head == nullptr) {
        head = new Node(data);
    } else {
        Node *currentNode = this->head;

        while (currentNode->pNext != nullptr) {
            currentNode = currentNode->pNext;
        }
        currentNode->pNext = new Node(data);
    }
    size++;
}

template<class T>
void List<T>::pop_front()
{
    if (head != nullptr) {
        Node *tempNode = head;
        head = head->pNext;
        delete tempNode;
        size--;
    }
}

template<class T>
void List<T>::pop_back()
{
    removeAt(size - 1);
}

template<class T>
void List<T>::insert(T data, int index)
{
    if (index == 0) {
        push_front(data);
    } else {
        Node *previousNode = this->head;

        for (int i = 0; i < index - 1; i++) {
            previousNode = previousNode->pNext;
        }

        Node *newNode = new Node(data, previousNode->pNext);
        previousNode->pNext = newNode;
        size++;
    }
}

template<class T>
void List<T>::removeAt(int index)
{
    if (index == 0) {
        pop_front();
    } else {
        Node *previousNode = this->head;
        for (int i = 0; i < index - 1; i++) {
            previousNode = previousNode->pNext;
        }

        Node *toDelete = previousNode->pNext;
        previousNode->pNext = toDelete->pNext;
        delete toDelete;
        size--;
    }
}

template<class T>
void List<T>::clear()
{
    while (size) {
        pop_front();
    }
}

template<class T>
T &List<T>::operator[](const int index)
{
    if (index < getSize()) {
        int counter = 0;
        Node *currentNode = this->head;

        while (currentNode != nullptr) {
            if (counter == index) {
                return currentNode->data;
            }
            currentNode = currentNode->pNext;
            counter++;
        }
    }
}

template<class T>
int List<T>::getSize()
{
    return size;
}

#endif // LIST_H