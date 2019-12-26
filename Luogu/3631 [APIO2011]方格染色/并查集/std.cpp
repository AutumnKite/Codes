#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 200005, P = 1000000000;
int n, m, k, fa[N], fw[N];
struct node{
	int x, y, z;
}a[100005];
std::pair<int, int> find(int x){
	if (fa[x] == x) return std::make_pair(x, 0);
	std::pair<int, int> res = find(fa[x]);
	res.second ^= fw[x];
	return fa[x] = res.first, fw[x] = res.second, res;
}
bool merge(int x, int y, int z){
	std::pair<int, int> tx = find(x), ty = find(y);
	int w = tx.second ^ ty.second;
	x = tx.first, y = ty.first;
	if (x == y) return w == z;
	return fa[y] = x, fw[y] = w ^ z, 1;
}
int get(int x, int y){ return x == 1 ? y : m + x - 1; }
int solve(int val){
	for (register int i = 1; i <= n + m - 1; ++i) fa[i] = i, fw[i] = 0;
	for (register int i = 1; i <= k; ++i){
		int t = ((a[i].x - 1) & 1) && ((a[i].y - 1) & 1);
		if (!merge(get(a[i].x, 1), get(1, a[i].y), a[i].z ^ val ^ t)) return 0;
	}
	int s = 1, flag = 0;
	for (register int i = 1; i <= n + m - 1; ++i)
		if (fa[i] == i) if (flag) s = 1ll * s * 2 % P; else flag = 1;
	return s;
}
int main(){
	n = read(), m = read(), k = read();
	for (register int i = 1; i <= k; ++i) a[i].x = read(), a[i].y = read(), a[i].z = read();
	printf("%d\n", (solve(0) + solve(1)) % P);
}