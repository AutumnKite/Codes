#include <cstdio>
#include <algorithm>
#define N 20005
int n, k, a[N], rank[N], height[N], sa[N], tx[N], ty[N], cnt[1000005];
bool cmp(int *a, int x, int y, int l){
	return a[x] == a[y] && a[x + l] == a[y + l];
}
void SA(int *a, int n, int m){
	int *x = tx, *y = ty;
	for (register int i = 0; i < m; ++i) cnt[i] = 0;
	for (register int i = 0; i < n; ++i) ++cnt[x[i] = a[i]];
	for (register int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
	for (register int i = n - 1; ~i; --i) sa[--cnt[x[i]]] = i;
	for (register int j = 1, p = 0; p < n; j <<= 1, m = p){
		p = 0;
		for (register int i = n - j; i < n; ++i) y[p++] = i;
		for (register int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (register int i = 0; i < m; ++i) cnt[i] = 0;
		for (register int i = 0; i < n; ++i) ++cnt[x[i]];
		for (register int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		for (register int i = n - 1; ~i; --i) sa[--cnt[x[y[i]]]] = y[i];
		std :: swap(x, y), p = 1, x[sa[0]] = 0;
		for (register int i = 1; i < n; ++i)
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
	}
}
void get_height(int *a, int n, int *sa, int *rank, int *height){
	for (register int i = 0; i < n; ++i) rank[sa[i]] = i;
	for (register int i = 0, k = 0, j; i < n; height[rank[i]] = k, ++i)
		if (rank[i]) for (k ? --k : 0, j = sa[rank[i] - 1]; a[i + k] == a[j + k]; ++k);
	height[0] = 0;
}
bool check(int x){
	register int cnt = 1;
	for (register int i = 1; i < n; ++i, ++cnt)
		if (height[i] < x) if (cnt >= k) return 1; else cnt = 0;
	return cnt >= k;
}
int main(){
	scanf("%d%d", &n, &k);
	for (register int i = 0; i < n; ++i) scanf("%d", a + i);
	a[++n] = 0, SA(a, n, 1000001), get_height(a, n, sa, rank, height);
	int l = 0, r = n - 1, mid, ans = 0;
	while (l <= r) if (check(mid = (l + r) >> 1)) ans = mid, l = mid + 1; else r = mid - 1;
	printf("%d", ans);
}

