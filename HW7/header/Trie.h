#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

using namespace std;

#define ALPHABET_SIZE 26
#define DOES_NOT_EXIST -1
#define ROOT_ID 0

struct TrieNode {
    int ID; // If ID > 0: ID = ID of word in input file
            //       = 0: root, contain no words
            //       = -1: the word does not exist
    TrieNode* next[ALPHABET_SIZE];
};

TrieNode* getNode();
void Insert(TrieNode* &Dic, string word, int ID);
void Delete(TrieNode* &node);
void createTrie(TrieNode* &Dic, string DicFile);
int lookUp(TrieNode* Dic, string word);
vector<string> getAllWords(TrieNode* root, string prefix);
vector<string> lookUpPrefix(TrieNode* Dic, string prefix);
void Remove(TrieNode* Dic, string word);
bool Remove(TrieNode* Dic, string word, int index);

#endif