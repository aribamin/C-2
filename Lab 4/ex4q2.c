/* Purpose: To intake input file containing amount of boxes, weights of boxes, weight capacity of trucks and outputing box limit of each truck 
 * Author: Arib Amin
 * Date: 2023-09-30
 * Persons discussed w/: TA's on Discord
 * References: Quicksort implementation: https://www.geeksforgeeks.org/quick-sort/
 */

 #include <stdio.h>
 int main(){
    //Get number of boxes
    int num_boxes = 0;
    scanf("%d", &num_boxes);
    
    //Create array size of number of boxes and get box weights
    float box_weights[num_boxes];
    for (int i = 0; i < num_boxes; i++){
        scanf("%f", &box_weights[i]);
    }
    
    //Sorting the weights using quick sort
    int stack[num_boxes];
    int top = -1;

    stack[++top] = 0;
    stack[++top] = num_boxes - 1;

    while (top >= 0) {
        int high = stack[top--];
        int low = stack[top--];

        int pivot_index = low;
        float pivot = box_weights[high];
        for (int i = low; i < high; i++) {
            if (box_weights[i] < pivot) {
                //Swap box_weights[i] and box_weights[pivot_index]
                float temp = box_weights[i];
                box_weights[i] = box_weights[pivot_index];
                box_weights[pivot_index] = temp;
                pivot_index++;
            }
        }
        //Swap box_weights[pivot_index] and box_weights[high]
        float temp = box_weights[pivot_index];
        box_weights[pivot_index] = box_weights[high];
        box_weights[high] = temp;

        if (pivot_index - 1 > low) {
            stack[++top] = low;
            stack[++top] = pivot_index - 1;
        }

        if (pivot_index + 1 < high) {
            stack[++top] = pivot_index + 1;
            stack[++top] = high;
        }
    }

    //Looping through box weights array and creating a running sum to use binary search after
    for (int i = 0; i < num_boxes; i++){
        if (i >= 1){
            box_weights[i] = box_weights[i] + box_weights[i - 1];
        }
    }

    //Getting truck weight capacities
    float truck_capacity = 0;
    while (scanf("%f", &truck_capacity) != EOF) {
        int max_boxes = 0;
        int left = 0, right = num_boxes - 1;
        
        //Binary search to find greatest weight in array that is <= truck capacity
        //This works because we sorted array first, as such all weights are greatest to least when running summed
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (box_weights[mid] <= truck_capacity) {
                max_boxes = mid + 1;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        printf("%d\n", max_boxes);
    }
    
    return 0;
 }