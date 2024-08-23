// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 3

#include <iostream>
#include <cstddef>

using namespace std;

// Following function will check if the int is prime
bool isPrime( int n )
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
int nextPrime( int n )
{
    if(n%2==0){
        n++;
    }
    for(; !isPrime(n); n+=2){
    }
    return n;
}

// Following function will return hashed value number
int hashArray(const string &x, int tableSize) 
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