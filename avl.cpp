// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 3

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "avl.h"

using namespace std;

/*
    Public Functions
*/

// Constructor
template <class Key, class Value>
AvlSearchTree<Key, Value>::AvlSearchTree(){
    root = nullptr;
}

// Copy constructor
template <class Key, class Value>
AvlSearchTree<Key, Value>::AvlSearchTree(const AvlSearchTree &rhs)
{
    root = clone(rhs.root);
}

// Destructor
template <class Key, class Value>
AvlSearchTree<Key, Value>::~AvlSearchTree()
{
    makeEmpty();
}

// Helper function for findMin -- public to call private
template <class Key, class Value>
const Key & AvlSearchTree<Key, Value>::findMin() const
{
    return findMin(root)->key;
}

// Helper function for elementAt -- public to call private
template <class Key, class Value>
const Value & AvlSearchTree<Key, Value>::elementAt(const Key &x) const
{
    return elementAt(x, root);
}

// Helper function for isExists -- public to call private
template <class Key, class Value>
bool AvlSearchTree<Key, Value>::isExists(const Key &x) const
{
    return isExists(x, root);
}

// Following function will check if tree is empty
template <class Key, class Value>
bool AvlSearchTree<Key, Value>::isEmpty() const
{
    if(root == nullptr){
        return true;
    }else{
        return false;
    }
}

// Helper function for makeEmpty -- public to call private
template <class Key, class Value>
void AvlSearchTree<Key, Value>::makeEmpty()
{
    makeEmpty(root);
}

// Helper function for insert -- public to call private
template <class Key, class Value>
void AvlSearchTree<Key, Value>::insert(const Key &x, const Value &y)
{
    insert(x, y, root);
}

// Helper function for remove -- public to call private
template <class Key, class Value>
void AvlSearchTree<Key, Value>::remove(const Key &x)
{
    remove(x, root);
}

// Following function will assign the tree to another tree -- operator overloading
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

// Following function will return the element for key x
template <class Key, class Value>
const Value & AvlSearchTree<Key, Value>::elementAt(const Key & x, AVLNode * t) const
{
    while (t != nullptr) {
        if (x < t->key) {
            return elementAt(x, t->left);
        } else if (t->key < x) {
            return elementAt(x, t->right);
        } else {
            return t->value;
        }
    }
    throw std::runtime_error("Key not found in AVL tree");
}

// Following function will insert the word to tree
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

// Following function will remove the word from tree
template <class Key, class Value>
void AvlSearchTree<Key, Value>::remove(const Key &x, AVLNode * &t) const
{   

    if(x < t->key){
        remove(x, t->left);
    }else if(t->key < x){
        remove(x, t->right);
    }else if(t->left != nullptr && t->right != nullptr){
        t->key = findMin(t->right)->key;
        remove(t->key, t->right);
    }else{
        AVLNode *removeNode = t;
        if (t->left != nullptr){
            t = t->left;
        } else if (t->right != nullptr){
            t = t->right;
        } else{
            t = nullptr;
        }
        delete removeNode;
        balance(t);
    }
}

// Following function will find the minimum value in tree -- basically leftmost node
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

// Following function will check if the word is in tree or not
template <class Key, class Value>
bool AvlSearchTree<Key, Value>::isExists(const Key &x, AVLNode *t) const {
    if(t == nullptr){
        return false;
    } else if(x < t->key){
        return isExists(x, t->left);
    } else if(t->key < x){
        return isExists(x, t->right);
    } else{
        return true;
    }
}

// Following function will empty the tree
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

// Following function will clone the tree
template <class Key, class Value>
typename AvlSearchTree<Key, Value>::AVLNode * AvlSearchTree<Key, Value>::clone(AVLNode *t) const
{
    if(t == nullptr){
        return nullptr;
    }else{
        return new AVLNode(t->key, t->value, clone(t->left), clone(t->right));
    }
}

// Following function will return the height
template <class Key, class Value>
int AvlSearchTree<Key, Value>::height(AVLNode *t) const
{
    if (t == nullptr){
        return -1;
    }else{
        return t->height;
    }
}

// Following function will rotate with left child
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

// Following function will rotate with right child
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

// Following function will double with left child
template <class Key, class Value>
void AvlSearchTree<Key, Value>::doubleWithLeftChild(AVLNode * &k3) const
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

// Following function will double with right child
template <class Key, class Value>
void AvlSearchTree<Key, Value>::doubleWithRightChild(AVLNode * &k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

// Following function will balance the tree
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
