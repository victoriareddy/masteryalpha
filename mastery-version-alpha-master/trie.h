#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 256
#define FIRST_VALID_CHAR 32
#define ASCII_CHARS 128

typedef struct TrieNode {
    bool isWord;
    unsigned char activeChildren;
    struct TrieNode* children[ASCII_CHARS - FIRST_VALID_CHAR];
} trie_node_t;

typedef struct WordListNode {
  char* word;
  struct WordListNode* next;
} list_node_t;

void autocomplete(trie_node_t* root, char* prefix);
bool insert(trie_node_t* root, char* word);
void free_trie(trie_node_t* root);
void* _malloc(size_t size);