#include <cstdio>
#include <cctype>
#include <cstring>
int read(){
	register int x = 0, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) ;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x;
}
#define N 100005
#define M 200005
int n, m, f[N], h, t, Q[N], d[N];
int edge, to[M], pr[M], hd[N];
void addedge(int u, int v){
	to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
}
int main(){
	n = read(), m = read();
	for (register int i = 1, x, y; i <= m; ++i)
		x = read(), y = read(), addedge(y, x), ++d[x];
	h = 0, t = 0;
	for (register int i = 1; i <= n; ++i) if (!d[i]) Q[++t] = i, f[i] = 2;
	while (h < t){
		int u = Q[++h];
		if (f[u] == 2)
			for (register int i = hd[u]; i; i = pr[i])
				!f[to[i]] ? Q[++t] = to[i] : 0, f[to[i]] = 1;
		else
			for (register int i = hd[u]; i; i = pr[i])
				if (!(--d[to[i]])) Q[++t] = to[i], f[to[i]] = 2;
	}
	if (f[1] == 0) printf("Draw\n");
	else if (f[1] == 1) printf("Snuke\n");
	else if (f[1] == 2) printf("Sothe\n");
}

