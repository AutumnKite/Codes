#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 250005
#define INF 0x3f3f3f3f3f3f3f3fll
int n, d[N], X, vis[N];
long long sum;
std :: vector< std :: pair<int, int> > E[N];
std :: pair<int, int> D[N];
void addedge(int u, int v, int w){
	E[u].push_back(std :: make_pair(v, w)), ++d[u];
}
bool cmp(std :: pair<int, int> x, std :: pair<int, int> y){
	return d[x.first] > d[y.first];
}
struct Normal_Heap{
	std :: vector<long long> a;
	void push(long long x){ a.push_back(x), std :: push_heap(a.begin(), a.end()); }
	long long top(){ return a[0]; }
	void pop(){ std :: pop_heap(a.begin(), a.end()), a.pop_back(); }
	long long popn(){ long long x; return std :: pop_heap(a.begin(), a.end()), x = a[a.size() - 1], a.pop_back(), x; }
	int size(){ return a.size(); }
};
struct Erase_Heap{
	Normal_Heap a, b;
	int sz; long long sum;
	void push(long long x){ a.push(x), ++sz, sum += x; }
	void erase(long long x){ b.push(x), --sz, sum -= x; }
	void pre(){ while (a.size() && b.size() && a.top() == b.top()) a.pop(), b.pop(); }
	long long top(){ return pre(), a.top(); }
	void pop(){ pre(), --sz, sum -= a.top(), a.pop(); }
	int size(){ return sz; }
}H[N];
void die(int u){
	for (auto to : E[u]){
		register int v = to.first, w = to.second;
		if (d[v] <= X) break;
		H[v].push(w);
	}
}
long long dp[N][2];
std :: vector<long long> tmp, del;
void dfs(int u, int fa = 0){
	vis[u] = X;
	int num = d[u] - X;
	long long res = 0;
	for (; H[u].size() > num; H[u].pop()) ;
	for (auto to : E[u]){
		register int v = to.first, w = to.second;
		if (v == fa) continue;
		if (d[v] <= X) break;
		dfs(v, u);
	}
	tmp.clear(), del.clear();
	for (auto to : E[u]){
		register int v = to.first, w = to.second;
		if (v == fa) continue;
		if (d[v] <= X) break;
		long long x = dp[v][1] + w - dp[v][0];
		if (x <= 0){ --num, res += dp[v][1] + w; continue; }
		res += dp[v][0], H[u].push(x), del.push_back(x);
	}
	for (; H[u].size() && H[u].size() > num; H[u].pop()) tmp.push_back(H[u].top());
	dp[u][0] = res + H[u].sum;
	for (; H[u].size() && H[u].size() > num - 1; H[u].pop()) tmp.push_back(H[u].top());
	dp[u][1] = res + H[u].sum;
	for (auto i : tmp) H[u].push(i);
	for (auto i : del) H[u].erase(i);
}
int main(){
	n = read();
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), addedge(u, v, w), addedge(v, u, w), sum += w;
	printf("%lld", sum);
	for (register int i = 1; i <= n; ++i)
		D[i] = std :: make_pair(d[i], i), std :: sort(E[i].begin(), E[i].end(), cmp);
	std :: sort(D + 1, D + 1 + n);
	register int i = 1;
	for (X = 1; X < n; ++X){
		while (i <= n && D[i].first == X) die(D[i].second), ++i;
		long long ans = 0;
		for (register int j = i; j <= n; ++j){
			register int v = D[j].second;
			if (vis[v] == X) continue;
			dfs(v), ans += dp[v][0];
		}
		printf(" %lld", ans);
	}
	putchar('\n');
}
