#include <cstdio>
int m, n, a[1024][1024];
void solve(int x, int n){
	if (n == 1) return a[x][x] = 1, void(0);
	int n_ = n >> 1;
	for (register int i = x; i < x + n_; ++i)
		for (register int j = x; j < x + n_; ++j)
			a[i][j] = 0;
	solve(x + n_, n_);
	for (register int i = x; i < x + n_; ++i)
		for (register int j = x + n_; j < x + n; ++j)
			a[i][j] = a[i + n_][j];
	for (register int i = x + n_; i < x + n; ++i)
		for (register int j = x; j < x + n_; ++j)
			a[i][j] = a[i][j + n_];
}
int main(){
	scanf("%d", &m), n = 1 << m;
	solve(0, n);
	for (register int i = 0; i < n; ++i){
		for (register int j = 0; j < n; ++j)
			putchar(a[i][j] + '0'), putchar(' ');
		putchar('\n');
	}
}