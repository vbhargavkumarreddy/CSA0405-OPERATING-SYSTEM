#include <stdio.h>

#define MAX_FRAMES 10

int main() {
    int referenceString[MAX_FRAMES];
    int pageFaults = 0;
    int m, n, s, pages, frames;

    printf("Enter the number of pages: ");
    scanf("%d", &pages);

    printf("Enter reference string values:\n");
    for (m = 0; m < pages; m++) {
        printf("Value No. [%d]: ", m + 1);
        scanf("%d", &referenceString[m]);
    }

    printf("Enter the total number of frames: ");
    scanf("%d", &frames);

    int memoryQueue[frames];
    for (m = 0; m < frames; m++) {
        memoryQueue[m] = -1; // Initialize memory slots
    }

    int front = 0; // Front of the queue

    for (m = 0; m < pages; m++) {
        int page = referenceString[m];
        int found = 0;

        // Check if page is already in memory
        for (n = 0; n < frames; n++) {
            if (memoryQueue[n] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // Page fault: Replace the oldest page
            memoryQueue[front] = page;
            front = (front + 1) % frames;
            pageFaults++;
        }
    }

    printf("Total page faults: %d\n", pageFaults);
    return 0;
}

