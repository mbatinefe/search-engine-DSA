// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 3

#ifndef _AVL_H
#define _AVL_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct DocumentItem {
	string documentName;
	int count;

	DocumentItem(const string& n, int c) : documentName(n), count(c) {}
};

struct WordItem {
	string word;
	vector<DocumentItem> docInfoVec;

	WordItem(const string& w) : word(w) {}

};

template <class Key, class Value >
class AvlSearchTree
{
    public:
        AvlSearchTree();
        AvlSearchTree(const AvlSearchTree & rhs);
        ~AvlSearchTree();

        const Value & elementAt(const Key & x) const;
        const Key & findMin() const;
        bool isExists(const Key & x) const;

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

        const Value & elementAt(const Key & x, AVLNode * t) const;

        void insert(const Key & x, const Value & y, AVLNode * & t ) const;
        void remove(const Key & x, AVLNode * & t ) const;

        AVLNode * findMin(AVLNode *t) const;
        bool isExists(const Key & x, AVLNode *t) const;

        void makeEmpty(AVLNode* & t) const;
        AVLNode * clone(AVLNode *t) const;

        // Manipulations
        int height(AVLNode *t) const;
        void rotateWithLeftChild(AVLNode* & k2) const;
        void rotateWithRightChild(AVLNode * & k1) const;
        void doubleWithLeftChild(AVLNode * & k3) const;
        void doubleWithRightChild(AVLNode * & k1) const;
        void balance(AVLNode * & t) const;
};

#endif

