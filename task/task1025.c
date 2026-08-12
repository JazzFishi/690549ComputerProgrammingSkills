#include <stdio.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    int maxExp[100001] = {0};

    for (int i = 0; i < n; i++) {
        int x;
        if (scanf("%d", &x) != 1) {
            return 0;
        }

        int y = x;

        if (y % 2 == 0) {
            int cnt = 0;
            while (y % 2 == 0) {
                cnt++;
                y /= 2;
            }
            if (cnt > maxExp[2]) {
                maxExp[2] = cnt;
            }
        }

        for (int p = 3; p * p <= y; p += 2) {
            if (y % p == 0) {
                int cnt = 0;
                while (y % p == 0) {
                    cnt++;
                    y /= p;
                }
                if (cnt > maxExp[p]) {
                    maxExp[p] = cnt;
                }
            }
        }

        if (y > 1 && maxExp[y] < 1) {
            maxExp[y] = 1;
        }
    }

    long long result = 1;
    for (int p = 2; p <= 100000; p++) {
        if (maxExp[p] > 0) {
            long long factor = 1;
            for (int e = 0; e < maxExp[p]; e++) {
                factor *= p;
            }
            result *= factor;
        }
    }

    printf("%lld\n", result);
    return 0;
}
