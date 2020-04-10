#ifndef HASHMAP_H
#define HASHMAP_H

#include "HashNode.h"
#include "HashNodeList.h"

template<class K, class V>
class HashMap
{
public:
    HashMap(int size);
    ~HashMap();

    int hashFunction(K key);
    void insertNode(HashNode<K, V> *node);
    void deleteNode(K key);
    HashNode<K, V> *find(K key);

    int getArraySize() const;
    HashNodeList<K, V> **getHashArray() const;

private:
    HashNodeList<K, V> **hashArray;
    int arraySize;
};

template<class K, class V>
HashMap<K, V>::HashMap(int size)
{
    arraySize = size;
    hashArray = new HashNodeList<K, V> *[size];
    for (int i = 0; i < arraySize; i++) {
        hashArray[i] = new HashNodeList<K, V>();
    }
}

template<class K, class V>
HashMap<K, V>::~HashMap()
{
    delete[] hashArray;
}

template<class K, class V>
int HashMap<K, V>::getArraySize() const
{
    return arraySize;
}

template<class K, class V>
HashNodeList<K, V> **HashMap<K, V>::getHashArray() const
{
    return hashArray;
}

//template<class K, class V>
//int HashMap<K, V>::hashFunction(K key)
//{}

template<class K, class V>
void HashMap<K, V>::insertNode(HashNode<K, V> *node)
{
    K key = node->getKey();
    int hashValue = hashFunction(key);
    hashArray[hashValue]->insertElement(node);
}

template<class K, class V>
void HashMap<K, V>::deleteNode(K key)
{
    int hashValue = hashFunction(key);
    hashArray[hashValue]->deleteElement(key);
}

template<class K, class V>
HashNode<K, V> *HashMap<K, V>::find(K key)
{
    int hashValue = hashFunction(key);
    HashNode<K, V> *node = hashArray[hashValue]->findElement(key);
    return node;
}

#endif // HASHMAP_H
