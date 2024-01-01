/* Purpose: Using two ring buffers to insert into a queue at tail and middle of the line
 * Author: Arib Amin
 * Date: 2023-12-04
 * Persons discussed w/: TAs on Discord & Professor Lin Office Hours
 * References: https://en.wikipedia.org/wiki/Circular_buffer
 *             https://doc.rust-lang.org/std/collections/struct.VecDeque.html
 *             https://en.cppreference.com/w/cpp/container/deque
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *head;
    int *start;
    int *end;
    int length;
    int capacity;
} Ring;

void initialize_ring(Ring *ring, int capacity) {
    ring->head = (int *)malloc(capacity * sizeof(int));
    ring->start = ring->head;
    ring->end = ring->head;
    ring->length = 0;
    ring->capacity = capacity;
}

void resize_ring(Ring *ring, int new_capacity) {
    int* new_head = (int *)realloc(ring->head, new_capacity * sizeof(int));

    // Updating pointers to new memory
    ring->head = new_head;
    ring->start = new_head;
    ring->end = new_head + ring->length;
    ring->capacity = new_capacity;
}

void push_back(Ring *ring, int value) {
    if (ring->length == ring->capacity) {
        // Resizing ring buffer to 2 x capacity
        resize_ring(ring, ring->capacity * 2);
    }

    // Adding value to the end
    *(ring->end) = value;
    ring->end++;

    // Wrapping around if reaching end of speace
    if (ring->end == ring->head + ring->capacity) {
        ring->end = ring->head;
    }

    ring->length++;
}

void push_front(Ring *ring, int value) {
    if (ring->length == ring->capacity) {
        // Resizing ring buffer to 2 x capacity
        resize_ring(ring, ring->capacity * 2);
    }

    // Moving starting pointer back
    ring->start--;

    // Wrapping around if reaching beginning of space
    if (ring->start < ring->head) {
        ring->start = ring->head + ring->capacity - 1;
    }

    // Adding value the front
    *(ring->start) = value;

    ring->length++;
}

int pop_front(Ring *ring) {
    if (ring->length == 0) {
        // Empty ring buffer
        return -1;
    }

    int value = *(ring->start);
    ring->start++;

    // Wrapping around if reaching end of space
    if (ring->start == ring->head + ring->capacity) {
        ring->start = ring->head;
    }

    ring->length--;

    return value;
}

int pop_back(Ring* ring) {
    if (ring->length == 0) {
        // Empty ring buffer
        return -1;
    }

    ring->end--;

    // Wrapping around if reaching beginning of space
    if (ring->end < ring->head) {
        ring->end = ring->head + ring->capacity - 1;
    }

    int value = *(ring->end);
    ring->length--;

    return value;
}

int main() {
    Ring front_ring, back_ring;
    initialize_ring(&front_ring, 2000000);
    initialize_ring(&back_ring, 2000000);

    char action;
    int num_students, student_id;

    while (1) {
        if (scanf(" %c", &action) == EOF) {
            break; // Exitting on EOF
        }

        int result;
        if (action == 'N' || action == 'C') {
            if (scanf("%d %d", &num_students, &student_id) != 2) {
                // Clearing newline character
                while (getchar() != '\n');
                continue;
            }

            int condition = 1;
            if (action == 'N' && (front_ring.length + back_ring.length) >= num_students) {
                condition = 0;
            } else if (action == 'C' && (int)( ( ( (float)front_ring.length + (float)back_ring.length ) / 2) + 0.50) >= num_students) {
                condition = 0;
            }

            if (condition) {
                if (action == 'N') {
                    push_back(&back_ring, student_id);
                } else {
                    if (front_ring.length == back_ring.length) {
                        push_back(&front_ring, student_id);
                    } else {
                        push_front(&back_ring, student_id);
                    }
                }
            }

            // Rebalancing ring buffers
            while (front_ring.length > back_ring.length + 1) {
                int value = pop_front(&front_ring);
                push_back(&back_ring, value);
            }

            while (back_ring.length > front_ring.length) {
                int value = pop_front(&back_ring);
                push_back(&front_ring, value);
            }

        } else if (action == 'F') {
            result = pop_front(&front_ring);
            if (result != -1) {
                printf("%d\n", result);
            } else {
                printf("empty\n");
            }

            // Rebalancing ring buffers
            while (front_ring.length > back_ring.length + 1) {
                int value = pop_front(&front_ring);
                push_back(&back_ring, value);
            }

            while (back_ring.length > front_ring.length){
                int value = pop_front(&back_ring);
                push_back(&front_ring,value);
            }

        } else if (action == 'L') {
            if (back_ring.length == 0) {
                // Removing last element from front ring if back ring is empty
                pop_back(&front_ring);
            }

            // Removing last element from back ring
            pop_back(&back_ring);

            // Rebalancing ring buffers
            if (front_ring.length - back_ring.length == 2) {
                int value = pop_back(&front_ring);
                push_front(&back_ring, value);
            } else {
            // Rebalancing ring buffers
                while (front_ring.length > back_ring.length + 1) {
                    int value = pop_front(&front_ring);
                    push_back(&back_ring, value);
                }
            }
        }
    }
    // Freeing memory
    if (front_ring.head != NULL) {
        free(front_ring.head);
    }

    if (back_ring.head != NULL) {
        free(back_ring.head);
    }

    return 0;
}