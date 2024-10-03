#include <stdio.h>
#include <stdlib.h>

static char current, previous;
static int count;

void compress(char* fileLocation);

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("wzip: file1 [file2 ...]\n");
		return 1;
	}
	else {
		for (int i = 1; i < 2; i++)
			compress(argv[i]);

		fwrite(&count, sizeof(int), 1, stdout);
		fwrite(&previous, sizeof(char), 1, stdout);
	}
	return 0;
}

void compress(char* fileLocation) {
	FILE* fp = NULL;
	fp = fopen(fileLocation, "r");
	if (fp == NULL) {
		printf("wzip: cannot open file\n");
		exit(1);
	}

	while (1) {
		current = fgetc(fp);
		if (current == EOF) {
			break;
		}

		if (count > 0) {
			if (current == previous) {
				count++;
			} else {
				fwrite(&count, sizeof(int), 1, stdout);
				fwrite(&previous, sizeof(char), 1, stdout);
				count = 0;
			}
		}
		else {
			count++;
		}
		previous = current;
	}
	fclose(fp);
}