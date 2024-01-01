/* Purpose: Dynamically allocating memory to store products in ailes by the modulo value of their serial number
 * Author: Arib Amin
 * Date: 2023-10-26
 * Persons discussed w/: TA's on Discord
 * References: Allocating Memory (TA Video): https://www.youtube.com/watch?v=0PiuG0HeblQ
 *             IBM Docs for scanf() comparison to EOF: https://www.ibm.com/docs/en/i/7.4?topic=functions-scanf-read-data
 */
#include <stdio.h>
#include <stdlib.h>

int main(){
    int num_of_ailes;
    int aile_num;
    int serial_num;
    char product;

    // Getting number of ailes from user
    scanf("%d", &num_of_ailes);

    // Initializing array to store lengths of ailes
    int aile_lengths[num_of_ailes];
    // Setting all lengths to 0
    for (int i = 0; i < num_of_ailes; i++){
        aile_lengths[i] = 0;
    }

    // Double pointer holds address of pointer to a char
    // Allocating memory for char array of size num_of_ailes
    char **ailes = (char **)malloc(num_of_ailes * sizeof(char *));
    // Setting all ailes to NULL
    for (int i = 0; i < num_of_ailes; i++){
        ailes[i] = NULL;
    }


    // Getting first serial number and looping until end of file/user inputs
    // "The return value is EOF for an attempt to read at end-of-file if no conversion was performed." -IBM Docs
    while (scanf("%d", &serial_num) != EOF){
        
        // If serial number is 0 (code for printing aile)
        if (serial_num == 0){
            // Getting aile number
            scanf("%d", &aile_num);
            // If aile isn't empty, print contents of aile
            if (ailes[aile_num] != NULL){
                for (int i = 0; i < aile_lengths[aile_num]; i++){
                    printf("%c", ailes[aile_num][i]);
                }
                printf("\n");
            // If aile is empty, print new line
            } else {
                printf("\n");
            }
            
        // If serial number isn't 0 (code for adding a product)
        } else {
            // Getting the product code
            scanf(" %c", &product);
            // Aile number is the modulo of serial_num % num_of_ailes (the aile product goes in)
            aile_num = serial_num % num_of_ailes;
            // Getting the length of aile at aile_num
            int aile_length = aile_lengths[aile_num];
            
            // Reallocating memory at aile_num to include space for one more char value
            ailes[aile_num] = (char *)realloc(ailes[aile_num], (aile_length + 1) * sizeof(char));
            // Placing product at end of aile
            ailes[aile_num][aile_length] = product;
            // Increasing length of aile
            aile_lengths[aile_num]++;
        }
    }

    // Freeing contents of each aile
    for (int i = 0; i < num_of_ailes; i++){
        free(ailes[i]);
    }
    // Freeing the ailes array
    free(ailes);

    return 0;
}