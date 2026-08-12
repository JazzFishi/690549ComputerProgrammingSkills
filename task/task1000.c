#include <stdio.h>
#include <string.h>

int main() {
    int L, N;
    char word[2][1005];
    if (scanf("%d", &L) != 1) return 0;
    if (scanf("%d", &N) != 1) return 0;
    if (scanf("%s", word[0]) != 1) return 0;
    int prev = 0;
    int current = 1;
    int len_prev = (int)strlen(word[prev]);
    int broken = 0;
    int have_valid = 0;
    char lastWord[1005] = "";

    if (len_prev == L) {
        have_valid = 1;
        strcpy(lastWord, word[prev]);
    } else {
        broken = 1; /* first word invalid, still consume remaining input */
    }

    for (int i = 1; i < N; i++) {
        if (scanf("%s", word[current]) != 1) return 0;

        if (!broken) {
            int len_curr = (int)strlen(word[current]);
            if (len_curr != L) {
                broken = 1;
            } else {
                int diff = 0;
                for (int k = 0; k < len_curr; k++) {
                    if (word[prev][k] != word[current][k]) diff++;
                    if (diff > 2) break;
                }
                if (diff > 2) {
                    broken = 1;
                } else {
                    /* still valid, update lastWord and advance */
                    have_valid = 1;
                    strcpy(lastWord, word[current]);
                    len_prev = len_curr;
                    prev = current;
                    current = 1 - current;
                }
            }
        }
        /* if broken, just continue reading remaining words */
    }

    if (have_valid) printf("%s\n", lastWord);
    return 0;
}