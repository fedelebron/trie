#include <stdlib.h>
#include "trie.h"

inline unsigned char ord(char x) {
  return x == '\'' ? 26 : x - 'a';
}

trie* create() {
  trie* t = (trie*) calloc(1, sizeof(trie));
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
  unsigned char x;
  if(*s == '\0') return t->present;
  x = ord(*s);
  if(t->children[x] == NULL) return 0;
  return trie_word_exists(s + 1, t->children[x]);
}

void trie_word_insert(const char* s, trie* t) {
  unsigned char x;
  if(s[0] == '\0') {
    t->present = 1;
    return;
  }
  x = ord(*s);
  if(t->children[x] == NULL) 
    t->children[x] = create();
  trie_word_insert(s + 1, t->children[x]);
}