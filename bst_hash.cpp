// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 3

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "bst_hash.h"

using namespace std;

/*
--------------------- Binary Search Tree ---------------------
*/

/*
    Public Functions
*/

// Constructor
template <class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree(){
    root = nullptr;
}

// Copy constructor
template <class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree(const BinarySearchTree &rhs)
{
    root = clone(rhs.root);
}

// Destructor
template <class Key, class Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    makeEmpty();
}

// Helper function for findMin -- public to call private
template <class Key, class Value>
const Key & BinarySearchTree<Key, Value>::findMin() const
{
    return findMin(root)->key;
}

// Helper function for elementAt -- public to call private
template <class Key, class Value>
const Value & BinarySearchTree<Key, Value>::elementAt(const Key &x) const
{
    return elementAt(x, root);
}

// Helper function for isExists -- public to call private
template <class Key, class Value>
bool BinarySearchTree<Key, Value>::isExists(const Key &x) const
{
    return isExists(x, root);
}

// Following function will check if tree is empty
template <class Key, class Value>
bool BinarySearchTree<Key, Value>::isEmpty() const
{
    if(root == nullptr){
        return true;
    }else{
        return false;
    }
}

// Helper function for makeEmpty -- public to call private
template <class Key, class Value>
void BinarySearchTree<Key, Value>::makeEmpty()
{
    makeEmpty(root);
}

// Helper function for insert -- public to call private
template <class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const Key &x, const Value &y)
{
    insert(x, y, root);
}

// Following function will assign the tree to another tree -- operator overloading
template <class Key, class Value>
const BinarySearchTree<Key, Value> & BinarySearchTree<Key, Value>::operator=(const BinarySearchTree &rhs)
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
const Value & BinarySearchTree<Key, Value>::elementAt(const Key & x, BinaryNode * t) const
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
    throw std::runtime_error("Key not found in BST tree");
}

// Following function will insert the word to tree
template <class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const Key &x, const Value &y, BinaryNode * &t) const
{
    if(t == nullptr){
        t = new BinaryNode(x, y, nullptr, nullptr);
    }else if(x < t->key){
        insert(x, y, t->left);
    }else if(t->key < x){
        insert(x, y, t->right);
    }else{
        // Duplicate; do nothing
        ;
    }
}

// Following function will find the minimum value in tree -- basically leftmost node
template <class Key, class Value>
typename BinarySearchTree<Key, Value>::BinaryNode * BinarySearchTree<Key, Value>::findMin(BinaryNode *t) const
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
bool BinarySearchTree<Key, Value>::isExists(const Key &x, BinaryNode *t) const {
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
void BinarySearchTree<Key, Value>::makeEmpty(BinaryNode * &t) const
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
typename BinarySearchTree<Key, Value>::BinaryNode * BinarySearchTree<Key, Value>::clone(BinaryNode *t) const
{
    if(t == nullptr){
        return nullptr;
    }else{
        return new BinaryNode(t->key, t->value, clone(t->left), clone(t->right));
    }
}


/*
--------------------- Hash Table ---------------------
*/

/*
    Public Functions
*/

// Following function will check if the int is prime
static bool isPrime(int n)
{
    if(n==2 || n==3){
        return true;
    }
    if(n==1 || n%2==0){
        return false;
    }
    for(int i=3; i*i<=n; i+=2){
        if(n%i==0){
            return false;
        }
    }
    return true;
}

// Following function will return the next prime number
static int nextPrime(int n)
{
    if(n%2==0){
        n++;
    }
    for(; !isPrime(n); n+=2){
    }
    return n;
}

// Constructor
template <class Key, class Value>
HashTable<Key, Value>::HashTable(int size)
{
    // Check if the size is prime
    if(!isPrime(size)){
        size = nextPrime(size);
    }
    array.resize(size);
    makeEmpty();
}

// Helper function for isExists -- public to call private
template <class Key, class Value>
bool HashTable<Key, Value>::isExists(const Key &x) const
{
    return isActive(findPos(x));
}

// Following function will return the value of key
template <class Key, class Value>
const Value & HashTable<Key, Value>::find(const Key &x) const
{
    int currentPos = findPos(x);
    if(isActive(currentPos)){
        return array[currentPos].value;
    }
    throw std::runtime_error("ITEM_NOT_FOUND");
}

// Following function will insert the key and value
template <class Key, class Value>
void HashTable<Key, Value>::insert(const Key &x, const Value &y)
{
    int currentPos = findPos(x);
    if(isActive(currentPos)){
        return;
    }
    array[currentPos] = HashEntry(x, y, ACTIVE);
    if(currentSize++ > array.size() * 0.90){
        this->rehash();
    }
}

// Following function will make the table empty
template <class Key, class Value>
void HashTable<Key, Value>::makeEmpty()
{
    currentSize = 0;
    for(int i = 0; i < array.size(); i++){
        array[i].info = EMPTY;
    }
}

// Deconstructor
template <class Key, class Value>
HashTable<Key, Value>::~HashTable()
{
    makeEmpty();
}

// Copy constructor -- operator overloading
template <class Key, class Value>
const HashTable<Key, Value> & HashTable<Key, Value>::operator=(const HashTable &rhs)
{
    if(this != &rhs){
        array = rhs.array;
        currentSize = rhs.currentSize;
    }
    return *this;
}

// Following function will return the value of key
template <class Key, class Value>
const Value & HashTable<Key, Value>::elementAt(const Key &x) const
{
    return find(x);
}

/*
    Private Functions
*/

// Following function will check if the key exists
template <class Key, class Value>
bool HashTable<Key, Value>::isExists(const Key &x, HashTable *h) const
{
    return h->isActive(h->findPos(x));
}

// Following function will rehash
template <class Key, class Value>
void HashTable<Key, Value>::rehash()
{
    vector<HashEntry> oldArray = array;
    
    cout << "rehashed..." << endl;

    // Create new double-sized, empty table
    array.resize(nextPrime(2 * oldArray.size()));
    for(int j = 0; j < array.size(); j++){
        array[j].info = EMPTY;
    }

    // Copy table over
    currentSize = 0;
    for(int i = 0; i < oldArray.size(); i++){
        if(oldArray[i].info == ACTIVE){
            insert(oldArray[i].key, oldArray[i].value);
        }
    }
    double loadFactor = double(currentSize) / double(array.size());
	cout << "previous table size:" << oldArray.size() << ", new table size: " << array.size() << ", current unique word count " << currentSize << ", current load factor: " << loadFactor << endl;
}

// Following function will return hashed value number
static int hashArray(const string &x, int tableSize) 
{
    int count = 0;
    for(size_t i = 0; i < x.length(); i++){
        count = 53 * count + x[i];
    }
    count %= tableSize;
    if(count < 0){
        count += tableSize;
    }
    return count;
}

// Following function will return the pos of given key
template <class Key, class Value>
int HashTable<Key, Value>::findPos(const Key &x) const
{
    int collisionNum = 0;
    int currentPos = hashArray(x, array.size());

    while(array[currentPos].info != EMPTY && array[currentPos].key != x)
    {
        currentPos += pow(++collisionNum, 2) ;
        currentPos %= array.size();
    }
    return currentPos;
}

// Following will check if the pos is active
template <class Key, class Value>
bool HashTable<Key, Value>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}