#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

int valid(char* s) {
  char* ptr = s;
  do {
    char x = *ptr;
    if(x == '\'') continue;
    if('A' >= x && 'Z' <= x) *ptr = tolower(x);
    else if ('z' < x || 'a' > x) return 0;
  } while(*++ptr);
  return 1;
}

int main() {
  const char dictionary[] = "large";
  const char input[] = "input";
  FILE *file = fopen (dictionary, "r");
  if(!file) exit(1);

  trie* t = create();

  char* line = NULL;
  size_t length;
  ssize_t read;
  while((read = getline(&line, &length, file)) != -1) {
    line[read - 1] = '\0';
    trie_insert(line, t);
    free(line);
    line = NULL;
  }
  free(line);
  fclose(file);

  printf("Dictionary loaded.\n");

  char delimiters[] = " \r\n";
  file = fopen(input, "r");
  if(!file) exit(2);
  line = NULL;
  int misspelled = 0, seen = 0, checked = 0;
  while((read = getline(&line, &length, file)) != -1) {
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
  destroy(t);
  return 0;
}