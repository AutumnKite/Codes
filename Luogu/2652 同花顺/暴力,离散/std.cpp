#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n, a[N], b[N], m, c[N], ans;
std :: vector<int> p[N];
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read(), b[i] = read(), c[i] = a[i];
	std :: sort(c + 1, c + 1 + n);
	m = std :: unique(c + 1, c + 1 + n) - c - 1;
	for (register int i = 1; i <= n; ++i)
		a[i] = std :: lower_bound(c + 1, c + 1 + m, a[i]) - c, p[a[i]].push_back(b[i]);
	for (register int i = 1; i <= m; ++i)
		std :: sort(p[i].begin(), p[i].end()), p[i].erase(std :: unique(p[i].begin(), p[i].end()), p[i].end());
	for (register int i = 1; i <= m; ++i)
		for (register int j = 0; j < p[i].size(); ++j){
			int k = std :: lower_bound(p[i].begin(), p[i].end(), p[i][j] + n) - p[i].begin();
			ans = std :: max(ans, k - j);
		}
	printf("%d\n", n - ans);
}