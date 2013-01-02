#include <stdlib.h>
#include "trie.h"

inline char ord(char x) {
  return x == '\'' ? 26 : x - 'a';
}

trie* create() {
  trie* t = calloc(1, sizeof(trie));
  return t;
}

void destroy(trie* t) {
  int i;
  for(i = 0; i < 27; ++i)
    if(t->children[i])
      destroy(t->children[i]);
  free(t);
}

int trie_word_exists(const char* s, const trie* t) {
  if(*s == '\0') return 0;
  if(s[1] == '\0') return t->present;
  char x = ord(*s);
  if(t->children[x] == NULL) return 0;
  return trie_word_exists(s + 1, t->children[x]);
}

void trie_word_insert_(const char* s, trie* t) {
  if(s[1] != '\0') {
    char x = ord(*s);
    if(t->children[x] == NULL) 
      t->children[x] = (trie*) calloc(1, sizeof(trie));
    return trie_word_insert_(s + 1, t->children[x]);
  }
  t->present = 1;
}

void trie_word_insert(char* s, trie* t) {
  if(*s == '\0') return;
  trie_word_insert_(s, t);
}