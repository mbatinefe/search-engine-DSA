// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 2

#include <vector>
#include <algorithm>
#include <iostream>
#include "avl.h"

using namespace std;

/*
    Public Functions
*/

template <class Key, class Value>
AvlSearchTree<Key, Value>::AvlSearchTree(){
    root = nullptr;
}

template <class Key, class Value>
AvlSearchTree<Key, Value>::AvlSearchTree(const AvlSearchTree &rhs)
{
    root = clone(rhs.root);
}

template <class Key, class Value>
AvlSearchTree<Key, Value>::~AvlSearchTree()
{
    makeEmpty();
}

template <class Key, class Value>
const Key & AvlSearchTree<Key, Value>::findMin() const
{
    return findMin(root)->key;
}

template <class Key, class Value>
const Key & AvlSearchTree<Key, Value>::findMax() const
{
    return findMax(root)->key;
}

template <class Key, class Value>
const Value & AvlSearchTree<Key, Value>::find(const Key &x) const
{
    return find(x, root);
}

template <class Key, class Value>
bool AvlSearchTree<Key, Value>::isEmpty() const
{
    if(root == nullptr){
        return true;
    }else{
        return false;
    }
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::makeEmpty()
{
    makeEmpty(root);
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::insert(const Key &x, const Value &y)
{
    insert(x, y, root);
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::remove(const Key &x)
{
    remove(x, root);
}

template <class Key, class Value>
const AvlSearchTree<Key, Value> & AvlSearchTree<Key, Value>::operator=(const AvlSearchTree &rhs)
{
    if(this != &rhs){
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}

/*
    Private Functions
*/

template <class Key, class Value>
const Value & AvlSearchTree<Key, Value>::elementAt(AVLNode *t, const Key &x) const
{
    if(t == nullptr){
        return VALUE_NOT_FOUND;
    }else if(x < t->key){
        return elementAt(t->left, x);
    }else if(t->key < x){
        return elementAt(t->right, x);
    }else{
        return t->value;
    }
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::insert(const Key &x, const Value &y, AVLNode * &t) const
{
    if(t == nullptr){
        t = new AVLNode(x, y, nullptr, nullptr);
    }else if(x < t->key){
        insert(x, y, t->left);
        if(height(t->left) - height(t->right) == 2){
            if(x < t->left->key){
                rotateWithLeftChild(t);
            }else{
                doubleWithLeftChild(t);
            }
        }
    }else if(t->key < x){
        insert(x, y, t->right);
        if(height(t->right) - height(t->left) == 2){
            if(t->right->key < x){
                rotateWithRightChild(t);
            }else{
                doubleWithRightChild(t);
            }
        }
    }else{
        // Duplicate; do nothing
        ;
    }
    t->height = max(height(t->left), height(t->right)) + 1;
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::remove(const Key &x, AVLNode * &t) const
{

}

template <class Key, class Value>
typename AvlSearchTree<Key, Value>::AVLNode * AvlSearchTree<Key, Value>::findMin(AVLNode *t) const
{
    if(t == nullptr){
        return nullptr;
    }else if(t->left == nullptr){
        return t;
    }else{
        return findMin(t->left);
    }
}

template <class Key, class Value>
typename AvlSearchTree<Key, Value>::AVLNode * AvlSearchTree<Key, Value>::findMax(AVLNode *t) const
{
    if(t != nullptr){
        while(t->right != nullptr){
            t = t->right;
        }
    }
    return t;
}

//template <class Key, class Value>
//AVLNode<Key, Value> *AvlSearchTree<Key, Value>::find(const Key &x, AVLNode *t) const


template <class Key, class Value>
void AvlSearchTree<Key, Value>::makeEmpty(AVLNode * &t) const
{
    if(t != nullptr){
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::printTree(AVLNode *t) const
{
    if(t != nullptr){
        printTree(t->left);
        cout << t->key << endl;
        printTree(t->right);
    }
}

template <class Key, class Value>
typename AvlSearchTree<Key, Value>::AVLNode * AvlSearchTree<Key, Value>::clone(AVLNode *t) const
{
    if(t == nullptr){
        return nullptr;
    }else{
        return new AVLNode(t->key, t->value, clone(t->left), clone(t->right));
    }
}

template <class Key, class Value>
int AvlSearchTree<Key, Value>::height(AVLNode *t) const
{
    if (t == nullptr){
        return -1;
    }else{
        return t->height;
    }
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::rotateWithLeftChild(AVLNode * &k2) const
{
    AVLNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::rotateWithRightChild(AVLNode * &k1) const
{
    AVLNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::doubleWithLeftChild(AVLNode * &k3) const
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::doubleWithRightChild(AVLNode * &k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

template <class Key, class Value>
void AvlSearchTree<Key, Value>::balance(AVLNode * &t) const
{
    if(t == nullptr){
        return;
    }
    if(height(t->left) - height(t->right) > 1){
        if(height(t->left->left) >= height(t->left->right)){
            rotateWithLeftChild(t);
        }else{
            doubleWithLeftChild(t);
        }
    }else{
        if(height(t->right) - height(t->left) > 1){
            if(height(t->right->right) >= height(t->right->left)){
                rotateWithRightChild(t);
            }else{
                doubleWithRightChild(t);
            }
        }
    }
}