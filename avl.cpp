// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 2

#include "avl.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

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




