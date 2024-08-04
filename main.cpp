// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 2

#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <sstream>

#include "avl.h"

using namespace std;

bool isContaints(string word, vector<string> unique_Word_Vector){
    for(int i = 0; i < unique_Word_Vector.size(); i++){
        if(word == unique_Word_Vector[i]){
            return true;
        }
    }
    return false;
}

int getOccurenceNumber(string word, vector<string> Word_Vector){
    int count = 0;
    for(int i = 0; i < Word_Vector.size(); i++){
        if(word == Word_Vector[i]){
            count++;
        }
    }
    return count;
}

int main(){
    AvlSearchTree< string, WordItem *> myTree;

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
            for(int x = 0; x < line.size()+1; x++){
                // if there is space, add that substr before as word to vector
                if(line[x] == ' ' || x == line.size()){
                    // Lets check if word_Single is alphabetic
                    bool isAlphabetic = true;
                    for(int j = 0; j < word_Single.size(); j++){
                        if(!isalpha(word_Single[j])){
                            isAlphabetic = false;
                        }
                    }
                    if(isAlphabetic){
                        word_Vector.push_back(word_Single);
                    }
                    word_Single = "";
                }
                else{
                    // Lets continue if there is any punctation
                    if(ispunct(line[x])){
                        continue;
                    } else{
                        line[x] = tolower(line[x]);
                        word_Single += line[x];
                    }
                }
            }

        }

        
        // Now, we have the vector, lowered, no punctation, and alphabetic
        // WordItem struct is to check if how many times a word is in a document {{“a.txt”, 1}, {“b.txt”, 4}}
        // For each word in vector, we will check if it is in the tree
        // If it is, we will add the document to the vector with its count
        // Lets create the vector
        vector<string> unique_Word_Vector;
        for(int i = 0; i < word_Vector.size(); i++){
            // If not unique, we will add the document to the vector
            if(!isContaints(word_Vector[i], unique_Word_Vector)){
                unique_Word_Vector.push_back(word_Vector[i]);
            }
        }

        // But, when we go through second file, we will have to add the new occurence on that word
        for(int y = 0; y < unique_Word_Vector.size(); y++){
            int count = getOccurenceNumber(unique_Word_Vector[y], word_Vector);
            WordItem* wordItem = new WordItem(unique_Word_Vector[y]);
            DocumentItem* docItem = new DocumentItem(fileName, count);
            wordItem->docInfoVec.push_back(*docItem);
            if(myTree.isExists(unique_Word_Vector[y])){
                // It means we already have word_Item_Vector[y] in the tree
                // We will add the document to the vector
                cout << "HEy there"  << unique_Word_Vector[y] << endl;
                //myTree.find(unique_Word_Vector[y])->docInfoVec.push_back(*docItem);
            } else {
                // We will add the word to the tree
                myTree.insert(unique_Word_Vector[y], wordItem);
            }


        }
   }
    
    myTree.printTree();

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