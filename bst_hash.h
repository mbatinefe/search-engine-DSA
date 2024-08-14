// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 3

#ifndef _BST_HASH_H
#define _BST_HASH_H

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

/*
--------------------- AVL Search Tree ---------------------
*/
template <class Key, class Value >
class BinarySearchTree
{
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree & rhs);
        ~BinarySearchTree();

        const Value & elementAt(const Key & x) const;
        const Key & findMin() const;
        bool isExists(const Key & x) const;

        bool isEmpty() const;
        void makeEmpty();
        void insert(const Key & x, const Value & y);

        const BinarySearchTree & operator=(const BinarySearchTree &rhs);
    
    private:

        struct BinaryNode{
            Key key;
            Value value;
            BinaryNode *left;
            BinaryNode *right;
            int height;
            BinaryNode(const Key& theKey, const Value& theValue, BinaryNode *lt, BinaryNode *rt, int h=0)
                    : key(theKey), value(theValue), left(lt), right(rt), height(h) {}
        };

        BinaryNode *root;

        const Value & elementAt(const Key & x, BinaryNode * t) const;

        void insert(const Key & x, const Value & y, BinaryNode * & t ) const;

        BinaryNode * findMin(BinaryNode *t) const;
        bool isExists(const Key & x, BinaryNode *t) const;

        void makeEmpty(BinaryNode* & t) const;
        BinaryNode * clone(BinaryNode *t) const;

};

/*
--------------------- Hash Table ---------------------
*/

template <class Key, class Value>
class HashTable
{
    public:
        HashTable(int size = 53);
        ~HashTable();

        HashTable(const HashTable & rhs): array(rhs.array), currentSize(rhs.currentSize) {}
        const Value & find(const Key & x) const;

        void makeEmpty();
        void insert(const Key & x, const Value & y);

        const Value & elementAt(const Key & x) const;
        bool isExists(const Key & x) const;

        const HashTable & operator=(const HashTable & rhs);

        enum EntryType { ACTIVE, EMPTY, DELETED };

        int getHashSize() const {
            return array.size();
        }

        int getHashCurSize() const {
            return currentSize;
        }

    private:
        struct HashEntry{
            Key key;
            Value value;
            EntryType info;

            HashEntry(const Key & k = Key(), const Value & v = Value(), EntryType i = EMPTY)
                    : key(k), value(v), info(i) {}
        };

        vector<HashEntry> array;
        int currentSize;

        bool isExists(const Key & x, HashTable *h) const;
        bool isActive(int currentPos) const;
        int findPos(const Key & x) const;
        void rehash();     

};

#endif

