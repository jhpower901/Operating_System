#include <stdlib.h>
int main() {
	int* arr = (int*)malloc(sizeof(int) * 100);
	free(&arr[50]);
	return 0;
}
