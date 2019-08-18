#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define P 1000000007
int T, n, a[100005], dp[100005];
void add(int &x, int y){
	(x += y) >= P ? x -= y : 0;
}
int main(){
	T = read();
	while (T--){
		n = read();
		for (register int i = 1; i <= n; ++i) a[i] = read();
		
	}
}
