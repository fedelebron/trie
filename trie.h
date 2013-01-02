#ifndef TRIE_H
#define TRIE_H


typedef struct trie_ {
  char present;
  struct trie_* children[27];
} trie;

trie* create();
void destroy(trie* t);
int trie_word_exists(const char* s, const trie* t);
void trie_insert(char* s, trie* t);

#endif