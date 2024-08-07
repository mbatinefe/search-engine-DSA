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

bool isContaints(string word, vector<string> unique_Word_Vector){
    for(long unsigned int i = 0; i < unique_Word_Vector.size(); i++){
        if(word == unique_Word_Vector[i]){
            return true;
        }
    }
    return false;
}

int getOccurenceNumber(string word, vector<string> Word_Vector){
    int count = 0;
    for(long unsigned int i = 0; i < Word_Vector.size(); i++){
        if(word == Word_Vector[i]){
            count++;
        }
    }
    return count;
}

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

        // Lets read the file
        string line;
        vector<string> word_Vector;
        while(getline(file, line)){
            // for each word in line, we will add to tree if unique
            // split line by space
            string word_Single = "";
            for(long unsigned int x = 0; x < line.size()+1; x++){
                // if there is space, add that substr before as word to vector
                if(line[x] == ' ' || x == line.size()){
                    // Lets check if word_Single is alphabetic
                    bool isAlphabetic = true;
                    for(long unsigned int j = 0; j < word_Single.size(); j++){
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
        for(long unsigned int m = 0; m < word_Vector.size(); m++){
            // If not unique, we will add the document to the vector
            if(!isContaints(word_Vector[m], unique_Word_Vector)){
                unique_Word_Vector.push_back(word_Vector[m]);
            }
        }

        // But, when we go through second file, we will have to add the new occurence on that word
        for(long unsigned int y = 0; y < unique_Word_Vector.size(); y++){
            int count = getOccurenceNumber(unique_Word_Vector[y], word_Vector);
            auto wordItem = make_shared<WordItem>(unique_Word_Vector[y]);
            auto docItem = make_shared<DocumentItem>(fileName, count);
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
            for(long unsigned int k = 0; k < query.size(); k++){
                if(query[k] == ' '){
                    break;
                } else{
                    word += query[k];
                }
            }
            // Delete the word from query
            query.erase(0, word.size()+1);
            queryWords.push_back(word);
        }

        vector<shared_ptr<WordItem>> tempWordItemVec;
        
        if(queryWords[0] == "ENDOFINPUT"){
            // We do not need to delete the tree since our deconstructor will do it
            // It will call makeEmpty function
            break;
        } else if (queryWords[0] == "REMOVE"){
            myTree.remove(queryWords[1]); 
        } else{

            bool isQueryFullExistAtAll = true;
            // Lets create wordItem list

            for (long unsigned int q = 0; q < queryWords.size(); q++){
                string word = toLower(queryWords[q]);
                // We will search the word in the tree
                if(myTree.isExists(word)){

                    // We will print the document information
                    auto wordItem = myTree.elementAt(word);

                    //cout << "Word: " << wordItem->word << " ------- ";
                    //cout << "Document Information: ";
                    for(long unsigned int u = 0; u < wordItem->docInfoVec.size(); u++){
                        bool isExistFile = false;
                        int indexOfExistFile = -1;
                        for(long unsigned int j = 0; j < tempWordItemVec.size(); j++){
                            if(tempWordItemVec[j]->word == wordItem->docInfoVec[u].documentName){
                                isExistFile = true;
                                indexOfExistFile = j;
                                break;
                            }
                        }
                        if(!isExistFile){
                            auto wordItemTemp = make_shared<WordItem>(wordItem->docInfoVec[u].documentName);
                            auto docItemTemp = make_shared<DocumentItem>(word, wordItem->docInfoVec[u].count);
                            wordItemTemp->docInfoVec.push_back(*docItemTemp);
                            tempWordItemVec.push_back(wordItemTemp);
                        } else{
                            auto docItemTemp = make_shared<DocumentItem>(word, wordItem->docInfoVec[u].count);
                            tempWordItemVec[indexOfExistFile]->docInfoVec.push_back(*docItemTemp);
                        }
                
                    }
                } else{
                    // cout << "Word: "<< word <<" not found" << endl;
                    isQueryFullExistAtAll = false;
                }
            }

            if(!isQueryFullExistAtAll){
                cout << "No document contains the given query" << endl;
            } else {

                int isQueryFullExistSameDoc = 0;
                // if all query words are in same tempWordItemVec[i].docInfoVec[j].documentName
                // we will print the document name
                for(long unsigned int u = 0; u < tempWordItemVec.size(); u++){

                    int queryCount = queryWords.size();
                    for(long unsigned int j = 0; j < tempWordItemVec[u]->docInfoVec.size(); j++){
                        for(long unsigned int e = 0; e < queryWords.size(); e++){
                            if(toLower(queryWords[e]) == tempWordItemVec[u]->docInfoVec[j].documentName){
                                queryCount--;
                            }
                        }
                    }

                    if(queryCount != 0){
                        continue;
                    } else {
                        isQueryFullExistSameDoc++;
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

                if(isQueryFullExistSameDoc == 0){
                    cout << "No document contains the given query" << endl;
                }
            }
        }
        tempWordItemVec.clear();
    }

    return 0;

}