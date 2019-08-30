#include <cstdio>
#include <cctype>
#include <algorithm>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
long long a[200005], ST[200005][21], t, D;
int n, m, Log[200005];
bool flag;
void change(int x){
	ST[x][0] = a[x];
	for (register int i = 1; x - (1 << i) >= 0; ++i)
		ST[x][i] = std :: max(ST[x][i - 1], ST[x - (1 << (i - 1))][i - 1]);
}
long long find(int x, int y){
	int t = Log[y - x + 1];
	return std :: max(ST[y][t], ST[x + (1 << t) - 1][t]);
}
int main(){
	m = read(), D = read(), Log[1] = 0;
	for (register int i = 2; i <= m; ++i) Log[i] = Log[i >> 1] + 1;
	for (register int i = 1; i <= m; ++i){
		char c = getchar();
		while (c != 'A' && c != 'Q') c = getchar();
		if (c == 'A'){
			long long x = read();
			a[++n] = (x + t) % D;
			change(n);
		}
		else{
			int L = read();
			long long ans;
			if (L == 1){
				printf("%lld\n", a[n]);
				t = a[n];
				continue;
			}
			ans = find(n - L + 1, n);
			printf("%lld\n", ans);
			t = ans;
		}
	}
}