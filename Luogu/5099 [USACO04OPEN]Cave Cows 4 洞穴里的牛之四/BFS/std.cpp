#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <map>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 50005
#define INF 0x3f3f3f3f
int n, m;
std :: map< std :: pair<int, int>, int > M;
int h, t;
std :: pair<int, int> Q[N];
int bfs(){
	h = 0, t = 1, M[Q[t] = std :: make_pair(0, 0)] = 0;
	while (h < t){
		std :: pair<int, int> u = Q[++h];
		int d = M[u];
		for (register int dx = -2; dx <= 2; ++dx)
			for (register int dy = -2; dy <= 2; ++dy){
				std :: pair<int, int> v = u;
				v.first += dx, v.second += dy;
				if (!M.count(v)) continue;
				if (v.second == m) return d + 1;
				if (M[v] == INF) M[v] = d + 1, Q[++t] = v;
			}
	}
	return -1;
}
int main(){
	n = read(), m = read();
	for (register int i = 1, x, y; i <= n; ++i)
		x = read(), y = read(), M[std :: make_pair(x, y)] = INF;
	printf("%d\n", bfs());
}