#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0, f = 1;
	register char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int T, r[25], n, a[25];
int edge, to[105], tw[105], pr[105], hd[25];
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
}
int h, t, in[25], cnt[25], Q[10005], dis[25];
bool SPFA(int md){
	for (register int i = 0; i <= 24; ++i) dis[i] = -0x3f3f3f3f, in[i] = cnt[i] = 0;
	h = 0, t = 1, Q[t] = 0, in[0] = 1, cnt[0] = 1, dis[0] = 0;
	while (h < t){
		int u = Q[++h];
		if (cnt[u] > 25) return 0;
		in[u] = 0;
		for (register int i = hd[u], v; i; i = pr[i])
			if (dis[v = to[i]] < dis[u] + tw[i]){
				dis[v] = dis[u] + tw[i];
				if (!in[v]) Q[++t] = v, ++cnt[v], in[v] = 1;
			}
	}
	return dis[24] <= md;
}
bool check(int md){
	memset(hd, 0, sizeof hd), memset(pr, 0, sizeof pr), edge = 0;
	for (register int i = 1; i <= 24; ++i){
		addedge(i - 1, i, 0), addedge(i, i - 1, -a[i]);
		if (i >= 8) addedge(i - 8, i, r[i]);
		else addedge(i + 16, i, r[i] - md);
	}
	addedge(0, 24, md);
	return SPFA(md);
}
int main(){
	T = read();
	while (T--){
		for (register int i = 1; i <= 24; ++i) r[i] = read(), a[i] = 0;
		n = read();
		for (register int i = 1; i <= n; ++i) ++a[read() + 1];
		int l = 0, r = n, md, ans = -1;
		while (l <= r) if (check(md = (l + r) >> 1)) r = md - 1, ans = md; else l = md + 1;
		if (~ans) printf("%d\n", ans); else printf("No Solution\n");
	}
}
/*
s[i]>=s[i-1]
s[i-1]>=s[i]-a[i]
i>=8 s[i]>=s[i-8]+r[i]
i<8 s[i]>=s[i+16]+r[i]-s[24]
s[24]>=s[0]+s[24]
*/