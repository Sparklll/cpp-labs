#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include "HashNode.h"

template<class K, class V>
class HashNodeList
{
public:
    HashNodeList();
    ~HashNodeList();

    HashNode<K, V> *findElement(K key);
    void insertElement(HashNode<K, V> *node);
    void deleteElement(K key);

    HashNode<K, V> *getHead() const;

private:
    HashNode<K, V> *head;
};

template<class K, class V>
HashNodeList<K, V>::HashNodeList()
{
    head = nullptr;
}

template<class K, class V>
HashNodeList<K, V>::~HashNodeList()
{
    HashNode<K, V> *current = head;

    while (current != nullptr) {
        HashNode<K, V> *removableNode = current;
        current = current->next;
        delete removableNode;
    }
}

template<class K, class V>
HashNode<K, V> *HashNodeList<K, V>::getHead() const
{
    return head;
}

template<class K, class V>
HashNode<K, V> *HashNodeList<K, V>::findElement(K key)
{
    HashNode<K, V> *current = head;

    while (current != nullptr) {
        if (current->getKey() == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template<class K, class V>
void HashNodeList<K, V>::insertElement(HashNode<K, V> *node)
{
    K key = node->getKey();
    HashNode<K, V> *current = head;
    HashNode<K, V> *previous = head;

    if (current == nullptr) {
        head = node;
        return;
    }

    while (current != nullptr) {
        if (current->getKey() == node->getKey()) {
            current->setValue(node->getValue());
            return;
        }
        previous = current;
        current = current->next;
    }
    previous->next = node;
}

template<class K, class V>
void HashNodeList<K, V>::deleteElement(K key)
{
    HashNode<K, V> *previous = nullptr;
    HashNode<K, V> *current = head;

    while (current != nullptr && key != current->getKey()) {
        previous = current;
        current = current->next;
    }

    if (previous == nullptr && current != nullptr) {
        head = current->next;
    } else if (previous != nullptr && current != nullptr) {
        previous->next = current->next;
    } else {
        return;
    }
    delete current;
}

#endif // SORTEDLIST_H
