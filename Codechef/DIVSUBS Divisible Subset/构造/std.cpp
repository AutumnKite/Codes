#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int T, n, pos[100005], sum[100005];
void print(int l, int r){
	printf("%d\n", r - l + 1);
	for (register int i = l; i <= r; ++i) printf("%d ", i);
	putchar('\n');
}
int main(){
	T = read();
	while (T--){
		n = read();
		for (register int i = 1; i <= n; ++i) sum[i] = (sum[i - 1] + read()) % n;
		for (register int i = 0; i < n; ++i) pos[i] = -1;
		for (register int i = 0; i <= n; ++i)
			if (~pos[sum[i]]){ print(pos[sum[i]] + 1, i); break; }
			else pos[sum[i]] = i;
	}
}
