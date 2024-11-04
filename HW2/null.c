/*First, write a simple program called null.c that creates a pointer to an integer, sets it to
 *NULL, and then tries to dereference it. Compile this into an executable called null. What
 *happens when you run this program?
**/
#include <stdio.h>

int main() {
	int* ptr = NULL;
	int x = *ptr;	//dereference NULL pointer
	return 0;
}
