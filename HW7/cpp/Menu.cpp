#include "../header/Trie.h"
#include "../header/Menu.h"

#include <iostream>

using namespace std;

void ShowMenu() {
    TrieNode* Dic = nullptr;
    int choice;

    while (true) {
        cout << "Commands: " << endl;
        cout << "1. Create dictionary" << endl;
        cout << "2. Look up word" << endl;
        cout << "3. Look up prefix" << endl;
        cout << "4. Remove word from dictionary" << endl;
        cout << "5. Exit" << endl;
        cout << "--------------------------------" << endl;
        cout << "Your choice: ";
        cin >> choice;

        if ((choice < 0) || (choice > 4)) break;
        switch (choice) {
            case 1:
                Command1(Dic);
                break;
            case 2:
                Command2(Dic);
                break;
            case 3:
                Command3(Dic);
                break;
            case 4:
                Command4(Dic);
                break;
            default:
                break;
        }

        cout << endl;
    }
    
    Delete(Dic);
    cout << endl << "Dictionary was deleted." << endl;
}

// Create dictionary
void Command1(TrieNode* &Dic) {
    string DicFile = "./input/HW6-dic.txt";
    cout << "Input file's name (file available: \"" << DicFile << "\"): ";
    cin >> DicFile;
    createTrie(Dic, DicFile);
}

// Look up a word
void Command2(TrieNode* Dic) {
    string word;
    cout << "Input a word to look up: ";
    cin >> word;
    int ID = lookUp(Dic, word);
    if (ID > 0)
        cout << "Word's ID: " << ID << endl;
    else
        cout << "Word does not exist." << endl;
}

// Look up words with prefix
void Command3(TrieNode* Dic) {
    string prefix;
    cout << "Input a prefix: ";
    cin >> prefix;
    vector<string> words = lookUpPrefix(Dic, prefix);
    cout << "Words with prefix: ";
    if (words.size() == 0)
        cout << "No word found." << endl;
    else {
        for (int i = 0; i < words.size(); ++i)
            cout << words[i] << " ";
        cout << endl;
    }
}

// Remove a word from dictionary
void Command4(TrieNode* Dic) {
    string word;
    cout << "Input word to delete: ";
    cin >> word;
    Remove(Dic, word);
    cout << "Word was removed." << endl;
}