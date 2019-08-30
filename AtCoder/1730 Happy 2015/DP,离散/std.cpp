#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define P 1000000007
int n, m, pos[4005], sum[4005], dp0[4005], dp1[4005];
bool cov[4005][4005];
std :: vector<int> p[4005];
struct node{
	int l, r;
}a[2005];
void add(int &x, int y){
	(x += y) >= P ? x -= P : 0;
}
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i)
		scanf("%d%d", &a[i].l, &a[i].r), pos[++m] = a[i].l, pos[++m] = a[i].r;
	std :: sort(pos + 1, pos + 1 + m);
	m = std :: unique(pos + 1, pos + 1 + m) - pos - 1;
	for (register int i = 1; i <= n; ++i){
		a[i].l = std :: lower_bound(pos + 1, pos + 1 + m, a[i].l) - pos + 1;
		a[i].r = std :: lower_bound(pos + 1, pos + 1 + m, a[i].r) - pos;
		p[a[i].r].push_back(a[i].l);
	}
	for (register int i = 1; i <= m; ++i){
		sum[i] = 0;
		for (register int j = 1; j <= n; ++j)
			if (a[j].l == i) cov[i][a[j].r] = 1;
		for (register int j = i; j <= m; ++j){
			for (register int k = 0; k < p[j].size(); ++k)
				if (p[j][k] > i && sum[j] > sum[p[j][k] - 1]){ cov[i][j] = 1; break; }
			sum[j + 1] = sum[j] + cov[i][j];
		}
	}
	dp0[0] = 1;
	for (register int i = 1; i <= m; ++i){
		add(dp0[i], dp0[i - 1]), add(dp0[i], dp1[i - 1]);
		for (register int j = 1; j <= i; ++j)
			if (cov[j][i]) add(dp1[i], dp0[j - 1]);
	}
	add(dp0[m], dp1[m]), printf("%d\n", dp0[m]);
}