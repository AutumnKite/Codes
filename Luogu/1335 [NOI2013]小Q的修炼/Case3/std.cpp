#include <cstdio>
#include <cstring>
#include <vector>
int n, m;
long long ans, Ans;
std :: vector<int> f, g;
struct node{
	int op, kx, ky, p, q;
	long long x, y;
}a[35005];
char s[10];
long long val(std :: vector<long long> v, int k, long long x){
	if (k == 1) return v[x];
	else return x;
}
void dfs(int l, int k, std :: vector<long long> v){
	while (k >= l && k < l + 170 && a[k].op < 3){
		if (a[k].op == 1) v[a[k].x] += a[k].kx * val(v, a[k].ky, a[k].y), ++k;
		else if (val(v, a[k].kx, a[k].x) < val(v, a[k].ky, a[k].y)) k = a[k].p;
		else k = a[k].q;
	}
	if (k < l || k >= l + 170){
		if (v[1] > ans) ans = v[1], g = f;
		return;
	}
	f.push_back(1), dfs(l, a[k].p, v), f.pop_back();
	f.push_back(2), dfs(l, a[k].q, v), f.pop_back();
}
int main(){
	freopen("train.in", "r", stdin);
	freopen("train.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (register int i = 1; i <= n; ++i){
		scanf("%s", s);
		if (s[0] == 'v'){
			a[i].op = 1, scanf("%lld", &a[i].x);
			scanf("%s", s);
			if (s[0] == '+') a[i].kx = 1; else a[i].kx = -1;
			scanf("%s", s);
			if (s[0] == 'v') a[i].ky = 1; else a[i].ky = 0;
			scanf("%lld", &a[i].y);
			continue;
		}
		if (s[0] == 'i'){
			a[i].op = 2;
			scanf("%s", s);
			if (s[0] == 'v') a[i].kx = 1; else a[i].kx = 0;
			scanf("%lld", &a[i].x);
			scanf("%s", s);
			if (s[0] == 'v') a[i].ky = 1; else a[i].ky = 0;
			scanf("%lld", &a[i].y);
			scanf("%d%d", &a[i].p, &a[i].q);
			if (a[i].p >= 1 && a[i].p <= i) return puts("2333"), 0;
			if (a[i].q >= 1 && a[i].q <= i) return puts("2333"), 0;
			continue;
		}
		a[i].op = 3, scanf("%d%d", &a[i].p, &a[i].q);
		if (a[i].p >= 1 && a[i].p <= i) return puts("2333"), 0;
		if (a[i].q >= 1 && a[i].q <= i) return puts("2333"), 0;
	}
	std :: vector<long long> v;
	for (register int i = 0; i <= m; ++i) v.push_back(0);
	for (register int i = 1; i <= n; i += 170){
		ans = -0x3f3f3f3f3f3f3f3fll;
		f.clear(), dfs(i, i, v);
		for (int p : g) printf("%d\n", p);
		Ans += ans;
	}
	fprintf(stderr, "ans = %lld\n", Ans);
}
