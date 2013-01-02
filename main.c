#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

int valid(char* s) {
  char* ptr = s;
  do {
    char x = *ptr;
    if(x == '\'') continue;
    if('A' <= x && 'Z' >= x) *ptr = tolower(x);
    else if ('z' < x || 'a' > x) return 0;
  } while(*++ptr);
  return 1;
}

void read_dictionary(trie* t, FILE* dictionary) {
  char* line;
  size_t length;
  ssize_t read;
  line = NULL;
  while((read = getline(&line, &length, dictionary)) != -1) {
    line[read - 1] = '\0';
    trie_word_insert(line, t);
    free(line);
    line = NULL;
  }
  free(line);
}

void check_spelling(trie* t, FILE* text) {
  char* line = NULL;
  size_t length;
  ssize_t read;
  char delimiters[] = " \r\n\",.():!;-_?[]";
  int misspelled = 0, seen = 0, checked = 0;

  while((read = getline(&line, &length, text)) != -1) {
    char* ptr = strtok(line, delimiters);
    while(ptr != NULL) {
      seen++;
      if(valid(ptr)) {
        checked++;
        if(!trie_word_exists(ptr, t)) {
          misspelled++;
        }
      }
      ptr = strtok(NULL, delimiters);
    }
    free(line);
    line = NULL;
  }
  free(line);
  printf("Seen: %d, Checked: %d, Misspelled: %d\n", seen, checked, misspelled);
}

int main() {
  const char dictionary[] = "large";
  const char input[] = "input";
  trie* t;

  FILE *file = fopen (dictionary, "r");
  if(!file) exit(1);
  t = create();
  read_dictionary(t, file);
  fclose(file);
  printf("Dictionary loaded.\n");

  file = fopen(input, "r");
  if(!file) exit(2);
  check_spelling(t, file);
  fclose(file);
  
  destroy(t);
  return 0;
}