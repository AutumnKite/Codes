#include <cstdio>
#include <cstring>
#include <vector>
struct node{
	int op, kx, ky, p, q, x, y;
}a[35005];
namespace bf{
	int ans;
	std :: vector<int> f, g;
	int val(std :: vector<int> v, int k, int x){
		if (k == 1) return v[x];
		else return x;
	}
	void dfs(int l, int r, int k, std :: vector<int> v){
		while (k >= l && k <= r && a[k].op < 3){
			if (a[k].op == 1) v[a[k].x] += a[k].kx * val(v, a[k].ky, a[k].y), ++k;
			else if (val(v, a[k].kx, a[k].x) < val(v, a[k].ky, a[k].y)) k = a[k].p;
			else k = a[k].q;
		}
		if (k < l || k > r){
			if (v[1] > ans) ans = v[1], g = f;
			return;
		}
		f.push_back(1), dfs(l, r, a[k].p, v), f.pop_back();
		f.push_back(2), dfs(l, r, a[k].q, v), f.pop_back();
	}
	void get_ans(int l, int r){
		std :: vector<int> v;
		for (register int i = 0; i <= 12; ++i) v.push_back(0);
		ans = -0x3f3f3f3f;
		dfs(l, r, l, v);
	}
}
int q, n, m, nx[205], w[205], v[205], id[35005];
std :: vector<int> h[205];
int f[205][1005], g[205][1005];
char s[10];
void print_ans(int p, int k){
	if (p == 1) return;
	if (g[p][k] < 0){
		print_ans(-g[p][k], k);
		if (m - k >= w[-g[p][k]]) puts("2");
	}
	else{
		print_ans(g[p][k], k - w[g[p][k]]);
		puts("1");
		for (int v : h[g[p][k]]) printf("%d\n", v);
	}
}
int main(){
	freopen("train10.in", "r", stdin);
	freopen("train10.out", "w", stdout);
	scanf("%d", &q), scanf("%s", s);
	scanf("%s%s%s%s", s, s, s, s), scanf("%d", &m);
	scanf("%s%s%s%s%s%s%s", s, s, s, s, s, s, s), id[2] = 1;
	int i = 2;
	while (i < q){
		++i, scanf("%s%s%s%s%s%s%s", s, s, s, s, s, s, s);
		++n, ++i, scanf("%s%s", s, s), scanf("%d", &nx[n]);
		if (nx[n] < 1 || nx[n] > q) nx[n] = 0;
		++i, scanf("%s%s%s%s", s, s, s, s), scanf("%d", &w[n]);
		int l = i + 1, r = 0;
		while (i < q){
			++i, scanf("%s", s);
			if (s[0] == 'v'){
				a[i].op = 1, scanf("%d", &a[i].x);
				scanf("%s", s);
				if (s[0] == '+') a[i].kx = 1; else a[i].kx = -1;
				scanf("%s", s);
				if (s[0] == 'v') a[i].ky = 1; else a[i].ky = 0;
				scanf("%d", &a[i].y);
				if (a[i].x == 12 && a[i].kx == -1 && a[i].y == 12 && a[i].ky == 1){ r = i; break; }
				continue;
			}
			if (s[0] == 'i'){
				a[i].op = 2, scanf("%s", s);
				if (s[0] == 'v') a[i].kx = 1; else a[i].kx = 0;
				scanf("%d", &a[i].x);
				scanf("%s", s);
				if (s[0] == 'v') a[i].ky = 1; else a[i].ky = 0;
				scanf("%d", &a[i].y);
				scanf("%d%d", &a[i].p, &a[i].q);
				continue;
			}
			if (s[0] == 's') a[i].op = 3, scanf("%d%d", &a[i].p, &a[i].q);
		}
		bool flag = 1;
		while (i < q && flag){
			++i, scanf("%s", s), scanf("%s", s), id[i] = n + 1;
			if (s[0] == 'v') flag = 0;
			scanf("%s%s%s%s%s", s, s, s, s, s);
		}
		// fprintf(stderr, "%d %d %d\n", l, r, i);
		bf :: get_ans(l, r), v[n] = bf :: ans, h[n] = bf :: g;
	}
	id[0] = n + 1;
	for (register int i = 1; i <= n; ++i) nx[i] = id[nx[i]];//, fprintf(stderr, "%d ", nx[i]);
	// fprintf(stderr, "\n");
	memset(f, 0xc0, sizeof f);
	f[1][0] = 0;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 0; j <= m; ++j){
			if (f[i][j] > f[nx[i]][j])
				f[nx[i]][j] = f[i][j], g[nx[i]][j] = -i;
			if (j + w[i] > m) continue;
			if (f[i][j] + v[i] > f[i + 1][j + w[i]])
				f[i + 1][j + w[i]] = f[i][j] + v[i], g[i + 1][j + w[i]] = i;
		}
	int ans = -0x3f3f3f3f, k = 0;
	for (register int i = 0; i <= m; ++i)
		if (f[n + 1][i] > ans) ans = f[n + 1][i], k = i;
	print_ans(n + 1, k);
	fprintf(stderr, "%d\n", ans);
}
