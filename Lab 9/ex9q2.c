/* Purpose: To do operations such as add, concatenate, and rotate for numbers of size up to 10^100 using strings
 * Author: Arib Amin
 * Date: 2023-11-09
 * Persons discussed w/: TAs on Discord and Professor Lin Office Hours
 * References:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function for adding number one and number two
void add(char *result, char *num1, char *num2) {
    // Getting lengths of number one and number two
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    // Initializing variable for carry and result index
    int carry = 0;
    int result_index = 0;

    // Looping until length of larger number between two
    for (int i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0; i--, j--){
        // Initializing variable for sum
        int sum = 0;
        
        // If both indexes are greater than 0, add values in both numbers
        if (i >= 0 && j >= 0){
            sum = (num1[i] - 48) + (num2[j] - 48) + carry;
        // If only number one index is greater than 0, just add number one
        }else if (i >= 0){
            sum = (num1[i] - 48) + carry;
        // If only number two index is greater than 0, just add number two
        }else if(j >= 0){
            sum = (num2[j] - 48) + carry;
        }

        // Getting amount to carry to next index
        carry = sum / 10;
        // Setting value to result at result index
        result[result_index] = (sum % 10) + 48;
        // Incrementing result index
        result_index++;
    }

    // If there is a carry at the end, additional digit
    if (carry > 0){
        result[result_index] = carry + '0';
        result_index++;
    }

    // Adding a '\0' at the end of string
    result[result_index] = '\0';

    // Reversing the digits of the string
    int left = 0;
    int right = result_index - 1;
    while (left < right){
        char temp = result[left];
        result[left] = result[right];
        result[right] = temp;
        
        left++;
        right--;
    }
}

// Function for concatenating number one and number two
void concatenate(char *result, char *num1, char *num2) {
    // Copy number one to result
    strcpy(result, num1);
    // Concatenate number two to result
    strcat(result, num2);
}

// Function for rotating digits of number
void rotate(char *result, char *num1, int rotations) {
    // Getting length of number one
    int length = strlen(num1);
    
    // Loop for number of rotations
    for(int i = 0; i < rotations; i++){
        // Keeping track of first digit
        int temp = num1[0];
        // Moving all values to left
        for (int j = 1; j < length; j++){
            num1[j - 1] = num1[j];
        }
        // Moving first digit to last index
        num1[length - 1] = temp;
    }
    // Finding first non-zero index of numbers with more than 1 digit
    int nonzero_index = 0;
    if (strlen(num1) > 1){
        while(num1[nonzero_index] == '0'){
            nonzero_index++;
        }
    }
    // Copying rotated number to result
    strcpy(result, num1 + nonzero_index);
}

int main() {
    // Get number of lines from user
    int num_lines;
    scanf("%d", &num_lines);

    // Initializing variables for number one, operation, number two, and result
    char *num1;
    char operation[4];
    char *num2;
    char *result;

    // Memory allocation for max size of number one and number two (10^100)
    num1 = (char *)malloc(102 * sizeof(char));
    num2 = (char *)malloc(102 * sizeof(char));
    // Memory allocation for max size of number one concatenated with number two (10^201)
    result = (char *)malloc(203 * sizeof(char));

    // Loop for amount of lines from user input
    for (int i = 0; i < num_lines; i++){
        // Get number one, operation, and number two from user
        scanf("%s %s %s", num1, operation, num2);

        // Check for type of operation, rotation, addition, or concatenate
        if (strcmp(operation, "rot") == 0){
            rotate(result, num1, atoi(num2));
        }else if (strcmp(operation, "+") == 0){
            add(result, num1, num2);
        }else if (strcmp(operation, "@") == 0){
            concatenate(result, num1, num2);
        }
        // Print result
        printf("%s\n", result);
    }

    // Free allocated memory
    free(num1);
    free(num2);
    free(result);

    return 0;
}
