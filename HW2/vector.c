/* 
 * 2024.11.04. 
 * electronic operating system
 * assignment 2
 * 
 * 
**/

#include <stdio.h>
#include <stdlib.h>

typedef int INT;
typedef struct _Vector {
    int size;
    int element_count;
    INT* data;
} Vector;

Vector* new_vector(int size) {
    Vector* v = (Vector*)malloc(sizeof(Vector));
    if (v == NULL) {
        printf("fail malloc operation<--Vector* v = (Vector*)malloc(sizeof(Vector));\n");
        return NULL;
    }
    v->size = size;
    v->element_count = 0;
    v->data = (INT*)calloc(size, sizeof(INT));
    if (v->data == NULL) {
        printf("fail allocate memoy<--v->data = (int*)calloc(size, sizeof(int));\n");
        return NULL;
    }
    printf(" Done!\n");
    return v;
}

INT* push_vector(Vector* v, int index, char* data) {
    printf("push %s to vector[%d]... ", data, index);
    if (v->element_count >= v->size ) {
        printf("realloc vector [%d->", v->size);
        if (v->size == 0)
            v->size = 1;
        INT* data = (INT*)realloc(v->data, (v->size = (v->size * 2)) * sizeof(INT));
        printf("%d]... ", v->size);
        if (data == NULL) {
            printf("fail realloc operation... ");
            v->size /= 2;
            return NULL;
        }
        v->data = data;
    }
    if (index < 0 || index > v->element_count) {
        *(v->data + v->element_count) = atoi(data);
        printf("done\n");
        return v->data + v->element_count++;
    } else {
        for (int i = v->element_count; index <= i; i--) {
            *(v->data + i) = *(v->data + i - 1);
        }
        *(v->data + index) = atoi(data);
        v->element_count++;
        printf("done\n");
        return v->data + index;
    }
}

void print_vector(Vector* v) {
    printf("[print Vector]\n");
    printf("size of vector: %d\n", v->size);
    printf("number of vector element: %d\n\n", v->element_count);
    printf(" No|     adress     | data\n");
    printf("---+----------------+-----\n");
    for (int i = 0; i < v->element_count; i++) {
        printf(" %02d %p  %04d\n", i, v->data + i, *(v->data + i));
    }
    printf("--------------------------\n");
}

void get_vector(Vector* v, int index) {
    if (0 <= index && index < v->element_count)
        printf("the %02dth elemenmt of the vector: vector[%02d] = %d\n", index, index, *(v->data + index));
    else
        printf("Invalid index...\n");
}

void delete_vector(Vector* v) {
    free(v->data);
    free(v);
}

int main(int argc, char* argv[]) {
    Vector *vec;
    INT* check;
    char* str[] = { "0", "111", "222", "333", "444", "555", "666"};

    printf("generate new vector...");
    vec = new_vector(0);
    if (vec == NULL) {
        printf("fail generate new vector... exit");
        return 1;
    }

    //push element in order
    for (int i = 1; i < argc; i++) {
        print_vector(vec);
        check = push_vector(vec, vec->element_count, argv[i]);
        if (check == NULL) {                    //realloc 실패한 경우
            printf("exit\n");
            return 1;
        }
        else if (*check != atoi(argv[i])) {         //삽입이 잘 됐는지 확인
            printf("fail push element...exit\n");
            return 1;
        }
    }

    //push element out of order
    for (int i = 0; i < 7; i++) {
        print_vector(vec);
        check = push_vector(vec, i, str[i]);
        if (check == NULL) {                    //realloc 실패한 경우
            printf("exit\n");
            return 1;
        }
        else if (*check != i*111) {         //삽입이 잘 됐는지 확인
            printf("fail push element...exit\n");
            return 1;
        }
    }

    //print element
    print_vector(vec);

    //get n th element
    for (int i = -1; i < vec->element_count+1; i++) {
        printf("get vector[%02d]: ", i);
        get_vector(vec, i);
    }

    delete_vector(vec);

    return 0;
}