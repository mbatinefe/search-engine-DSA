// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 3

#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <chrono>

#include "avl_hash.cpp"

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

// Following function will return the correct word vector, lowered, no punctation, and alphabetic
vector<string> getCorrectWordVector(vector<string> wordVector){
    vector<string> tempWordVector;
    // We will check if the word is alphabetic, or punctation
    for(long unsigned int i = 0; i < wordVector.size(); i++){
        string word = wordVector[i];
        string newWord = "";
        
        for(long unsigned int j = 0; j < word.size(); j++){
            if(isalpha(word[j])){
                newWord += word[j];
            }
            if(newWord != "" && !isalpha(word[j])){
                tempWordVector.push_back(toLower(newWord));
                newWord = "";
            }
                
        }
        if(newWord != ""){
            tempWordVector.push_back(toLower(newWord));
        }
    }

    // Now, check if wordVector has empty string
    for(long unsigned int i = 0; i < tempWordVector.size(); i++){
        if(tempWordVector[i] == ""){
            // Erase wordVector[i]
            tempWordVector.erase(tempWordVector.begin() + i);
        }
    }
    return tempWordVector;

}



int main(){
    AvlSearchTree< string, shared_ptr<WordItem> > myTree;
    HashTable<string, shared_ptr<WordItem>> myHash;
    cout << "Enter number of input files: ";
    int fileCount;
    cin >> fileCount;

    // Lets store the file names to string vector
    vector<string> fileNames;
    for(int i = 0; i < fileCount; i++){
        cout << "Enter " << i+1 << ". file name: ";
        string fileName;
        cin >> fileName;
        fileNames.push_back(fileName);
    }

    for(int i = 0; i < fileCount; i++){
        string fileNameX = fileNames[i];
        ifstream file(fileNameX);
        if(!file.is_open()){
            cout << "File ERROR" << endl;
            return 1;
        }

        string line;
        vector<string> word_Vector;

        // Lets read the file line by line
        while(getline(file, line)){
            vector<string> word_VectorTemp;
            istringstream iss(line);
            string word;
            while(iss >> word){
                word_VectorTemp.push_back(word);
            }

            word_VectorTemp = getCorrectWordVector(word_VectorTemp);
            // Add temp word vector to word vector since we might have more lines in doc
            for(long unsigned int k = 0; k < word_VectorTemp.size(); k++){
                word_Vector.push_back(word_VectorTemp[k]);
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
            auto docItem = make_shared<DocumentItem>(fileNameX, count);
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

        for(long unsigned int m = 0; m < unique_Word_Vector.size(); m++){
            // count is the occurence number of the word in word_Vector
            int count = getOccurenceNumber(unique_Word_Vector[m], word_Vector);
            auto wordItem = make_shared<WordItem>(unique_Word_Vector[m]);
            auto docItem = make_shared<DocumentItem>(fileNameX, count);
            wordItem->docInfoVec.push_back(*docItem);
            if(myHash.isExists(unique_Word_Vector[m])){
                // It means we already have word_Item_Vector[y] in the tree
                // We will add the document to the vector 
                myHash.elementAt(unique_Word_Vector[m])->docInfoVec.push_back(*docItem);
            } else {
                // We will add the word to the tree as new
                myHash.insert(unique_Word_Vector[m], wordItem);
            }
        }
        file.close();
    }
    cout << "\n\n";
    cout << "After preprocessing, the unique word count is " << myHash.getHashCurSize() <<
    ". Current load ratio is " << (double(myHash.getHashCurSize()) / double(myHash.getHashSize()));

    string query;
    cout << endl<<"Enter queried words in one line: ";
    vector<string> queryWords;
    cin.ignore(); // To ignore the newline character

    getline(cin, query);
    istringstream iss(query);
    string word;
    while(iss >> word){
        queryWords.push_back(word);
    }

    queryWords = getCorrectWordVector(queryWords);

    vector<shared_ptr<WordItem>> tempWordItemVecAVL;
    vector<shared_ptr<WordItem>> tempWordItemVecHash;
    
    if(toLower(queryWords[0]) == "endofinput"){
        // We do not need to delete tree since our deconstructor will do it
        return 0;
    } else{
        // We need to check if all query is in tree
        bool isQueryFullExistAtAllAVL = true;
        bool isQueryFullExistAtAllHash = true;

        int repeatCount = 20;
        auto start = chrono::high_resolution_clock::now();
        for (int r = 0; r < repeatCount; r++){
            // Clecn temp word item vector, since we will just repeat the process
            tempWordItemVecAVL.clear();
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
                        for(long unsigned int j = 0; j < tempWordItemVecAVL.size(); j++){
                            if(tempWordItemVecAVL[j]->word == wordItem->docInfoVec[u].documentName){
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
                            tempWordItemVecAVL.push_back(wordItemTemp);
                        } else{
                            // Meaning we have the file in tempWordItemVec
                            auto docItemTemp = make_shared<DocumentItem>(word, wordItem->docInfoVec[u].count);
                            tempWordItemVecAVL[indexOfExistFile]->docInfoVec.push_back(*docItemTemp);
                        }
                    }
                } else{
                    isQueryFullExistAtAllAVL = false;
                }
            }
        }
        auto BSTTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start);
    
        start = chrono::high_resolution_clock::now();
        for(int r = 0; r < repeatCount; r++){
            // Clecn temp word item vector, since we will just repeat the process
            tempWordItemVecHash.clear();
            for (long unsigned int q = 0; q < queryWords.size(); q++){
                string word = toLower(queryWords[q]);
                // We will search the word in the tree
                if(myHash.isExists(word)){
                    // Get the wordItem of that word
                    auto wordItem = myHash.elementAt(word);
                    for(long unsigned int u = 0; u < wordItem->docInfoVec.size(); u++){
                        bool isExistFile = false; // If file is already on tempWordItemVec
                        int indexOfExistFile = -1;
                        for(long unsigned int j = 0; j < tempWordItemVecHash.size(); j++){
                            if(tempWordItemVecHash[j]->word == wordItem->docInfoVec[u].documentName){
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
                            tempWordItemVecHash.push_back(wordItemTemp);
                        } else{
                            // Meaning we have the file in tempWordItemVec
                            auto docItemTemp = make_shared<DocumentItem>(word, wordItem->docInfoVec[u].count);
                            tempWordItemVecHash[indexOfExistFile]->docInfoVec.push_back(*docItemTemp);
                        }
                    }
                } else{
                    isQueryFullExistAtAllHash = false;
                }
            }

        }
        auto HashTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start);

        if(!isQueryFullExistAtAllAVL && !isQueryFullExistAtAllHash){
            // Query word is not in the tree at all, but same doc check is later. 
            // This is to decrease running time
            cout << "No document contains the given query" << endl;
            cout << "No document contains the given query" << endl;
        } else {
            int isQueryFullExistSameDocAVL = 0;
            int isQueryFullExistSameDocHash = 0;
            // If all query words are in same tempWordItemVec[i].docInfoVec[j].documentName
            // we will print the document name
            for(long unsigned int u = 0; u < tempWordItemVecAVL.size(); u++){
                int queryCount = queryWords.size();
                for(long unsigned int j = 0; j < tempWordItemVecAVL[u]->docInfoVec.size(); j++){
                    for(long unsigned int e = 0; e < queryWords.size(); e++){
                        if(toLower(queryWords[e]) == tempWordItemVecAVL[u]->docInfoVec[j].documentName){
                            queryCount--; // We need to find every query word in document
                        }
                    }
                }

                if(queryCount != 0){
                    continue;
                } else {
                    isQueryFullExistSameDocAVL++; // Saying we found the document
                    cout << "in Document " << tempWordItemVecAVL[u]->word << ", ";
                    for(long unsigned int z= 0; z < tempWordItemVecAVL[u]->docInfoVec.size(); z++){
                        cout << tempWordItemVecAVL[u]->docInfoVec[z].documentName << " found ";
                        cout << tempWordItemVecAVL[u]->docInfoVec[z].count << " times";
                        if(z+1 == tempWordItemVecAVL[u]->docInfoVec.size()){
                            cout << ".";
                        } else{
                            cout << ", ";
                        }
                    }
                    cout << endl;
                }

            }
            // Not all Query is found in the same document
            if(isQueryFullExistSameDocAVL == 0){
                cout << "No document contains the given query" << endl;
            }

            for(long unsigned int u = 0; u < tempWordItemVecHash.size(); u++){
                int queryCount = queryWords.size();
                for(long unsigned int j = 0; j < tempWordItemVecHash[u]->docInfoVec.size(); j++){
                    for(long unsigned int e = 0; e < queryWords.size(); e++){
                        if(toLower(queryWords[e]) == tempWordItemVecHash[u]->docInfoVec[j].documentName){
                            queryCount--; // We need to find every query word in document
                        }
                    }
                }

                if(queryCount != 0){
                    continue;
                } else {
                    isQueryFullExistSameDocHash++; // Saying we found the document
                    cout << "in Document " << tempWordItemVecHash[u]->word << ", ";
                    for(long unsigned int z= 0; z < tempWordItemVecHash[u]->docInfoVec.size(); z++){
                        cout << tempWordItemVecHash[u]->docInfoVec[z].documentName << " found ";
                        cout << tempWordItemVecHash[u]->docInfoVec[z].count << " times";
                        if(z+1 == tempWordItemVecHash[u]->docInfoVec.size()){
                            cout << ".";
                        } else{
                            cout << ", ";
                        }
                    }
                    cout << endl;
                }

            }
        
            // Not all Query is found in the same document
            if(isQueryFullExistSameDocHash == 0){
                cout << "No document contains the given query" << endl;
            }
        }
        cout << endl << "BST Time: " << BSTTime.count() << " nanoseconds" << endl;
        cout << "Hash Time: " << HashTime.count() << " nanoseconds" << endl;
        cout << "Speed Up: " << (double)BSTTime.count() / (double)HashTime.count() << endl;

    }
    tempWordItemVecAVL.clear();
    tempWordItemVecHash.clear();
    return 0;
}