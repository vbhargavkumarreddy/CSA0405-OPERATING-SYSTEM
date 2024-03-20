#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void FCFS(int requests[], int numRequests, int initialHead) {
    int totalSeekCount = 0;
    int currentTrack = initialHead;

    for (int i = 0; i < numRequests; i++) {
        int requestedTrack = requests[i];
        int seekDistance = abs(requestedTrack - currentTrack);
        totalSeekCount += seekDistance;
        currentTrack = requestedTrack;
    }

    printf("Total number of seek operations = %d\n", totalSeekCount);
}

int main() {
    int requests[MAX_REQUESTS];
    int numRequests, initialHead;

    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);

    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    printf("Enter the track numbers:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    FCFS(requests, numRequests, initialHead);
    return 0;
}

