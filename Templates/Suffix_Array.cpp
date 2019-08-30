#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1000005
char ch[N];
int n, a[N], rank[N], height[N], sa[N], tx[N], ty[N], cnt[N];
bool cmp(int *a, int x, int y, int l){
	return a[x] == a[y] && a[x + l] == a[y + l];
}
void SA(int *a, int n, int m){
	int *x = tx, *y = ty;
	for (register int i = 0; i < m; ++i) cnt[i] = 0;
	for (register int i = 0; i < n; ++i) ++cnt[x[i] = a[i]];
	for (register int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
	for (register int i = n - 1; ~i; --i) sa[--cnt[x[i]]] = i;
	for (register int j = 1, p = 0, *t; p < n; j <<= 1, m = p){
		p = 0;
		for (register int i = n - j; i < n; ++i) y[p++] = i;
		for (register int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (register int i = 0; i < m; ++i) cnt[i] = 0;
		for (register int i = 0; i < n; ++i) ++cnt[x[i]];
		for (register int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		for (register int i = n - 1; ~i; --i) sa[--cnt[x[y[i]]]] = y[i];
		t = x, x = y, y = t, p = 1, x[sa[0]] = 0;
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
int main(){
	scanf("%s", ch), n = strlen(ch);
	for (register int i = 0; i < n; ++i) a[i] = ch[i];
	a[++n] = 0, SA(a, n, 128), get_height(a, n, sa, rank, height);
	for (register int i = 1; i < n; ++i) printf("%d ", sa[i] + 1);
}

