/* Purpose: Implementing bubble sort, gnome sort, insertion sort, and shell sort
 * Author: Arib Amin
 * Date: 2023-10-15
 * Persons discussed w/: TA's on Discord
 * References: Gnome Sort: https://en.wikipedia.org/wiki/Gnome_sort
 * Insertion Sort: https://en.wikipedia.org/wiki/Insertion_sort
 * Shell Sort: https://en.wikipedia.org/wiki/Shellsort and https://www.youtube.com/watch?v=IViqgakt-Eg&t=606s
 */
#include "ex6q2.h"

// Please don't change anything in this main function!
int main(void) {
    if (!test_bubble(bubble_sort))
        fprintf(stderr, "Bubble sorting failed\n");
    if (!test_gnome(gnome_sort))
        fprintf(stderr, "Gnome sorting failed\n");
    if (!test_insertion(insertion_sort))
        fprintf(stderr, "Insertion sorting failed\n");
    if (!test_custom(custom_sort)) {
        fprintf(stderr, "Custom sorting failed\n");
	}
	return 0;
}

void bubble_sort(int n, int arr[n]) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n - i - 1; j++){
            if  (arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Not very well known, but very easy!
// Check out the description on here https://en.wikipedia.org/wiki/Gnome_sort
void gnome_sort(int n, int arr[n]) {
    int i = 0;

    while (i < n){
        if (i == 0){
            i++;
        }

        if (arr[i] >= arr[i - 1]){
            i++;
        } else {
            int temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;
            i--;
        }
    }
}

void insertion_sort(int n, int arr[n]) {
    for (int i = 1; i < n; i++){
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}


// The sort you found! (See lab description for details)
void custom_sort(int n, int arr[n]) {
    for (int gap = n / 2; gap > 0; gap = gap / 2){
        for (int i = gap; i < n; i += 1){
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
