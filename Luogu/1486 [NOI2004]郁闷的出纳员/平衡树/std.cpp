#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 100005
#define pr std :: pair<int, int>
int q, m, k, x, ans, s;
char opt[3];
struct fhq_treap{
	int cnt, rt, ls[N], rs[N], sz[N], val[N], key[N];
	void up(int u){
		sz[u] = sz[ls[u]] + sz[rs[u]] + 1;
	}
	pr split(int u, int V){
		if (!u) return pr(0, 0);
		pr D;
		if (val[u] < V) D = split(ls[u], V), ls[u] = D.second, up(u), D.second = u;
		else D = split(rs[u], V), rs[u] = D.first, up(u), D.first = u;
		return D;
	}
	int merge(int u, int v){
		if (!u || !v) return u + v;
		if (key[u] < key[v]) return rs[u] = merge(rs[u], v), up(u), u;
		else return ls[v] = merge(u, ls[v]), up(v), v;
	}
	void Insert(int V){
		pr D = split(rt, V);
		val[++cnt] = V, key[cnt] = rand(), sz[cnt] = 1, ls[cnt] = rs[cnt] = 0;
		rt = merge(merge(D.first, cnt), D.second);
	}
	void Delete(int V){
		pr D = split(rt, V);
		rt = D.first, ans += sz[D.second];
	}
	int kth(int u, int k){
		if (!u) return -1;
		if (k <= sz[ls[u]]) return kth(ls[u], k);
		if (k == sz[ls[u]] + 1) return val[u];
		return kth(rs[u], k - sz[ls[u]] - 1);
	}
	int Kth(int k){ return kth(rt, k); }
}T;
int main(){
	scanf("%d%d", &q, &m), k = 0;
	while (q--){
		scanf("%s%d", opt, &x);
		if (opt[0] == 'I') if (x >= m) T.Insert(x - k);
		if (opt[0] == 'A') k += x;
		if (opt[0] == 'S') k -= x, T.Delete(m - k);
		if (opt[0] == 'F') s = T.Kth(x), printf("%d\n", ~s ? s + k : -1);
	}
	printf("%d\n", ans);
}
