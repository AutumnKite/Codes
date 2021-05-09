#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 5005, M = 100005;
int head[N], nxt[M], v[M], tot, que[M], l, r, vis[M], dis[M], n, q, nw;
vector<int> vec[N];
bitset<N> bt[N], now, cur, all;
inline void add(int a, int b) {
	bt[a][b] = bt[b][a] = 1;
	if (tot > 100000) return;
	tot++;
	nxt[tot] = head[a];
	head[a] = tot;
	v[tot] = b;
}
inline int min(int a, int b) { return a < b ? a : b; }
void dfs(int pos, int f, int maxn) {
	int SZ = vec[pos].size(), i;
	for (i = 0; i < SZ; i++) {
		if (vec[pos][i] == f) continue;
		if (maxn < min(nw, vec[pos][i])) add(nw, vec[pos][i]), add(vec[pos][i], nw);
		if (max(maxn, vec[pos][i]) >= nw) continue;
		dfs(vec[pos][i], pos, max(maxn, vec[pos][i]));
	}
}
int main() {
	int i, op, a, b, ans;
	scanf("%d%d", &n, &q);
	while (q--) {
		scanf("%d%d%d", &op, &a, &b);
		if (op == 1) {
			vec[a].pb(b);
			vec[b].pb(a);
			nw = b;
			dfs(b, 0, 0);
			continue;
		}
		if (tot < 100000) {
			l = 1;
			r = 0;
			que[++r] = a;
			dis[a] = 0;
			vis[a] = q;
			int tag = 0;
			while (l <= r) {
				int t = que[l++];
				for (i = head[t]; i; i = nxt[i]) {
					if (vis[v[i]] == q) continue;
					dis[v[i]] = dis[t] + 1;
					vis[v[i]] = q;
					que[++r] = v[i];
					if (v[i] == b) {
						tag = 1;
						break;
					}
				}
				if (tag) break;
			}
			printf("%d\n", dis[b]);
			continue;
		}
		for (i = 1; i <= n; i++) all[i] = 1;
		now = 0;
		now[a] = 1;
		ans = 0;
		while (!now[b]) {
			all ^= now;
			cur = 0;
			for (i = 1; i <= n; i++)
				if (now[i]) cur |= bt[i];
			now = (cur & all);
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
