#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;
const int N = 1005, M = 500005;
int n, m, e, vis[N], num[N], ans;
int edge, to[M], pr[M], hd[N];
inline void addedge(int u, int v){
    to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
}
inline int find(int u){
    for (register int i = hd[u], v; i; i = pr[i]){
        v = to[i];
        if (!vis[v]){
            vis[v] = 1;
            if (!num[v] || find(num[v])) return num[v] = u, 1;
        }
    }
    return 0;
}
int main(){
    scanf("%d%d%d", &n, &m, &e);
    for (register int i = 1, u, v; i <= e; ++i)
        scanf("%d%d", &u, &v), (v <= m ? addedge(u, v) : void(0));
    for (register int i = 1; i <= n; ++i){
        memset(vis, 0, sizeof vis);
        if (find(i)) ++ans;
    }
    return printf("%d", ans), 0;
}
