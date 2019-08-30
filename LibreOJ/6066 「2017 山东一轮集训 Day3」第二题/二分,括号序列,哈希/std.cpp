#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
namespace Double_Hash{
	static const int N = 200005, B1 = 233, P1 = 382538579, B2 = 331, P2 = 952959323;
	int pw1[N], pw2[N];
	struct node{
		int H1, H2;
		node(int _H1 = 0, int _H2 = 0){ H1 = _H1, H2 = _H2; }
		bool operator == (const node &rhs) const {
			return H1 == rhs.H1 && H2 == rhs.H2;
		}
		bool operator < (const node &rhs) const {
			return H1 < rhs.H1 || (H1 == rhs.H1 && H2 < rhs.H2);
		}
		node operator + (const char ch) const {
			return node((1ll * H1 * B1 + ch) % P1, (1ll * H2 * B2 + ch) % P2);
		}
		node operator + (const node &rhs) const {
			return node((H1 + rhs.H1) % P1, (H2 + rhs.H2) % P2);
		}
		node operator - (const node &rhs) const {
			return node((H1 - rhs.H1 + P1) % P1, (H2 - rhs.H2 + P2) % P2);
		}
		node operator << (const int x) const {
			return node(1ll * H1 * pw1[x] % P1, 1ll * H2 * pw2[x] % P2);
		}
	}h[N];
	void pre(int n = N - 1){
		pw1[0] = 1, pw2[0] = 1;
		for (register int i = 1; i <= n; ++i)
			pw1[i] = 1ll * pw1[i - 1] * B1 % P1, pw2[i] = 1ll * pw2[i - 1] * B2 % P2;
	}
	node hash(int l, int r){
		return h[r] - (h[l - 1] << (r - l + 1));
	}
	void build(char *a, int n){
		for (register int i = 1; i <= n; ++i) h[i] = h[i - 1] + a[i];
	}
}
using namespace Double_Hash;
#define N 100005
int n, fa[N][20], idx, l[N], r[N], dis[N];
char a[N << 1];
std :: vector<int> son[N], po[N];
std :: set<node> S;
void dfs(int u){
	dis[u] = 0, l[u] = ++idx, a[idx] = 23;
	for (register int i = 1; i <= 18; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (register int i = 0, v; i < son[u].size(); ++i)
		v = son[u][i], fa[v][0] = u, dfs(v), dis[u] = std :: max(dis[u], dis[v] + 1);
	r[u] = ++idx, a[idx] = 97;
}
int kth_fa(int u, int k){
	for (register int i = 0; i <= 18; ++i)
		if (k >> i & 1) u = fa[u][i];
	return u;
}
bool check(int k){
	for (register int i = 1; i <= n; ++i) po[i].clear();
	for (register int i = 1; i <= n; ++i)
		po[i].push_back(l[i]), po[i].push_back(r[i] + 1);
	for (register int i = 1; i <= n; ++i){
		int p = kth_fa(i, k + 1);
		if (p) po[p].push_back(l[i]), po[p].push_back(r[i] + 1);
	}
	for (register int i = 1; i <= n; ++i)
		std :: sort(po[i].begin(), po[i].end());
	S.clear();
	for (register int i = 1; i <= n; ++i)
		if (dis[i] >= k){
			node tmp;
			for (register int j = 0; j < po[i].size(); j += 2)
				tmp = (tmp << (po[i][j + 1] - po[i][j])) + hash(po[i][j], po[i][j + 1] - 1);
			if (S.count(tmp)) return 1;
			S.insert(tmp);
		}
	return 0;
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i){
		int k = read();
		for (register int j = 1; j <= k; ++j) son[i].push_back(read());
	}
	dfs(1);
	pre(n << 1), build(a, n << 1);
	int l = 0, r = n, md, ans = 0;
	while (l <= r) if (check(md = (l + r) >> 1)) l = md + 1, ans = md; else r = md - 1;
	printf("%d\n", ans);
}