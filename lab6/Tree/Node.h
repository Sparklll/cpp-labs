#ifndef NODE_H
#define NODE_H

template<class K, class D>
class Node
{
public:
    Node(K key, D data);
    Node<K, D> *leftChild;
    Node<K, D> *rightChild;

    K getKey() const;
    D getData() const;
    void setData(const D &value);

private:
    K key;
    D data;
};

template<class K, class D>
Node<K, D>::Node(K key, D data)
{
    this->key = key;
    this->data = data;
    leftChild = nullptr;
    rightChild = nullptr;
}

template<class K, class D>
K Node<K, D>::getKey() const
{
    return key;
}

template<class K, class D>
D Node<K, D>::getData() const
{
    return data;
}

template<class K, class D>
void Node<K, D>::setData(const D &value)
{
    data = value;
}

#endif // NODE_H
