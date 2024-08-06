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
    for(long long unsigned int i = 0; i < unique_Word_Vector.size(); i++){
        if(word == unique_Word_Vector[i]){
            return true;
        }
    }
    return false;
}

int getOccurenceNumber(string word, vector<string> Word_Vector){
    int count = 0;
    for(long long unsigned int i = 0; i < Word_Vector.size(); i++){
        if(word == Word_Vector[i]){
            count++;
        }
    }
    return count;
}

string toLower(string word){
    for(long long unsigned int i = 0; i < word.size(); i++){
        word[i] = tolower(word[i]);
    }
    return word;
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
            for(long long unsigned int x = 0; x < line.size()+1; x++){
                // if there is space, add that substr before as word to vector
                if(line[x] == ' ' || x == line.size()){
                    // Lets check if word_Single is alphabetic
                    bool isAlphabetic = true;
                    for(long long unsigned int j = 0; j < word_Single.size(); j++){
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
        for(long long unsigned int i = 0; i < word_Vector.size(); i++){
            // If not unique, we will add the document to the vector
            if(!isContaints(word_Vector[i], unique_Word_Vector)){
                unique_Word_Vector.push_back(word_Vector[i]);
            }
        }

        // But, when we go through second file, we will have to add the new occurence on that word
        for(long long unsigned int y = 0; y < unique_Word_Vector.size(); y++){
            int count = getOccurenceNumber(unique_Word_Vector[y], word_Vector);
            WordItem* wordItem = new WordItem(unique_Word_Vector[y]);
            DocumentItem* docItem = new DocumentItem(fileName, count);
            wordItem->docInfoVec.push_back(*docItem);
            if(myTree.isExists(unique_Word_Vector[y])){
                // It means we already have word_Item_Vector[y] in the tree
                // We will add the document to the vector
                //cout << "HEy there"  << unique_Word_Vector[y] << endl;
                //myTree.change(unique_Word_Vector[y])->docInfoVec.push_back(*docItem);
                
                myTree.elementAt(unique_Word_Vector[y])->docInfoVec.push_back(*docItem);
                
                //myTree.find(unique_Word_Vector[y])->docInfoVec.push_back(*docItem);
            } else {
                // We will add the word to the tree
                myTree.insert(unique_Word_Vector[y], wordItem);
            }


        }
   }
    
    myTree.printTree();

    while(true){
        cout << endl<<"Enter queried words in one line: ";
        vector<string> queryWords;
        // Lets assign getline into query
        getline(cin, query);
        while(query.size() != 0){
            string word = "";
            for(long long unsigned int i = 0; i < query.size(); i++){
                if(query[i] == ' '){
                    break;
                } else{
                    word += query[i];
                }
            }
            // Delete the word from query
            query.erase(0, word.size()+1);
            queryWords.push_back(word);
        }

        if(queryWords[0] == "ENDOFINPUT"){
            break;
        } else if (queryWords[0] == "REMOVE"){
            myTree.remove(queryWords[1]); 
        } else{

            bool isQueryFullExist = true;
            // Lets create wordItem list
            vector<WordItem*> tempWordItemVec;
            for (int q = 0; q < queryWords.size(); q++){
                string word = toLower(queryWords[q]);
                // We will search the word in the tree
                if(myTree.isExists(word)){

                    // We will print the document information
                    WordItem* wordItem = myTree.elementAt(word);

                    //cout << "Word: " << wordItem->word << " ------- ";
                    //cout << "Document Information: ";
                    for(unsigned int i = 0; i < wordItem->docInfoVec.size(); i++){
                        bool isExistFile = false;
                        int indexOfExistFile = -1;
                        for(unsigned int j = 0; j < tempWordItemVec.size(); j++){
                            if(tempWordItemVec[j]->word == wordItem->docInfoVec[i].documentName){
                                isExistFile = true;
                                indexOfExistFile = j;
                                break;
                            }
                        }
                        if(!isExistFile){
                            WordItem* wordItemTemp = new WordItem(wordItem->docInfoVec[i].documentName);
                            DocumentItem* docItemTemp = new DocumentItem(word, wordItem->docInfoVec[i].count);
                            wordItemTemp->docInfoVec.push_back(*docItemTemp);
                            tempWordItemVec.push_back(wordItemTemp);
                        } else{
                            DocumentItem* docItemTemp = new DocumentItem(word, wordItem->docInfoVec[i].count);
                            tempWordItemVec[indexOfExistFile]->docInfoVec.push_back(*docItemTemp);
                        }
                        //cout << wordItem->docInfoVec[i].documentName << " ";
                        //cout << wordItem->docInfoVec[i].count << " ";
                    }
                } else{
                    // cout << "Word: "<< word <<" not found" << endl;
                    isQueryFullExist = false;
                }
            }

            if(!isQueryFullExist){
                cout << "No document contains the given query" << endl;
            } else {
                // Lets print the document information
                for(unsigned int i = 0; i < tempWordItemVec.size(); i++){
                    cout << "in Document " << tempWordItemVec[i]->word << ", ";
                    for(unsigned int j= 0; j < tempWordItemVec[i]->docInfoVec.size(); j++){
                        cout << tempWordItemVec[i]->docInfoVec[j].documentName << " found ";
                        cout << tempWordItemVec[i]->docInfoVec[j].count << " times";
                        if(j+1 == tempWordItemVec[i]->docInfoVec.size()){
                            cout << ".";
                        } else{
                            cout << ", ";
                        }
                    }
                    cout << endl;
                }
            }

        }
    }

}