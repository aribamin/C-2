/* Purpose: Using Levenshtein Distance to spell check words using a dictionary of correctly spelled words
 * Author: Arib Amin
 * Date: 2023-11-08
 * Persons discussed w/: TAs on Discord & Professor Lin Office Hours
 * References: Levenshtein Distance Implementation: https://www.geeksforgeeks.org/introduction-to-levenshtein-distance/
 *                                                  https://www.youtube.com/watch?v=MiqoA-yF-0M&t=734s
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate Levenshtein distance
int lev_distance(char* user_word, char* dict_word){
    // Getting length of user word and dictionary word
    int user_len = strlen(user_word);
    int dict_len = strlen(dict_word);

    // Initializing matrix to store Levenshtein distance between words (+1 for " " chacter to full string)
    int lev_matrix[user_len + 1][dict_len + 1];
    
    // Looping through indicies of user word (rows)
    for (int i = 0; i <= user_len; i++){
        // Looping through indices of dictionary word (columns)
        for (int j = 0; j <= dict_len; j++){
            // Amount of steps to go from " " string to string of length j (row 1)
            if (i == 0){
                lev_matrix[i][j] = j;
            // Amount of steps to go from " " string to string of length i (column 1)
            }else if (j == 0){
                lev_matrix[i][j] = i;
            }
            // If row and column cell value match, do not need to additional step
            else if (user_word[i - 1] == dict_word[j - 1]){
                lev_matrix[i][j] = lev_matrix[i - 1][j - 1];
            // For the cell you are working on, find the minimum of left, above, and diagonal and add 1 to it
            }else{
                // Start with minimum value equals above cell
                int min_val = lev_matrix[i - 1][j];
                // Compare it to value of left cell
                if (lev_matrix[i][j - 1] < min_val){
                    min_val = lev_matrix[i][j - 1];
                } 
                // Compare it to value of diagonal cell
                if (lev_matrix[i - 1][j - 1] < min_val){
                    min_val = lev_matrix[i - 1][j - 1];
                }
                // Set value of index to minimum value + the additional step needed to make change
                lev_matrix[i][j] = min_val + 1;
            }
        }
    }
    // Return Levenshtein distance
    return lev_matrix[user_len][dict_len];
}

int main() {
    // Initializing variables for number of words in dictionary and number of lines 
    int num_words;
    int num_lines;

    // Getting number of words in dictionary and number of lines 
    scanf("%d %d", &num_words, &num_lines);

    // Allocating memory for poitner to array of pointers to character arrays
    char **dictionary = (char **)malloc(num_words * sizeof(char *));
    // Looping for amount of words in dictionary
    for (int i = 0; i < num_words; i++) {
        // Allocating memory for each word in dictionary
        dictionary[i] = (char *)malloc(11 * sizeof(char));
        // Storing words in dictionary
        scanf("%s", dictionary[i]);
        // Reallocating size of each character array to size of string
        dictionary[i] = (char *)realloc(dictionary[i], (strlen(dictionary[i]) + 1) * sizeof(char));
    }

    // Getting "\n" from stdin
    getchar();

    // Allocating memory to store each word in line
    char *word = (char *)malloc(11 * sizeof(char));
    // Allocating memory for nearest word (word to print out)
    char *nearest_word = (char *)malloc(11 * sizeof(char));

    // Looping for number of lines of words
    for (int i = 0; i < num_lines; i++) {
        // Loop untill end of line
        while (scanf("%s", word) == 1) {
            // Initial minimum distance from " " to final string is 11 steps (10 letter word)
            int min_distance = 11;

            // Looping through dictionary words
            for (int j = 0; j < num_words; j++) {
                // Comparing Levenshtein distance with each dictionary word
                int distance = lev_distance(word, dictionary[j]);
                
                // Keeping track of lowest distance
                if (distance < min_distance) {
                    min_distance = distance;
                    // Keeping track of nearest word
                    strcpy(nearest_word, dictionary[j]);
                }
            }
            // When reaching end of line, break out of loop
            if (getchar() == '\n') {
                printf("%s", nearest_word);
                break;
            }
            // Printing nearest word
            printf("%s ", nearest_word);
        }
        // Print new line character to separate lines
        printf("\n");
    }
    // Free memory allocated for word
    free(word);
    // Freeing nearest word;
    free(nearest_word);

    // Looping for amount of words in dictionary
    for (int i = 0; i < num_words; ++i) {
        // Freeing each word in dictionary
        free(dictionary[i]);
    }
    // Freeing dictionary
    free(dictionary);
    
    return 0;
}