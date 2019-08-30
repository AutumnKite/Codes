bool query(int, int, int, int);
int get_ans(int, int);
#include <cstdio>
#include <cstdlib>
#include <cstring>
namespace zyk_AK_IOI{
	int n, m, a[6][105], cnt, dp[6][105][6][105];
	bool query(int x1, int y1, int x2, int y2){
		++cnt;
		if (cnt > 4500) printf("WA 1\n"), exit(0);
		if (x1 > x2 || y1 > y2) printf("WA 2\n"), exit(0);
		if (x1 < 1 || x2 > n || y1 < 1 || y2 > m) printf("WA 3\n"), exit(0);
		return a[x1][y1] == a[x2][y2] && a[x2][y1] == a[x1][y2];
	}
	bool DP(int x1, int y1, int x2, int y2){
		if (x1 > x2 || y1 > y2) return 1;
		if (~dp[x1][y1][x2][y2]) return dp[x1][y1][x2][y2];
		return dp[x1][y1][x2][y2] = a[x1][y1] == a[x2][y2] && a[x1][y2] == a[x2][y1] && DP(x1 + 1, y1, x2 - 1, y2) && DP(x1, y1 + 1, x2, y2 - 1);
	}
	void Main(){
		scanf("%d%d", &n, &m);
		memset(dp, -1, sizeof dp);
		for (register int i = 1; i <= n; ++i)
			for (register int j = 1; j <= m; ++j)
				scanf("%d", &a[i][j]), dp[i][j][i][j] = 1;
		cnt = 0;
		int ans = get_ans(n, m), sum = 0;
		for (register int x1 = 1; x1 <= n; ++x1)
			for (register int y1 = 1; y1 <= m; ++y1)
				for (register int x2 = x1; x2 <= n; ++x2)
					for (register int y2 = y1; y2 <= m; ++y2)
						sum += DP(x1, y1, x2, y2);
		if (ans == sum) printf("AC answer=%d count=%d\n", ans, cnt), exit(0);
		else printf("WA 4 yours=%d answer=%d\n", ans, sum), exit(0);
	}
}
bool query(int x1, int y1, int x2, int y2){
	return zyk_AK_IOI :: query(x1, y1, x2, y2);
}
int main(){
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	return zyk_AK_IOI :: Main(), 0;
}