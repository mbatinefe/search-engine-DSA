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

        cin.ignore();

        // Lets read the file
        string line;
        vector<string> word_Vector;
        while(getline(file, line)){
            // for each word in line, we will add to tree if unique
            // split line by space
            string word_Single = "";
            for(int i = 0; i < line.size(); i++){
                // if there is space, add that substr before as word to vector
                if(line[i] == ' '){
                    // Lets check if word_Single is alphabetic
                    for(int j = 0; j < word_Single.size(); j++){
                        if(!isalpha(word_Single[j])){
                            cout << "Word is not alphabetic" << endl;
                        } else{
                            // Word is aplhabetic and punctation is ignored
                            // Lets lowercase the word
                            for(int k = 0; k < word_Single.size(); k++){
                                word_Single[k] = tolower(word_Single[k]);
                            }
                            word_Vector.push_back(word_Single);
                        }
                        word_Single = "";
                    }
                } else{
                    // Lets continue if there is any punctation
                    if(ispunct(line[i])){
                        continue;
                    } else{
                        word_Single += line[i];
                    }
                }
            }

        }
        
        // Now, we have the vector, lowered, no punctation, and alphabetic
        

        // Lets create a tree
        //AvlSearchTree<string, WordItem*> tree;

   }
   
    while(true){
        cout << endl<<"Enter queried words in one line: " << endl;
        cin.ignore(); // what does this do? 
        // 
        getline(cin, query);

        cout<< query << endl;
        // Get first word
        string word = query.substr(0, query.find(" "));
        
        cout << word << endl;
        if(word == "ENDOFINPUT"){
            break;
        } else if (word == "REMOVE"){
            cout << "Time to Remove" << endl;
            break;  
        } else{
            cout << "Time to Insert" << endl;
            break;
        }
    }




}