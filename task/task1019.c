#include <stdio.h>
#include <string.h>

int main(void) {
    char s1[201], s2[201];

    if (scanf("%200s", s1) != 1) {
        return 0;
    }
    if (scanf("%200s", s2) != 1) {
        return 0;
    }

    int n1 = (int)strlen(s1);
    int n2 = (int)strlen(s2);
    int dp[201][201] = {{0}};

    int bestLen = 0;
    int bestStart = 0;

    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;

                int length = dp[i][j];
                int start = i - length;

                if (length > bestLen || (length == bestLen && start < bestStart)) {
                    bestLen = length;
                    bestStart = start;
                }
            }
        }
    }

    if (bestLen == 0) {
        printf("\n");
        return 0;
    }

    char answer[201];
    memcpy(answer, s1 + bestStart, bestLen);
    answer[bestLen] = '\0';
    printf("%s\n", answer);

    return 0;
}