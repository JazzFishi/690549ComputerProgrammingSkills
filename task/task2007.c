#include <stdio.h>
#include <stdlib.h>

static inline int id(char c){ return c>='a' ? 26 + (c - 'a') : (c - 'A'); }

int main(void){
	int g,n;
	if (scanf("%d %d", &g, &n) != 2) return 0;
	char W[3005];
	char *S = malloc(n + 5);
	if (!S) return 0;
	scanf("%s", W);
	scanf("%s", S);

	int need[52] = {0}, have[52] = {0};
	for (int i = 0; i < g; ++i) need[id(W[i])]++;
	for (int i = 0; i < g; ++i) have[id(S[i])]++;

	int good = 0;
	for (int i = 0; i < 52; ++i) if (have[i] == need[i]) ++good;

	int ans = (good == 52) ? 1 : 0;
	for (int i = g; i < n; ++i){
		int in = id(S[i]), out = id(S[i - g]);
		if (have[out] == need[out]) --good;
		--have[out];
		if (have[out] == need[out]) ++good;
		if (have[in] == need[in]) --good;
		++have[in];
		if (have[in] == need[in]) ++good;
		if (good == 52) ++ans;
	}

	printf("%d\n", ans);
	free(S);
	return 0;
}

