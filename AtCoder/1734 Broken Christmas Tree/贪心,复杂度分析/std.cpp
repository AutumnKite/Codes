#include <cstdio>
#include <cctype>
#include <set>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 200005
int n, m, h, t, Q[N], cnt, x[N], y[N];
std :: set<int> num, E[N];
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= m; ++i){
		int x = read(), y = read();
		E[x].insert(y), E[y].insert(x);
	}
	for (register int i = 2; i <= n; ++i) num.insert(i);
	h = 0, t = 1, Q[t] = 1;
	while (h < t){
		int u = Q[++h];
		for (auto it = num.begin(), It = it; it != num.end(); )
			if (!E[u].count(*it)) x[++cnt] = u, y[cnt] = *it, Q[++t] = *it, It = it, ++it, num.erase(It);
			else ++it;
	}
	if (num.size()) printf("No\n");
	else{
		printf("Yes\n");
		for (register int i = 1; i <= cnt; ++i) printf("%d %d\n", x[i], y[i]);
	}
}