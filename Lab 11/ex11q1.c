#include "ex11q1.h"

// ############################################################################
// Vector
// ############################################################################


// ############################################################################
// Linked List
// ############################################################################


// ############################################################################
// Doubly Linked List
// ############################################################################


// ############################################################################
// Main
// ############################################################################
int main(void) {
    char line[1000];
    // Uncomment each for loop as you implement that part

    clock_t begin_vec = clock();
    Vec* v = vec_create();

    for (int i = 0; i < 100000; i++) {
       int a, b;
       if (getchar() == 'i') {
           scanf("%s %d %s %d\n", line, &a, line, &b);
           vec_insert_at(v, b, a);
       } else {
           scanf("%s\n", line);
           vec_print(v);
       }
    }

    vec_free(v);
    clock_t end_vec = clock();

    clock_t begin_list = clock();
    LinkedList* l = list_create();

    for (int i = 0; i < 100000; i++) {
       int a, b;
       if (getchar() == 'i') {
           scanf("%s %d %s %d\n", line, &a, line, &b);
           list_insert_at(l, b, a);
       } else {
           scanf("%s\n", line);
           list_print(l);
       }
    }

    list_free(l);
    clock_t end_list = clock();

    clock_t begin_dlist = clock();
    DoublyLinkedList* dlist = dlist_create();

    for (int i = 0; i < 100000; i++) {
       int a, b;
       if (getchar() == 'i') {
           scanf("%s %d %s %d\n", line, &a, line, &b);
           dlist_insert_at(dlist, b, a);
       } else {
           scanf("%s\n", line);
           dlist_print(dlist);
       }
    }

    dlist_free(dlist);
    clock_t end_dlist = clock();

    fprintf(stderr, "Vector: %gs\n", (double)(end_vec - begin_vec) / CLOCKS_PER_SEC);
    fprintf(stderr, "Linked List: %gs\n", (double)(end_list - begin_list) / CLOCKS_PER_SEC);
    fprintf(stderr, "Doubly Linked List: %gs\n", (double)(end_dlist - begin_dlist) / CLOCKS_PER_SEC);
}
