#ifndef HASHNODE_H
#define HASHNODE_H

template<class K, class V>
class HashNode
{
public:
    HashNode(K key, V value);

    HashNode<K, V> *next;
    K getKey() const;
    V getValue() const;
    void setValue(const V &value);

private:
    K key;
    V value;
};

template<class K, class V>
HashNode<K, V>::HashNode(K key, V value)
{
    next = nullptr;
    this->key = key;
    this->value = value;
}

template<class K, class V>
K HashNode<K, V>::getKey() const
{
    return key;
}

template<class K, class V>
V HashNode<K, V>::getValue() const
{
    return value;
}

template<class K, class V>
void HashNode<K, V>::setValue(const V &value)
{
    this->value = value;
}

#endif // HASHNODE_H
