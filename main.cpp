// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 2

#include <iostream>
#include <string>
#include <random>
#include <fstream>

#include "avl.h"

using namespace std;

int main(){

    cout << "Enter number of input files: ";
    int fileCount;
    cin >> fileCount;

    string query;
    for(int i = 0; i < fileCount; i++){
        cout << "Enter " << i+1 << ". file name: ";
        string fileName;
        cin >> fileName;

        ifstream file(fileName);
        if(!file.is_open()){
            cout << "File ERROR" << endl;
            return 1;
        }
   }
   
    while(true){
        cout << endl<<"Enter queried words in one line: " << endl;
        cin.ignore();
        getline(cin, query);

        // Get first word
        string word = query.substr(0, query.find(" "));
        
        if(word == "ENDOFINPUT"){
            break;
        } else if (word == "REMOVE"){
            cout << "Time to Remove" << endl;
        } else{
            cout << "Time to Insert" << endl;
        }
    }




}