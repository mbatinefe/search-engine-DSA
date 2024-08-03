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
        bool & find(const Key & x) const;

        void printTree() const;

        bool isEmpty() const;
        void makeEmpty();
        void insert(const Key & x, const Value & y);
        void remove(const Key & x);

        const AvlSearchTree & operator=(const AvlSearchTree &rhs);
    
    private:

        Struct AVLNode{
            Key key;
            Value value;
            AVLNode *left;
            AVLNode *right;
            int height;
            AvlNode(const Key& theKey, const Value& theValue, AvlNode *lt, AvlNode *rt, int h=0)
                    : key(theKey), value(theValue), left(lt), right(rt), height(h) {}
        };

        AvlNode *root;
        const Key KEY_NOT_FOUND;
        const Value VALUE_NOT_FOUND;

        const Value & elementAt(AvlNode*t, const Key&) const;

        void insert(const Key & x, const Value & y, AvlNode * & t ) const;
        void remove(const Key & x, AvlNode * & t ) const;

        AvlNode * findMin(AvlNode *t) const;
        AvlNode * findMax(AvlNode *t) const;
        bool find(const Key & x, AvlNode *t);
                                                                                                        const;
        void makeEmpty(AvlNode* & t) const;
        void printTree(AvlNode *t) const;
        AvlNode * clone(AvlNode *t) const;

        // Manipulations
        int height(AvlNode<Comparable> *t) const;
        void rotateWithLeftChild(AvlNode* & k2) const;
        void rotateWithRightChild(AvlNode * & k1) const;
        void doubleWithLeftChild(AvlNode * & k3) const;
        void doubleWithRightChild(AvlNode * & k1) const;
        void balance(AvlNode * & t) const;
};

#include "avl.cpp"
#endif