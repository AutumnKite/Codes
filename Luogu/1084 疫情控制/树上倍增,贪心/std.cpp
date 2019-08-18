#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
int read(){
    register int x = 0;
    register char f = 1, ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
    return f ? x : -x;
}
#define N 50005
int n, m, k[N], fa[N][17], bo[N], cnta, cntb;
std :: vector< std :: pair<int, int> > E[N];
long long s[N][17];
std :: pair<long long, int> ta[N], tb[N];
void dfs(int u){
    for (register int i = 1; i <= 16; ++i)
        if (fa[u][i - 1]) fa[u][i] = fa[fa[u][i - 1]][i - 1], s[u][i] = s[u][i - 1] + s[fa[u][i - 1]][i - 1];
    for (auto v : E[u])
        if (v.first != fa[u][0]) fa[v.first][0] = u, s[v.first][0] = v.second, dfs(v.first);
}
bool Dfs(int u){
    if (bo[u]) return 1;
    bool flag = 0;
    bo[u] = 1;
    for (auto v : E[u])
        if (v.first != fa[u][0]){
            flag = 1, Dfs(v.first);
            if (!bo[v.first]) bo[u] = 0;
        }
    if (!flag) bo[u] = 0;
    return bo[u];
}
bool check(long long x){
    for (register int i = 1; i <= n; ++i) bo[i] = 0;
    cnta = cntb = 0;
    for (register int i = 1; i <= m; ++i){
        long long S = 0;
        int u = k[i];
        for (register int i = 16; ~i; --i) if (fa[u][i] > 1 && S + s[u][i] <= x) S += s[u][i], u = fa[u][i];
        if (fa[u][0] > 1 || S + s[u][0] > x) bo[u] = 1;
        else ta[++cnta] = std :: make_pair(x - S - s[u][0], u);
    }
    if (Dfs(1)) return 1;
    for (auto v : E[1]) if (!bo[v.first]) tb[++cntb] = std :: make_pair(v.second, v.first);
    std :: sort(ta + 1, ta + 1 + cnta), std :: sort(tb + 1, tb + 1 + cntb);
    int pa = 1, pb = 1;
    while (pa <= cnta && pb <= cntb){
        if (!bo[ta[pa].second]) bo[ta[pa].second] = 1;
        else if (ta[pa].first >= tb[pb].first) bo[tb[pb].second] = 1, ++pb;
        ++pa;
        while (pb <= cntb && bo[tb[pb].second]) ++pb;
    }
    return pb > cntb;
}
int main(){
    n = read();
    for (register int i = 1, u, v, w; i < n; ++i)
        u = read(), v = read(), w = read(), E[u].push_back(std :: make_pair(v, w)), E[v].push_back(std :: make_pair(u, w));
    m = read();
    for (register int i = 1; i <= m; ++i) k[i] = read();
    dfs(1);
    long long l = 0, r = 5e13, md, ans = 0;
    while (l <= r) if (check(md = (l + r) >> 1)) r = md - 1, ans = md; else l = md + 1;
    printf("%lld", ans);
}