#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100005
int n, m, k, a[N], h, t, Q[N];
long long sum[N], id[N];
void push(int x, long long *cp){
	while (h <= t && cp[Q[t]] <= cp[x]) --t;
	Q[++t] = x;
}
bool check(long long x){
	h = 1, t = 1, Q[t] = k;
	for (register int i = 1; i <= n; i + k <= n ? push(i + k, sum) : void(0), ++i){
		if (Q[h] < i) ++h;
		if (sum[Q[h]] - a[i] <= x) id[i] = i; else id[i] = 0;
	}
	h = 1, t = 0;
	for (register int i = 1; i <= k; ++i) push(i, id);
	int s = 0;
	for (register int i = 1, p = 0; i <= n - k + 1; push(i + k, id), ++i){
		if (Q[h] < i) ++h;
		if (i <= p) continue;
		if (sum[i + k - 1] <= x) continue;
		p = int(id[Q[h]]), ++s;
		if (p == 0) return 0;
	}
	return s <= m;
}
int main(){
	scanf("%d%d%d", &n, &m, &k);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1; i <= n; ++i)
		sum[i] = sum[i - 1] + a[i] - (i > k ? a[i - k] : 0);
	long long l = 0, r = 100000000000000ll, md, ans;
	while (l <= r) if (check(md = (l + r) >> 1)) ans = md, r = md - 1; else l = md + 1;
	printf("%lld\n", ans);
	getchar(), getchar();
}

/*
It's a wrong greedy algorithm.
Input: 
10 5 4
2 2 2 5 1 5 1 1 2 10
Output: 8
Answer: 9
*/
