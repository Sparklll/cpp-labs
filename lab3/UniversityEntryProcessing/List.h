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

#endif // LIST_H
