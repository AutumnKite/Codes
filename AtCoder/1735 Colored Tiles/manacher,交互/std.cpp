#include <cstdio>
#include <algorithm>
#include <map>
int n, m, len[6][6][205];
struct node{
	int a, b, c, d;
	bool operator < (const node &res) const {
		return a < res.a || (a == res.a && b < res.b) || (a == res.a && b == res.b && c < res.c) || (a == res.a && b == res.b && c == res.c && d < res.d);
	}
};
std :: map<node, int> M;
bool check(int x1, int y1, int x2, int y2){
	if (x1 > x2 || y1 > y2 || x1 < 1 || x2 > n || y1 < 1 || y2 > (m >> 1)) return 0;
	if (x1 == x2 && y1 == y2) return 1;
	if (M.count((node){x1, y1, x2, y2})) return M[(node){x1, y1, x2, y2}];
	printf("? %d %d %d %d\n", x1, y1, x2, y2), fflush(stdout);
	char opt[5];
	scanf("%s", opt);
	return M[(node){x1, y1, x2, y2}] = (opt[0] == 'y');
}
void manacher(int x, int y, int *hw){
	int mr = 0, mid = 0, n = m;
	hw[0] = 1;
	for (register int i = 1; i <= n; ++i){
		hw[i] = i <= mr ? std :: min(hw[(mid << 1) - i], mr - i + 1) : 0;
		if (i + hw[i] <= mr) continue;
		while ((i - hw[i]) % 2 == 0 || check(x, (i - hw[i] + 1) / 2, y, (i + hw[i] + 1) / 2)) ++hw[i];
		if (i + hw[i] - 1 > mr) mid = i, mr = i + hw[i] - 1;
	}
}
int main(){
	scanf("%d%d", &n, &m);
	m <<= 1;
	for (register int i = 1; i <= n; ++i)
		for (register int j = i; j <= n; ++j)
			manacher(i, j, len[i][j]);
	int ans = 0;
	for (register int i = 1; i <= n; ++i)
		for (register int j = i; j <= n; ++j)
			for (register int k = 1; k <= m; ++k){
				int s = 1e9;
				for (register int l = i, r = j; l <= r; ++l, --r)
					s = std :: min(s, len[l][r][k]);
				ans += s >> 1;
			}
	printf("! %d\n", ans), fflush(stdout);
}