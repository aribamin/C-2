/* Purpose: Joining groups of student ids and checking if two student ids are in same group using Disjoint Sets and Union-Find
 * Author: Arib Amin
 * Date: 2023-12-06
 * Persons discussed w/: TAs on Discord & Professor Lin Office Hours
 * References:
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef FASTIO
#define condition 1
#elif EASYIO
#define condition 0
#endif

int find(int *students_array, int student){
    if (students_array[student] == 0){
        return student;
    }else if(students_array[student] != student){
        students_array[student] = find(students_array, students_array[student]);
    }
    return students_array[student];
}

int main(int argc, char *argv[]){
    if (argc != 4){
        exit(100);
    }

    int num_students = atoi(argv[2]);
    
    FILE *source;
    source = fopen(argv[3], "r");

    char *print_buffer = calloc(2000001, sizeof(char));
    int index = 0;
    int *students_array = calloc(num_students + 1, sizeof(int));

    int i = 0;
    char action = '\0';
    int num1 = 0;
    int num2 = 0;

    while(i < atoi(argv[1])){
        fscanf(source, " %c %d %d\n", &action, &num1, &num2);

        int parent1 = find(students_array, num1);
        int parent2 = find(students_array, num2);

        if(action == 'j'){
            students_array[parent2] = parent1;
        }else if(action == '?'){
            char result;
            
            if (parent1 == parent2){
                result = 'T';
            }else{
                result = 'F';
            }

            if (result == 'T'){
                students_array[parent2] = parent1;
            }

            if(condition == 0){
                printf("%c\n", result);
            }else{
                print_buffer[index] = result;
                index++;
            }
        }
        i++;
    }

    if(condition == 1){
        for(int j = 0; j < index; j++){
            printf("%c\n", print_buffer[j]);
        }
    }

    fclose(source);
    free(print_buffer);
    free(students_array);
}
