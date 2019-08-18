#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define N 100005
int n, r[N], rank[N], sa[N], height[N];
int t1[N], t2[N], cnt[N];
bool cmp(int* c, int x, int y, int l){
	return c[x] == c[y] && c[x + l] == c[y + l];
}
void getsa(int* r, int n, int m, int* sa){
	int *x = t1, *y = t2;
	memset(t1, 0, sizeof t1), memset(t2, 0, sizeof t2);
	for (register int i = 0; i < m; ++i) cnt[i] = 0;
	for (register int i = 0; i < n; ++i) ++cnt[x[i] = r[i]];
	for (register int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
	for (register int i = n - 1; i >= 0; --i) sa[--cnt[x[i]]] = i;
	for (register int j = 1, p = 1, *t; p < n; j <<= 1, m = p){
		p = 0;
		for (register int i = n - j; i < n; ++i) y[p++] = i;
		for (register int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (register int i = 0; i < m; ++i) cnt[i] = 0;
		for (register int i = 0; i < n; ++i) ++cnt[x[i]];
		for (register int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		for (register int i = n - 1; i >= 0; --i) sa[--cnt[x[y[i]]]] = y[i];
		t = x, x = y, y = t, p = 1, x[sa[0]] = 0;
		for (register int i = 1; i < n; ++i)
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
	}
}
void getheight(int* r, int n, int* sa, int* rank){
	for (register int i = 0, k = 0; i < n; height[rank[i]] = k, ++i){
		if (!rank[i]) continue;
		if (k) --k;
		for (register int j = sa[rank[i] - 1]; r[i + k] == r[j + k]; ++k) ;
	}
}
bool check(int k){
	for (register int i = 1, max = sa[0], min = sa[0]; i <= n + 1; ++i)
		if (height[i] < k || i == n + 1){
			if (max - min > k) return true;
			max = sa[i], min = sa[i];
		}
		else max = std :: max(max, sa[i]), min = std :: min(min, sa[i]);
	return false;
}
int main(){
	while (scanf("%d", &n), n--){
		memset(r, 0, sizeof r);
		for (register int i = 0; i <= n; ++i) scanf("%d", r + i);
		if (n == 0) { printf("0\n"); continue; }
		for (register int i = 0; i < n; ++i) r[i] = r[i + 1] - r[i] + 88;
		r[n] = 0, getsa(r, n + 1, 200, sa);
		for (register int i = 0; i <= n; ++i) rank[sa[i]] = i;
		getheight(r, n, sa, rank);
		int L = 4, R = (n - 1) >> 1, ans = -1, mid;
		while (L <= R) if (check(mid = (L + R) >> 1)) ans = mid, L = mid + 1; else R = mid - 1;
		printf("%d\n", ans + 1);
	}
}