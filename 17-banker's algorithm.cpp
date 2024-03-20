#include <stdio.h>
int main() {
    int n = 5; 
    int r = 3;
    int alloc[5][3] = {
        {0, 0, 1}, // P0
        {3, 0, 0}, // P1
        {1, 0, 1}, // P2
        {2, 3, 2}, // P3
        {0, 0, 3}  // P4
    };
    int max[5][3] = {
        {7, 6, 3}, // P0
        {3, 2, 2}, // P1
        {8, 0, 2}, // P2
        {2, 1, 2}, // P3
        {5, 2, 3}  // P4
    };
    int avail[3] = {2, 3, 2};
    int need[5][3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    printf("Need Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    int f[5] = {0}; 
    int ans[5];
    int ind = 0;
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 1;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    ans[ind++] = i;
                    for (int y = 0; y < r; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }
    printf("The SAFE Sequence is as follows:\n");
    for (int i = 0; i < n - 1; i++) {
        printf("P%d -> ", ans[i]);
    }
    printf("P%d\n", ans[n - 1]);

    return 0;
}

