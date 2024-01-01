/* Purpose: To get 22 integers from user, find max and min of first 20 integers and output (integer #21) * max + (integer #22) * min
 * Author: Arib Amin
 * Date: 2023-09-23
 * Persons discussed w/:
 * References: Lab 2, Part 1 for limits.h, INT_MIN, and INT_MAX
 */

#include <stdio.h>
#include <limits.h>

int main(){
    int num;
    //Setting max and min to lowest and highest possible integers
    int max = INT_MIN;
    int min = INT_MAX;
    int x, y;

    printf("Enter 22 integers: ");
    //Looping 22 times inorder to get first 20 integers, then x and y
    for (int i = 0; i < 22; i++){
        //Checking for invalid input, ie. not an int and returning with exit code 100
        if (scanf("%d", &num) != 1){
            return 100;
        }

        //Only comparing upto integer #20
        if ((num > max) && (i <= 19)){
            max = num;
        }

        if ((num < min) && (i <= 19)){
            min = num;
        }

        //Setting x to integer #21
        if (i == 20){
            x = num;
        }

        //Setting y to integer #22
        if (i == 21){
            y = num;
        }

    }

    //Calculating and outputting result
    int result = x * max + y * min;
    printf("x * max + y * min: %d\n", result);
    
    return 0;
}