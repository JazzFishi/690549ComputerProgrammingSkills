#include <stdio.h>
#include <string.h>

int countDistinct(int a, int b, int c) {
	int mask = 0;
	if (a) mask |= 1 << (a - 1);
	if (b) mask |= 1 << (b - 1);
	if (c) mask |= 1 << (c - 1);
	/* builtin popcount is fine for gcc/clang */
	int cnt = __builtin_popcount(mask);
	if (cnt == 0) return 0; /* shouldn't happen for a new delivery (t>0) */
	return cnt;
}

int main(void) {
	int N;
	if (scanf("%d", &N) != 1) return 0;
	static char s[100005];
	if (scanf("%s", s) != 1) return 0;

	int map[256] = {0};
	map['M'] = 1; /* meat */
	map['F'] = 2; /* fish */
	map['B'] = 3; /* bread */

	const int STATES = 256; /* 4^4 */
	const int NEG = -1000000000;
	static int dp[256];
	static int ndp[256];
	for (int i = 0; i < STATES; ++i) dp[i] = NEG;
	dp[0] = 0; /* both mines empty: last1=0,last2=0 for each */

	for (int i = 0; i < N; ++i) {
		int t = map[(unsigned char)s[i]];
		for (int j = 0; j < STATES; ++j) ndp[j] = NEG;
		for (int idx = 0; idx < STATES; ++idx) {
			int val = dp[idx];
			if (val <= NEG/2) continue;
			int x = idx;
			int d = x & 3; x >>= 2;
			int c = x & 3; x >>= 2;
			int b = x & 3; x >>= 2;
			int a = x & 3;

			/* assign to mine1: new last1=a<-t, last2=a becomes prev last1 */
			int gain1 = countDistinct(t, a, b);
			int nidx1 = (((t * 4 + a) * 4 + c) * 4 + d);
			if (ndp[nidx1] < val + gain1) ndp[nidx1] = val + gain1;

			/* assign to mine2 */
			int gain2 = countDistinct(t, c, d);
			int nidx2 = (((a * 4 + b) * 4 + t) * 4 + c);
			if (ndp[nidx2] < val + gain2) ndp[nidx2] = val + gain2;
		}
		for (int j = 0; j < STATES; ++j) dp[j] = ndp[j];
	}

	int ans = 0;
	for (int i = 0; i < STATES; ++i) if (dp[i] > ans) ans = dp[i];
	printf("%d\n", ans);
	return 0;
}

