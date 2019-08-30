#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 600005
int n, a[N], b[N], cnt[N], tx[N], ty[N], sa[N];
bool cmp(int *a, int x, int y, int l){
	return a[x] == a[y] && a[x + l] == a[y + l];
}
void Radix_Sort(int n, int m, int *sa, int *x, int *y){
	for (register int i = 0; i < m; ++i) cnt[i] = 0;
	for (register int i = 0; i < n; ++i) ++cnt[x[i]];
	for (register int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
	for (register int i = n - 1; ~i; --i) sa[--cnt[x[y[i]]]] = y[i];
}
void Get_SA(int n, int m, int *a, int *sa){
	int *x = tx, *y = ty;
	for (register int i = 0; i < n; ++i) x[i] = a[i], y[i] = i;
	Radix_Sort(n, m, sa, x, y);
	for (register int j = 1, p = 0; p < n; j <<= 1, m = p){
		p = 0;
		for (register int i = n - j; i < n; ++i) y[p++] = i;
		for (register int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
		Radix_Sort(n, m, sa, x, y);
		std :: swap(x, y), p = 1, x[sa[0]] = 0;
		for (register int i = 1; i < n; ++i)
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
	}
}
int main(){
	n = read();
	for (register int i = 0; i < n; ++i) a[i] = b[i] = read();
	std :: sort(b, b + n);
	for (register int i = 0; i < n; ++i)
		a[i + n] = a[i] = std :: lower_bound(b, b + n, a[i]) - b + 1;
	n <<= 1, a[n - 1] = 0, Get_SA(n, n, a, sa);
	int id = 0;
	for (register int i = 0; i < n; ++i) if (sa[i] < (n >> 1)){ id = sa[i]; break; }
	for (register int i = id; i < id + (n >> 1); ++i) printf("%d ", b[a[i] - 1]);
}
