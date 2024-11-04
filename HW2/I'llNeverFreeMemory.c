#include <stdio.h>
#include <stdlib.h>
int main() {
	char* forgot = (char*)malloc(sizeof(char) * 40);
	forgot  = "OMG... I forgot free my memory!!";
	printf("%s\n", forgot);
	return 0;
}
