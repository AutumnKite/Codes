#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x3f3f3f3f
#define N 200005
int T, x, y, dis[N], h, t, Q[N];
int main(){
	scanf("%d", &T);
	while (T--){
		scanf("%d%d", &x, &y);
		if (x > y) { printf("%d\n", x - y); continue; }
		memset(dis, 0x3f, sizeof dis);
		h = 0, t = 1, Q[t] = x, dis[x] = 0;
		while (h < t){
			int u = Q[++h];
			if (u == y) break;
			if (u + 1 < N && dis[u + 1] == INF) Q[++t] = u + 1, dis[u + 1] = dis[u] + 1;
			if (u - 1 > 0 && dis[u - 1] == INF) Q[++t] = u - 1, dis[u - 1] = dis[u] + 1;
			if ((u << 1) < N && dis[u << 1] == INF) Q[++t] = u << 1, dis[u << 1] = dis[u] + 1;
		}
		printf("%d\n", dis[y]);
	}
}