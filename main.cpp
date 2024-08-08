// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 2

#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

#include "avl.cpp"

using namespace std;

// Following function will check if the word is in the vector
bool isContaints(string word, vector<string> unique_Word_Vector){
    for(long unsigned int i = 0; i < unique_Word_Vector.size(); i++){
        if(word == unique_Word_Vector[i]){
            return true;
        }
    }
    return false;
}

// Following function will return the occurence number of the word in the vector
int getOccurenceNumber(string word, vector<string> Word_Vector){
    int count = 0;
    for(long unsigned int i = 0; i < Word_Vector.size(); i++){
        if(word == Word_Vector[i]){
            count++;
        }
    }
    return count;
}

// Following function will lower the string
string toLower(string word){
    for(long unsigned int i = 0; i < word.size(); i++){
        word[i] = tolower(word[i]);
    }
    return word;
}

int main(){
    AvlSearchTree< string, shared_ptr<WordItem> > myTree;

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

        string line;
        vector<string> word_Vector;

        // Lets read the file line by line
        while(getline(file, line)){
            string word_Single = "";
            for(long unsigned int x = 0; x < line.size()+1; x++){
                if(line[x] == ' ' || x == line.size()){
                    // Lets check if word_Single is alphabetic
                    bool isAlphabetic = true;
                    for(long unsigned int j = 0; j < word_Single.size(); j++){
                        if(!isalpha(word_Single[j])){
                            isAlphabetic = false;
                        }
                    }
                    if(isAlphabetic){
                        // If yes, add to the vector
                        word_Vector.push_back(word_Single);
                    }
                    word_Single = "";
                }
                else{
                    // Lets continue if there is any punctation
                    if(ispunct(line[x])){
                        // Continue, if yes
                        continue;
                    } else{
                        line[x] = tolower(line[x]);
                        word_Single += line[x];
                    }
                }
            }

        }

        // Now, we have the vector, lowered, no punctation, and alphabetic
        // Lets create the unique word vector from word_Vector
        vector<string> unique_Word_Vector;
        for(long unsigned int m = 0; m < word_Vector.size(); m++){
            // If not unique, we will add the document to the vector
            if(!isContaints(word_Vector[m], unique_Word_Vector)){
                unique_Word_Vector.push_back(word_Vector[m]);
            }
        }

        // For each unique word, we will create a wordItem and documentItem
        for(long unsigned int y = 0; y < unique_Word_Vector.size(); y++){
            // count is the occurence number of the word in word_Vector
            int count = getOccurenceNumber(unique_Word_Vector[y], word_Vector);
            auto wordItem = make_shared<WordItem>(unique_Word_Vector[y]);
            auto docItem = make_shared<DocumentItem>(fileName, count);
            wordItem->docInfoVec.push_back(*docItem);
            if(myTree.isExists(unique_Word_Vector[y])){
                // It means we already have word_Item_Vector[y] in the tree
                // We will add the document to the vector 
                myTree.elementAt(unique_Word_Vector[y])->docInfoVec.push_back(*docItem);
            } else {
                // We will add the word to the tree as new
                myTree.insert(unique_Word_Vector[y], wordItem);
            }
        }
    }
    
    while(true){
        cout << endl<<"Enter queried words in one line: ";
        vector<string> queryWords;
        getline(cin, query);
        while(query.size() != 0){
            string word = "";
            for(long unsigned int k = 0; k < query.size(); k++){
                if(query[k] == ' '){
                    break;
                } else{
                    word += query[k];
                }
            }
            // Delete the word from query
            query.erase(0, word.size()+1);
            // Add the word
            queryWords.push_back(word);
        }

        vector<shared_ptr<WordItem>> tempWordItemVec;
        
        if(queryWords[0] == "ENDOFINPUT" || queryWords[0] == "endofinput"){
            // We do not need to delete tree since our deconstructor will do it
            break;
        } else if (toLower(queryWords[0]) == "remove" && !myTree.isEmpty()){
            if(myTree.isExists(queryWords[1])){
                myTree.remove(toLower(queryWords[1])); 
            } else{
                cout << "Word to be removed is not found or tree is empty." << endl;
            }
        } else{
            // We need to check if all query is in tree
            bool isQueryFullExistAtAll = true;
            for (long unsigned int q = 0; q < queryWords.size(); q++){
                string word = toLower(queryWords[q]);
                // We will search the word in the tree
                if(myTree.isExists(word)){
                    // Get the wordItem of that word
                    auto wordItem = myTree.elementAt(word);
                    /*
                        In here, I try different approach to get the document names
                        I put document names into wordItem, and word appeareance into DocumentItem
                        Then, I put the wordItem into tempWordItemVec
                        a.txt {                          b.txt {      
                            sabanci 2                     sabanci 1 
                            cs 2                          cs 4
                        }                                }
                    */
                    for(long unsigned int u = 0; u < wordItem->docInfoVec.size(); u++){
                        bool isExistFile = false; // If file is already on tempWordItemVec
                        int indexOfExistFile = -1;
                        for(long unsigned int j = 0; j < tempWordItemVec.size(); j++){
                            if(tempWordItemVec[j]->word == wordItem->docInfoVec[u].documentName){
                                isExistFile = true;
                                indexOfExistFile = j; // get index to push back
                                break;
                            }
                        }
                        if(!isExistFile){
                            // Meaning we do not have the file in tempWordItemVec
                            auto wordItemTemp = make_shared<WordItem>(wordItem->docInfoVec[u].documentName);
                            auto docItemTemp = make_shared<DocumentItem>(word, wordItem->docInfoVec[u].count);
                            wordItemTemp->docInfoVec.push_back(*docItemTemp);
                            tempWordItemVec.push_back(wordItemTemp);
                        } else{
                            // Meaning we have the file in tempWordItemVec
                            auto docItemTemp = make_shared<DocumentItem>(word, wordItem->docInfoVec[u].count);
                            tempWordItemVec[indexOfExistFile]->docInfoVec.push_back(*docItemTemp);
                        }
                    }
                } else{
                    isQueryFullExistAtAll = false;
                }
            }

            if(!isQueryFullExistAtAll){
                // Query word is not in the tree at all, but same doc check is later. 
                // This is to decrease running time
                cout << "No document contains the given query" << endl;
            } else {
                int isQueryFullExistSameDoc = 0;
                // If all query words are in same tempWordItemVec[i].docInfoVec[j].documentName
                // we will print the document name
                for(long unsigned int u = 0; u < tempWordItemVec.size(); u++){
                    int queryCount = queryWords.size();
                    for(long unsigned int j = 0; j < tempWordItemVec[u]->docInfoVec.size(); j++){
                        for(long unsigned int e = 0; e < queryWords.size(); e++){
                            if(toLower(queryWords[e]) == tempWordItemVec[u]->docInfoVec[j].documentName){
                                queryCount--; // We need to find every query word in document
                            }
                        }
                    }

                    if(queryCount != 0){
                        continue;
                    } else {
                        isQueryFullExistSameDoc++; // Saying we found the document
                        cout << "in Document " << tempWordItemVec[u]->word << ", ";
                        for(long unsigned int z= 0; z < tempWordItemVec[u]->docInfoVec.size(); z++){
                            cout << tempWordItemVec[u]->docInfoVec[z].documentName << " found ";
                            cout << tempWordItemVec[u]->docInfoVec[z].count << " times";
                            if(z+1 == tempWordItemVec[u]->docInfoVec.size()){
                                cout << ".";
                            } else{
                                cout << ", ";
                            }
                        }
                        cout << endl;
                    }

                }
                // Not all Query is found in the same document
                if(isQueryFullExistSameDoc == 0){
                    cout << "No document contains the given query" << endl;
                }
            }
        }
        tempWordItemVec.clear();
    }
    return 0;
}