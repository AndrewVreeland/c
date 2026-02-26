#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrLen = sizeof(arr) / sizeof(arr[0]);
    
    int left = 0;
    int right = arrLen - 1;
    int answer = 8;
    int foundIndex = -1; // -1 indicates the value hasn't been found yet

    // The condition must be <= to check the very last possible element
    while (left <= right) {
        int midpoint = left + (right - left) / 2; // Safer way to calculate midpoint

        if (arr[midpoint] == answer) {
            foundIndex = midpoint;
            break; // Exit the loop immediately upon finding the value
        }
        
        if (arr[midpoint] > answer) {
            // If the middle value is too high, look in the left half
            right = midpoint - 1;
        } else {
            // If the middle value is too low, look in the right half
            left = midpoint + 1;
        }
    }

    // Final result check after the loop finishes
    if (foundIndex != -1) {
        printf("I found the answer and it is : %d at position: %d\n", answer, foundIndex);
    } else {
        printf("We did not find the answer sadly\n");
    }

    return 0;
}