#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) {
        return 0;
    }

    char grid[20][21];
    bool occupied[20][20] = {false};

    for (int i = 0; i < N; i++) {
        if (scanf("%20s", grid[i]) != 1) {
            return 0;
        }
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'O') {
                occupied[i][j] = true;
            }
        }
    }

    int drops[20] = {0};
    for (int j = 0; j < M; j++) {
        if (scanf("%d", &drops[j]) != 1) {
            return 0;
        }
    }

    for (int j = 0; j < M; j++) {
        for (int k = 0; k < drops[j]; k++) {
            if (occupied[0][j]) {
                break;
            }
            int r = 0;
            while (r + 1 < N && !occupied[r + 1][j]) {
                r++;
            }
            occupied[r][j] = true;
            if (grid[r][j] == '.') {
                grid[r][j] = '#';
            }
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i]);
    }

    return 0;
}
