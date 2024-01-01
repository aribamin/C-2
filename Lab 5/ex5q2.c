/* Purpose: Solving magic square
 * Author: Arib Amin
 * Date: 2023-10-07
 * References: https://en.wikipedia.org/wiki/Magic_square
 */

#include "lab05.h"

// Do not touch anything in this main function (used for testing purposes)
int main(void) {
    return test_magic(magic);
}

int unused(int n, int grid[n][n], int num) {
    // Check if num is not in the grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == num) {
                return 0;
            }
        }
    }
    return 1;
}

// This function is a non-recursive function that checks whether a given grid[n][n] is a magic square.
// Complete the function definition:
int check(int n, int grid[n][n]) {
    // Calculate what sum of rows, columns, diagonals should be
    int sum = (n * (1 + n * n))/2;

    // Calculate if rows and columns equal correct sum
    for (int i = 0; i < n; i++){
        int row_sum = 0;
        int column_sum = 0;
        for (int j = 0; j < n; j++){
            row_sum += grid[i][j];
            column_sum+=grid[j][i];
        }
        if (row_sum != sum){
            return 0;
        }
        if (column_sum != sum){
            return 0;
        }
    }

    // Calculate if diagonals equal correct sum
    int diagonal_left_right = 0;
    int diagonal_right_left = 0;
    for (int i = 0; i < n; i++){
        diagonal_left_right += grid[i][i];
        diagonal_right_left += grid[i][n - i - 1];
    }
    if (diagonal_left_right != sum){
        return 0;
    }
    if (diagonal_right_left != sum){
        return 0;
    }    

    return 1;
}

// This function is a recursive function that intends to solve a given grid[n][n] as in the lab05 description.
// Complete the function definition:
int magic(int n, int grid[n][n]) {
    // Iterating through grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            // Finding empty cell
            if (grid[i][j] == 0) {

                // Iterating through values from 1 to n^2 (max value)
                for (int num = 1; num <= n * n; num++) {

                    // Check if value is unused in grid
                    if (unused(n, grid, num)) {

                        // Place value into empty cell
                        grid[i][j] = num;

                        // Calling function again with updated grid to fill next empty cell
                        if (magic(n, grid)) {
                            // If magic square is found, return 1
                            return 1;
                        }

                        // If magic square is not found by placing value in empty cell, trace back and change value to 0
                        grid[i][j] = 0;
                    }
                }
                // If no number can be placed in empty cell
                return 0;
            }
        }
    }

    // If no empty cells, check if it is a magic square
    if (check(n, grid) == 1) {
        return 1;
    }
    // If not magic square, return 0
    return 0;
}