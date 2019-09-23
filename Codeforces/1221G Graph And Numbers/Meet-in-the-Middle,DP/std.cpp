#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, m, e[45][45];
long long ans;
bool A[1 << 20], B[1 << 20];
int S[1 << 20], dp[1 << 20];
long long no0(){
	int n0 = n >> 1, n1 = n - n0, U = (1 << n1) - 1;
	for (register int i = 0; i < n0; ++i)
		for (register int j = i + 1; j < n0; ++j)
			if (e[i][j]) A[(1 << i) | (1 << j)] = 1;
	for (register int i = 0; i < n1; ++i)
		for (register int j = i + 1; j < n1; ++j)
			if (e[i + n0][j + n0]) B[(1 << i) | (1 << j)] = 1;
	for (register int i = 0; i < n0; ++i)
		for (register int j = 0; j < (1 << n0); ++j)
			if (j >> i & 1) A[j] |= A[j ^ (1 << i)];
	for (register int i = 0; i < n1; ++i)
		for (register int j = 0; j < (1 << n1); ++j)
			if (j >> i & 1) B[j] |= B[j ^ (1 << i)];
	// A[i] 表示只考虑集合 A，i 这个子集填 0，其他填 1 是否合法，B[i] 同理
	for (register int i = 0; i < (1 << n1); ++i)
		if (!B[i]) dp[i] = 1;
	for (register int i = 0; i < n1; ++i)
		for (register int j = 0; j < (1 << n1); ++j)
			if (j >> i & 1) dp[j] += dp[j ^ (1 << i)];
	// dp[i] 表示在集合 B 中，只考虑 i 这个子集合法的方案数
	for (register int i = 0; i < n0; ++i)
		for (register int j = 0; j < n1; ++j)
			if (e[i][j + n0]) S[1 << i] |= 1 << j;
	for (register int i = 0; i < n0; ++i)
		for (register int j = 0; j < (1 << n0); ++j)
			if (j >> i & 1) S[j] |= S[j ^ (1 << i)];
	// S[i] 表示 A 中 i 这个集合填 0 时，B 中需要填 1 的集合
	long long res = 0;
	for (register int i = 0; i < (1 << n0); ++i)
		if (!A[i]) res += dp[U ^ S[i]];
	// B 中 S[i] 这个集合必须填 1，其他点填的数与这个集合无关（不可能形成 0 边），所以只需要使得 U ^ S[i] 满足条件
	return res;
}
int fa[45], sz[45], s1, s2;
int find(int x){
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}
void merge(int x, int y){
	x = find(x), y = find(y);
	if (x != y) fa[y] = x, sz[x] += sz[y];
}
int h, t, Q[45], dep[45];
bool bfs(int s){
	h = 0, t = 1, Q[t] = s, dep[s] = 1;
	while (h < t){
		int u = Q[++h];
		for (register int v = 0; v < n; ++v)
			if (e[u][v]){
				if (!dep[v]) dep[v] = dep[u] + 1, Q[++t] = v;
				else if ((dep[u] & 1) == (dep[v] & 1)) return 0;
			}
	}
	return 1;
}
long long only1(){
	for (register int i = 0; i < n; ++i)
		if (!dep[i]) if (!bfs(i)) return 0;
	return 1ll << s1;
}
int main(){
	n = read(), m = read();
	if (m == 0) return puts("0"), 0;
	for (register int i = 0; i < n; ++i) fa[i] = i, sz[i] = 1;
	for (register int i = 1; i <= m; ++i){
		int u = read() - 1, v = read() - 1;
		e[u][v] = e[v][u] = 1, merge(u, v);
	}
	for (register int i = 0; i < n; ++i)
		if (find(i) == i) ++s1, sz[i] == 1 ? ++s2 : 0;
	ans = (1ll << n) - no0() * 2 - (1ll << s1) + (1ll << s2) * 2 + only1();
	printf("%lld\n", ans);
}
/*
根据黑红名大巨佬xuxuxuxuxu的说法，考虑容斥。
有012的方案数=总方案数-没0的方案数-没1的方案数-没2的方案数+没01的方案数+没02的方案数+没12的方案数-没012的方案数
总方案数：2^n
没0的方案数/没2的方案数：把点分成两个集合A,B，A枚举状态，可以根据A的状态得出B中每个点只能填1/只能填0还是可以任意填，可以直接DP出方案数
没1的方案数：每个联通块要么全填0要么全填1，方案数2^联通块数量
没01的方案数/没12的方案数：每个大小>1的联通块必须全为1/全为0，单点可以任意填，方案数为2^单点数量
没02的方案数：每个联通块一定可以从某个点开始分层，且层数奇偶性相同的点之间一定没有边，此时每个联通块有两种方案，方案数为2^联通块数量；若不满足则为0
没012的方案数：必须满足m=0否则不可能有，而m=0的时候整个问题的答案就是0，直接特判
*/