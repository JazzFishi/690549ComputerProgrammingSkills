#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXN 305

int main(void) {
	int R, C;
	if (scanf("%d %d", &R, &C) != 2) return 0;
	static char g[MAXN][MAXN];
	for (int i = 0; i < R; ++i) {
		scanf("%s", g[i]);
	}

	static char gr[MAXN][MAXN];
	for (int i = 0; i < R; ++i)
		for (int j = 0; j < C; ++j)
			gr[i][j] = g[R-1-i][C-1-j];

	const unsigned long long BC = 9113823ULL;
	const unsigned long long BR = 9726637ULL;

	static unsigned long long powC[MAXN], powR[MAXN];
	powC[0] = powR[0] = 1ULL;
	for (int i = 1; i <= MAXN-1; ++i) {
		powC[i] = powC[i-1] * BC;
		powR[i] = powR[i-1] * BR;
	}

	static unsigned long long rowPref[MAXN][MAXN];
	static unsigned long long rowPrefR[MAXN][MAXN];
	for (int i = 0; i < R; ++i) {
		rowPref[i][0] = 0ULL;
		rowPrefR[i][0] = 0ULL;
		for (int j = 0; j < C; ++j) {
			unsigned long long v = (unsigned long long)(g[i][j]-'0'+1);
			rowPref[i][j+1] = rowPref[i][j] * BC + v;
			unsigned long long vr = (unsigned long long)(gr[i][j]-'0'+1);
			rowPrefR[i][j+1] = rowPrefR[i][j] * BC + vr;
		}
	}

	int best = -1;
	int maxk = (R < C) ? R : C;

	// search sizes from largest to 2
	for (int k = maxk; k >= 2; --k) {
		int cols = C - k + 1;
		int rows = R - k + 1;
		if (cols <= 0 || rows <= 0) continue;

		int found = 0;
		// for each column start in original
		for (int c0 = 0; c0 <= C - k && !found; ++c0) {
			int c0r = C - k - c0; // corresponding column in reversed grid

			// build vertical prefix for original at column c0
			static unsigned long long colPref[MAXN];
			colPref[0] = 0ULL;
			for (int r = 0; r < R; ++r) {
				unsigned long long seg = rowPref[r][c0+k] - rowPref[r][c0] * powC[k];
				colPref[r+1] = colPref[r] * BR + seg;
			}

			static unsigned long long colPrefR[MAXN];
			colPrefR[0] = 0ULL;
			for (int r = 0; r < R; ++r) {
				unsigned long long seg = rowPrefR[r][c0r+k] - rowPrefR[r][c0r] * powC[k];
				colPrefR[r+1] = colPrefR[r] * BR + seg;
			}

			// compute vertical k-row hashes
			static unsigned long long vert[MAXN];
			static unsigned long long vertR[MAXN];
			for (int r0 = 0; r0 <= R - k; ++r0) {
				vert[r0] = colPref[r0+k] - colPref[r0] * powR[k];
				vertR[r0] = colPrefR[r0+k] - colPrefR[r0] * powR[k];
			}

			// compare positions: for top row r0 in original, corresponding top in reversed is R-k-r0
			for (int r0 = 0; r0 <= R - k; ++r0) {
				int r0r = R - k - r0;
				if (vert[r0] == vertR[r0r]) { found = 1; break; }
			}
		}

		if (found) { best = k; break; }
	}

	if (best == -1) printf("-1\n");
	else printf("%d\n", best);

	return 0;
}

