#include <stdio.h>
#include <stdlib.h>

/* txt ���� �����Ͽ� stdout���� ����ϴ� �Լ�
 * @param: txt ���� ��ġ
 * @return: 1: �Ű����� X, file can not be opened
 */
void compress(char* fileLocation);

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("wzip: file1 [file2 ...]\n");
		return 1;
	}
	else {
		for (int i = 1; i < argc; i++)
			compress(argv[i]);
	}
	return 0;
}

void compress(char* fileLocation) {
	char current, previous;
	int count = 0;

	FILE* fp = NULL;
	fp = fopen(fileLocation, "r");
	if (fp == NULL) {
		printf("wzip: cannot open file\n");
		exit(1);
	}

	while (1) {
		current = fgetc(fp);
		if (current == EOF) {
			if (count > 0) {
				fwrite(&count, sizeof(int), 1, stdout);
				fwrite(&previous, sizeof(char), 1, stdout);
			}
			break;
		}

		if (count > 0) {
			if (current == previous)
				count++;
			else {
				fwrite(&count, sizeof(int), 1, stdout);
				fwrite(&previous, sizeof(char), 1, stdout);
				count = 0;
			}
		}
		else {
			count++;
			previous = current;
		}
	}
	fclose(fp);
}