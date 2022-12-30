#include "../header/Trie.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int getPositionInAlphabet(char ch) {
    return int(ch - 'a');
}

TrieNode* getNode() {
    TrieNode* newNode = new TrieNode;
    newNode->ID = DOES_NOT_EXIST;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        newNode->next[i] = nullptr;
    return newNode;
}

void Insert(TrieNode* &Dic, string word, int ID) {
    if (Dic == nullptr) {
        Dic = getNode();
        Dic->ID = ROOT_ID;
    }
    TrieNode* curNode = Dic;

    // Travese by each character in word
    for (int i = 0; i < word.length(); ++i) {
        int pos = getPositionInAlphabet(word[i]);
        // If Trie has not grown to the current character, expand it
        if (curNode->next[pos] == nullptr)
            for (int i = 0; i < ALPHABET_SIZE; ++i)
                curNode->next[i] = getNode();
        curNode = curNode->next[pos];
    }
    curNode->ID = ID;
}

void Delete(TrieNode* &node) {
    if (node == nullptr) return;

    for (int i = 0; i < ALPHABET_SIZE; ++i)
        Delete(node->next[i]);
    
    delete node;
    node = nullptr;
}

void createTrie(TrieNode* &Dic, string DicFile) {
    Delete(Dic);
    ifstream input(DicFile, ios::in);
    if (input.fail()) {
        cerr << "Cannot open \"" << DicFile << "\"" << endl;
        return;
    }

    int ID;
    string word;
    while (1) {
        input >> ID;
        input.ignore(2);
        input >> word;
        if (input.eof()) break;
        Insert(Dic, word, ID);
    }
    input.close();
}

TrieNode* findNode(TrieNode* Dic, string word) {
    TrieNode* curNode = Dic;
    for (int i = 0; (i < word.length()) && (curNode != nullptr); ++i) {
        int pos = getPositionInAlphabet(word[i]);
        curNode = curNode->next[pos];
    }
    return curNode;
}

int lookUp(TrieNode* Dic, string word) {
    TrieNode* node = findNode(Dic, word);
    if (node != nullptr) return node->ID;
    return DOES_NOT_EXIST;
}

vector<string> getAllWords(TrieNode* root, string prefix) {
    vector<string> res;
    if (root == nullptr) return res;

    if (root->ID > 0) res.push_back(prefix);

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        vector<string> subRes = getAllWords(root->next[i], prefix + char(i + 'a'));
        res.insert(res.end(), subRes.begin(), subRes.end());
    }

    return res;
}

vector<string> lookUpPrefix(TrieNode* Dic, string prefix) {
    TrieNode* node = findNode(Dic, prefix);
    return getAllWords(node, prefix);
}

void Remove(TrieNode* Dic, string word) {
    Remove(Dic, word, 0);
}

// If node to remove is leaf, return true, otherwise return false
bool Remove(TrieNode* Dic, string word, int index) {
    // If the word is not appear in dictionary, we do not need to remove any node
    if (Dic == nullptr) return false;

    if (index == word.length()) {
        Dic->ID = DOES_NOT_EXIST;

        for (int i = 0; i < ALPHABET_SIZE; ++i)
            if (Dic->next[i] != nullptr)
                return false;
        return true;
    }

    int pos = getPositionInAlphabet(word[index]);
    // If we remove a leaf, then its siblings may be useless. If so, remove them
    if (Remove(Dic->next[pos], word, index + 1)) {
        int i = 0;
        // Check if all the children contain no words
        for (; i < ALPHABET_SIZE; ++i) {
            int j = 0;
            for (; j < ALPHABET_SIZE; ++j)
                if (Dic->next[i]->next[j] != nullptr) break;
            if (j < ALPHABET_SIZE) break;
        }
        if (i == ALPHABET_SIZE) {
            for (int j = 0; j < ALPHABET_SIZE; ++j)
                delete Dic->next[j];
            if (Dic->ID == DOES_NOT_EXIST) return true;
            return false;
        }
    }
    
    return false;
}