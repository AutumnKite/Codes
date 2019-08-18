#include <cstdio>
#include <cctype>
#include <algorithm>
#include <set>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x; 
}
#define N 100005
int n, a[N], L[N], R[N], cnt, ans[N];
std :: set< std :: pair<int, int> > S;
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i)
		a[i] = read(), L[i] = i - 1, R[i] = i + 1;
	for (register int i = 1; i < n; ++i)
		S.insert(std :: make_pair(-a[i], i));
	for (register int i = 1; i <= (n >> 1); ++i){
		int x = S.begin() -> second, y = R[x];
		ans[++cnt] = a[x], ans[++cnt] = a[y];
		S.erase(S.begin());
		if (R[y] <= n) S.erase(std :: make_pair(-a[y], y));
		else S.erase(std :: make_pair(-a[L[x]], L[x]));
		R[L[x]] = R[y], L[R[y]] = L[x];
	}
	for (register int i = 1; i <= n; ++i) printf("%d ", ans[i]);
}