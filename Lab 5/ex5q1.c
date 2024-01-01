/* Purpose: To intake input file containing sudoku puzzles and then outputting whether it is valid or invalid
 * Author: Arib Amin
 * Date: 2023-10-07
 * Persons discussed w/: 
 * References: 
 */
#include <stdio.h>

//Function to check validity of 9x9 sudoku array
int valid(int sudoku[9][9]){
    //Initializing 9 rows to hold 9 unique values from 1-9 in each row
    int row[9][9];

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            row[i][j] = 0;
        }
    }
    //Initializing 9 columns to hold 9 unique values from 1-9 in each row
    int column[9][9];

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            column[i][j] = 0;
        }
    }
    //Initializing 9 subgrids to hold 9 unique values from 1-9 in each row
    int subgrid[3][3][9];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 9; ++k) {
                subgrid[i][j][k] = 0;
            }
        }
    }

    //Iterating through sudoku array, rows then columns
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            //Getting index value of number at sudoku[i][j], 0-8
            int num = sudoku[i][j] - 1;
            //If index value is within 0-8
            if (num >= 0 && num < 9){
                //Check if current number has been used in row i
                if (row[i][num]){
                    return 0;   
                }
                //Set number as used in row i
                row[i][num] = 1;

                //Check if current number has been used in column j
                if (column[j][num]){
                    return 0;
                }
                //Set number as used in column j
                column[j][num] = 1;
                
                //Divide rows and colums by 3 to create 9 subgrids
                int subgrid_row = i / 3;
                int subgrid_column = j / 3;
                //Check if current number has been used in subgrid[i][j]
                if (subgrid[subgrid_row][subgrid_column][num]){
                    return 0;
                }
                //Set number as used in subgrid[i][j]
                subgrid[subgrid_row][subgrid_column][num] = 1;

            //If index value is not within 0-8
            }else{
                return 0;
            }
        }
    }
    return 1;
}

int main(){
    //Creatig 9 x 9 sudoku array
    int sudoku[9][9];

    //Iterating through sudoku array, rows then columns
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            //Setting values into sudoku array, using %1d to read one integer at a time and skip space
            scanf("%1d", &sudoku[i][j]);
        }
    }

    //Checking validity of sudoku array by calling valid() function
    if (valid(sudoku)){
        printf("Valid\n");
    }else{
        printf("Invalid\n");
    }

    return 0;
}