#include <stdio.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    int can[101] = {0};
    can[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (i - 6 >= 0 && can[i - 6]) {
            can[i] = 1;
        }
        if (i - 9 >= 0 && can[i - 9]) {
            can[i] = 1;
        }
        if (i - 20 >= 0 && can[i - 20]) {
            can[i] = 1;
        }
    }

    int found = 0;
    for (int i = 1; i <= n; i++) {
        if (can[i]) {
            printf("%d\n", i);
            found = 1;
        }
    }
    if (!found) {
        printf("no\n");
    }

    return 0;
}
