#include <stdio.h>

void binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1, found = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            printf("Element found at index %d\n", mid);
            found = 1;
            break; // Stops searching once found
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    if (!found) {
        printf("Element not found\n");
    }
}

void bubbleSort(int arr[], int n) { // Sorting is required for binary search
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, key;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bubbleSort(arr, n); // Ensure array is sorted for binary search

    printf("Enter element to search: ");
    scanf("%d", &key);

    binarySearch(arr, n, key);
    return 0;
}
