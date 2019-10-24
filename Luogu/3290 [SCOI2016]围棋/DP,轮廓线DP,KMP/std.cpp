#include <cstdio>
const int P = 1000000007;
int n, m, c, q, fail[2][8], trans[2][8][3], f[2][1 << 12][8][8];
char s[2][8];
int val(char ch){ return ch == 'W' ? 0 : (ch == 'B' ? 1 : 2); }
void KMP(char s[], int fail[], int trans[][3]){
	for (register int i = 1; i <= c; ++i){
		int x = val(s[i]);
		if (i == 1) fail[i] = 0;
		else fail[i] = trans[fail[i - 1]][x];
		for (register int j = 0; j < 3; ++j)
			if (j == x) trans[i - 1][j] = i;
			else if (i == 1) trans[i - 1][j] = 0;
			else trans[i - 1][j] = trans[fail[i - 1]][j];
	}
	for (register int i = 0; i < 3; ++i) trans[c][i] = trans[fail[c]][i];
}
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
void dec(int &a, int b){ (a -= b) < 0 ? a += P : 0; }
void solve(){
	scanf("%s%s", s[0] + 1, s[1] + 1);
	for (register int i = 0; i < 2; ++i) KMP(s[i], fail[i], trans[i]);
	f[0][0][0][0] = 1;
	int o = 0, r = 1 << (m - c + 1), ans = 1;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j){
			o ^= 1, ans = 3ll * ans % P;
			for (register int k = 0; k < r; ++k)
				for (register int x = 0; x <= c; ++x)
					for (register int y = 0; y <= c; ++y){
						int &s = f[o ^ 1][k][x][y];
						if (!s) continue;
						for (register int v = 0; v < 3; ++v){
							int _x = trans[0][x][v], _y = trans[1][y][v];
							if (j < c){ inc(f[o][k][_x][_y], s); continue; }
							if (!(k & 1) || _y < c)
								inc(f[o][k >> 1 | (_x == c) << (m - c)][j == m ? 0 : _x][j == m ? 0 : _y], s);
						}
						s = 0;
					}
		}
	for (register int i = 0; i < r; ++i) dec(ans, f[o][i][0][0]), f[o][i][0][0] = 0;
	printf("%d\n", ans);
}
int main(){
	scanf("%d%d%d%d", &n, &m, &c, &q);
	while (q--) solve();
}
