#include <stdio.h>
#include <stdlib.h>

void decompress(char* filelocation);

int main (int argc, char** argv) {
  if (argc < 2) {
    printf("wunzip: file1 [file2 ...]\n");
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    decompress(argv[i]);
  }
  return 0;
}

void decompress(char* filelocation) {
  int count = 0;
  char current = 0;
  FILE* fp = NULL;
  fp = fopen(filelocation, "r");
  if (fp == NULL) {
    printf("wunzip: cannot open file\n");
    exit(1);
  }
  while(1) {
    if (fread(&count, 1, 4, fp) != 4)
      break;
    fread(&current, 1, 1, fp);
    for(int i = 0; i < count; i++)
      printf("%c", current);
  }
}
