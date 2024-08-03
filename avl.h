// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 2

#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <string>

using namespace std;

template <class Key, class Value >
class AvlSearchTree
{
    public:
        explicit AvlSearchTree();
        AvlSearchTree(const AvlSearchTree & rhs);
        ~AvlSearchTree();

        const Key & findMin() const;
        const Key & findMax() const;
        const Value & find(const Key & x) const;

        // void printTree() const;

        bool isEmpty() const;
        void makeEmpty();
        void insert(const Key & x, const Value & y);
        void remove(const Key & x);

        const AvlSearchTree & operator=(const AvlSearchTree &rhs);
    
    private:

        struct AVLNode{
            Key key;
            Value value;
            AVLNode *left;
            AVLNode *right;
            int height;
            AVLNode(const Key& theKey, const Value& theValue, AVLNode *lt, AVLNode *rt, int h=0)
                    : key(theKey), value(theValue), left(lt), right(rt), height(h) {}
        };

        AVLNode *root;
        const Key KEY_NOT_FOUND;
        const Value VALUE_NOT_FOUND;

        const Value & elementAt(AVLNode*t, const Key&) const;

        void insert(const Key & x, const Value & y, AVLNode * & t ) const;
        void remove(const Key & x, AVLNode * & t ) const;

        AVLNode * findMin(AVLNode *t) const;
        AVLNode * findMax(AVLNode *t) const;
        //AVLNode<Key, Value> *find(const Key & x, AVLNode *t) const; 

        void makeEmpty(AVLNode* & t) const;
        void printTree(AVLNode *t) const;
        AVLNode * clone(AVLNode *t) const;

        // Manipulations
        int height(AVLNode *t) const;
        void rotateWithLeftChild(AVLNode* & k2) const;
        void rotateWithRightChild(AVLNode * & k1) const;
        void doubleWithLeftChild(AVLNode * & k3) const;
        void doubleWithRightChild(AVLNode * & k1) const;
        void balance(AVLNode * & t) const;
};

#include "avl.cpp"
#endif

