#include <stdio.h>
#include <ctype.h>

int main() {
    char text[10005];
    scanf("%s", text);

    int has_upper = 0;
    int has_lower = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            has_upper = 1;
        }
        if (islower(text[i])) {
            has_lower = 1;
        }
    }

    if (has_upper && !has_lower) {
        printf("All Capital Letter\n");
    } else if (!has_upper && has_lower) {
        printf("All Small Letter\n");
    } else {
        printf("Mix\n");
    }

    return 0;
}