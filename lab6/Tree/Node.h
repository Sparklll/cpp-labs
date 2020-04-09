#ifndef NODE_H
#define NODE_H

template<class K, class D>
class Node
{
public:
    K key;
    D data;
    Node<K, D> *leftChild;
    Node<K, D> *rightChild;

    Node(K key, D data);

private:
};

template<class K, class D>
Node<K, D>::Node(K key, D data)
{
    this->key = key;
    this->data = data;
    leftChild = nullptr;
    rightChild = nullptr;
}

#endif // NODE_H
