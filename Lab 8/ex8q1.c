/* Purpose: Dynamically allocating memory to store values and indices in two parallel arrays
 * Author: Arib Amin
 * Date: 2023-11-01
 * Persons discussed w/: TA's on Discord
 * References: Binary Search Implementation: https://www.geeksforgeeks.org/binary-search/
 */

#include "ex8q1.h"

int main(void) {
    int is_print, value;
    float index;
    
    // float *indices = (float*)malloc(sizeof(float));
    // indices = NULL;
    // int *values = (int*)malloc(sizeof(int));
    // values = NULL;

    // Initializing pointers for indices and values arrays
    float *indices = NULL;
    int *values = NULL;
    int size = 0;

    // Looping until end of input
    while (!feof(stdin)) {
        // Read in line of input, if print line return 1, else return 0 for is_print
        read_line(&is_print, &index, &value);

        // If it is a print line input
        if (is_print == 1) {
            // Loop through the values array and print each value
            printf("[");
            for (int i = 0; i < size; i++){
                printf("%d", values[i]);
                // Print "," after each value except the last one
                if (i < size - 1){
                    printf(", ");
                }
            }
            printf("]\n");

        // If it is a store value line
        } else {
            // Initializing variable for insertion point (index where to insert new value)
            // Initializing variable to flag if the index already exists in indices array
            int insert_point = 0;
            int index_exists = 0;
            
            int left = 0;
            int right = size - 1;
            // Using binary search to see if user index already exists in indices array (sorted in ascending order)
            while (left <= right) {
                int mid = left + (right - left) / 2;
                // If index is found in indices array, trigger flag and break out of loop
                if (indices[mid] == index) {
                    insert_point = mid;
                    index_exists = 1;
                    break;
                } else if (indices[mid] < index) {
                    left = mid + 1;
                    // Update insert_point to index to the left of indices[mid] if less than user index
                    insert_point = left;
                } else {
                    right = mid - 1;
                }
            }

            // If the index value exists in indices array
            if (index_exists == 1){
                // Update value at insertion point in values array
                values[insert_point] = value;
            // If index value doesn't exist in indices array
            } else {
                // Allocate space in indices array for one additional float value
                indices = realloc(indices, (size + 1) * sizeof(float));
                // Allocate space in indices array for one additional int value
                values = realloc(values, (size + 1) * sizeof(int));

                // Move all values greater than user input values to the right
                for (int i = size; i > insert_point; i--){
                    indices[i] = indices[i - 1];
                    values[i] = values[i - 1];
                }

                // Update values in indices and values arrays with user inputs
                indices[insert_point] = index;
                values[insert_point] = value;

                // Increment counter for size of arrays
                size++;
            }
        }
    }
    // Free parallel arrays
    free(indices);
    free(values);

    return 0;
}
