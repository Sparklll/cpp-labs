#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <QVector>

template<class K, class D>
class Tree
{
public:
    Node<K, D> *findNode(K key);
    Node<K, D> *getNodeSuccessor(Node<K, D> *delNode);
    void insertNode(K key, D data);
    void deleteNode(K key);

    void _deleteTree(Node<K, D> *localRoot);
    void deleteTree(Node<K, D> *localRoot);

    void storeNodes(Node<K, D> *localRoot, QVector<Node<K, D> *> &nodes);
    Node<K, D> *buildBalancedTree(QVector<Node<K, D> *> &nodes, int start, int end);
    void balanceTree();

    void preOrder(Node<K, D> *localRoot);
    void inOrder(Node<K, D> *localRoot);
    void postOrder(Node<K, D> *localRoot);

    Tree();
    Tree(K key, D value);
    Node<K, D> *getRoot() const;

private:
    Node<K, D> *root;
};

template<class K, class D>
Tree<K, D>::Tree()
{
    root = nullptr;
}

template<class K, class D>
Tree<K, D>::Tree(K key, D value)
{
    root = new Node<K, D>(key, value);
}

template<class K, class D>
Node<K, D> *Tree<K, D>::getRoot() const
{
    return root;
}

template<class K, class D>
Node<K, D> *Tree<K, D>::findNode(K key)
{
    Node<K, D> *current = root;

    if (current != nullptr) {
        while (current->key != key) {
            if (key < current->key) {
                current = current->leftChild;
            } else {
                current = current->rightChild;
            }

            if (current == nullptr) {
                return nullptr;
            }
        }
    }
    return current;
}

template<class K, class D>
Node<K, D> *Tree<K, D>::getNodeSuccessor(Node<K, D> *delNode)
{
    Node<K, D> *successorParent = delNode;
    Node<K, D> *successor = delNode;
    Node<K, D> *current = delNode->rightChild;

    while (current != nullptr) {
        successorParent = successor;
        successor = current;
        current = current->leftChild;
    }

    if (successor != delNode->rightChild) {
        successorParent->leftChild = successor->rightChild;
        successor->rightChild = delNode->rightChild;
    }
    return successor;
}

template<class K, class D>
void Tree<K, D>::insertNode(K key, D data)
{
    Node<K, D> *newNode = new Node<K, D>(key, data);

    if (root == nullptr) {
        root = newNode;
    } else {
        Node<K, D> *current = root;
        Node<K, D> *parent;
        bool searchPosition = true;
        bool isLeftChild = true;

        while (searchPosition) {
            parent = current;

            if (key < current->key) {
                isLeftChild = true;
                current = current->leftChild;
                if (current == nullptr) {
                    parent->leftChild = newNode;
                    searchPosition = false;
                }

            } else if (key == current->key) {
                current->data = data;
                searchPosition = false;
            } else if (key > current->key) {
                isLeftChild = false;
                current = current->rightChild;
                if (current == nullptr) {
                    parent->rightChild = newNode;
                    searchPosition = false;
                }
            }
        }
    }
}

template<class K, class D>
void Tree<K, D>::deleteNode(K key)
{
    Node<K, D> *current = root;
    Node<K, D> *parent = root;
    bool isLeftChild = true;

    if (current != nullptr) {
        while (current->key != key) {
            parent = current;
            if (key < current->key) {
                isLeftChild = true;
                current = current->leftChild;
            } else {
                isLeftChild = false;
                current = current->rightChild;
            }
            if (current == nullptr) {
                return;
            }
        }

        if (current->leftChild == nullptr && current->rightChild == nullptr) {
            if (current == root) {
                root = nullptr;
            } else if (isLeftChild) {
                parent->leftChild = nullptr;
            } else {
                parent->rightChild = nullptr;
            }
        } else if (current->rightChild == nullptr) {
            if (current == root) {
                root = current->leftChild;
            } else if (isLeftChild) {
                parent->leftChild = current->leftChild;
            } else {
                parent->rightChild = current->leftChild;
            }
        } else if (current->leftChild == nullptr) {
            if (current == root) {
                root = current->rightChild;
            } else if (isLeftChild) {
                parent->leftChild = current->rightChild;
            } else {
                parent->rightChild = current->rightChild;
            }
        } else {
            Node<K, D> *successor = getNodeSuccessor(current);

            if (current == root) {
                root = successor;
            } else if (isLeftChild) {
                parent->leftChild = successor;
            } else {
                parent->rightChild = successor;
            }

            successor->leftChild = current->leftChild;
        }
        delete current;
    }
}

template<class K, class D>
void Tree<K, D>::storeNodes(Node<K, D> *localRoot, QVector<Node<K, D> *> &nodes)
{
    if (localRoot == nullptr) {
        return;
    }

    storeNodes(localRoot->leftChild, nodes);
    nodes.push_back(localRoot);
    storeNodes(localRoot->rightChild, nodes);
}

template<class K, class D>
Node<K, D> *Tree<K, D>::buildBalancedTree(QVector<Node<K, D> *> &nodes, int start, int end)
{
    if (start > end) {
        return nullptr;
    }

    int mid = (start + end) / 2;
    Node<K, D> *localRoot = nodes[mid];

    localRoot->leftChild = buildBalancedTree(nodes, start, mid - 1);
    localRoot->rightChild = buildBalancedTree(nodes, mid + 1, end);
    return localRoot;
}

template<class K, class D>
void Tree<K, D>::balanceTree()
{
    // Simple tree balancing
    QVector<Node<K, D> *> nodes;
    storeNodes(root, nodes);
    root = buildBalancedTree(nodes, 0, nodes.size() - 1);
}

template<class K, class D>
void Tree<K, D>::_deleteTree(Node<K, D> *localRoot)
{
    if (localRoot == nullptr) {
        return;
    }
    _deleteTree(localRoot->leftChild);
    _deleteTree(localRoot->rightChild);
    delete localRoot;
}

template<class K, class D>
void Tree<K, D>::deleteTree(Node<K, D> *localRoot)
{
    bool isNodeRoot = localRoot == root;
    _deleteTree(localRoot);
    if (isNodeRoot) {
        root = nullptr;
    }
}

template<class K, class D>
void Tree<K, D>::preOrder(Node<K, D> *localRoot)
{
    if (localRoot != nullptr) {
        // Manipulate with key/data;
        preOrder(localRoot->leftChild);
        preOrder(localRoot->rightChild);
    }
}

template<class K, class D>
void Tree<K, D>::inOrder(Node<K, D> *localRoot)
{
    if (localRoot != nullptr) {
        inOrder(localRoot->leftChild);
        // Manipulate with key/data;
        inOrder(localRoot->rightChild);
    }
}

template<class K, class D>
void Tree<K, D>::postOrder(Node<K, D> *localRoot)
{
    if (localRoot != nullptr) {
        postOrder(localRoot->leftChild);
        postOrder(localRoot->rightChild);
        // Manipulate with key/data;
    }
}

#endif // TREE_H
