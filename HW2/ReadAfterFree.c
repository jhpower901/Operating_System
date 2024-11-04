#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
	srand((unsigned int)time(NULL));
	int index = rand()%100;
	int* arr = (int*)malloc(sizeof(int) * 100);
	free(arr);
	printf("arr[%02d]: %d\n", index, arr[index]);
	return 0;
}
