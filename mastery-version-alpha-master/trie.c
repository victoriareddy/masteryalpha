#include "trie.h"
#include <stdio.h>

static void recurse_node(trie_node_t* root, char* word, size_t pos, bool* found_first);
static void free_trie_node(trie_node_t** node);

/**
 * Prints all words in the Trie with a given prefix (like autocomplete suggestions).
 * @param root the root of the Trie.
 * @param prefix the prefix to search with
 */
void autocomplete(trie_node_t* root, char* prefix) {
    if (!prefix) {
        return;
    }
    printf("finding all completions of prefix \"%s\":\n", prefix);
    int len = 0;
    trie_node_t* letter = root;
    char* itr = prefix;
    while (*itr && len < MAX_WORD_LENGTH) {
        letter = letter->children[*itr - FIRST_VALID_CHAR];
        itr++;
        len++;
    }
    char* word = malloc(MAX_WORD_LENGTH * sizeof(char));
    if (!word) {
        return;
    }
    bool found_first = false;
    strncpy(word, prefix, len); // type man strncpy if you havent seen strncpy before
    *(word + len) = '\0';
    recurse_node(letter, word, (size_t) len, &found_first);
    printf("\n");
    free(word);
}

static void recurse_node(trie_node_t* root, char* word, size_t pos, bool* found_first) {
    if (!root) {
        return;
    }
    if (root->isWord) {
        if (!*found_first) {
            printf("%s", word);
        } else {
            printf(" %s", word);
        }
        *found_first = true;
    }
    for (int i = 0; i < ASCII_CHARS - FIRST_VALID_CHAR; i++) {
        *(word+pos) = i + FIRST_VALID_CHAR;
        *(word+pos+1) = '\0';
        recurse_node(root->children[i], word, pos + 1, found_first);
    }
    *(word+pos) = '\0';
}

/**
 * Inserts a single word into the Trie
 * @param root the root of the Trie
 * @param word the word to insert
 * @return
 */
bool insert(trie_node_t* root, char* word) {
    if (!word) {
        return false;
    }
    int len = 0;
    while (*word && len < MAX_WORD_LENGTH) {
        if (!root->children[*word - FIRST_VALID_CHAR]) {
            root->children[*word - FIRST_VALID_CHAR] = (trie_node_t*) calloc(1, sizeof(trie_node_t));
        }
        root = root->children[*word - FIRST_VALID_CHAR];
        word++;
        len++;
    }
    bool res =  !root->isWord;
    root->isWord = true;
    return res;
}

/**
 * Cleans the trie up, freeing nodes in a post-order DFS
 * @param root the root of the Trie to clean up
 */
void free_trie(trie_node_t* root) {
    if (!root) {
        return;
    }
    for (int i = 0; i < ASCII_CHARS - FIRST_VALID_CHAR; i++) {
        free_trie(root->children[i]);
    }
    free_trie_node(&root);
}

static void free_trie_node(trie_node_t** node) {
    free(*node);
    *node = NULL;
}