#include <cstdio>
#include <algorithm>
int T, n, a[105], b[105], mx;
int Left(int i){
	if (i == 1) return n;
	else return i - 1;
}
int Right(int i){
	if (i == n) return 1;
	else return i + 1;
}
int main(){
	scanf("%d", &T);
	while (T--){
		scanf("%d", &n), mx = -1;
		for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (register int i = 1; i <= n; ++i) scanf("%d", b + i);
		for (register int i = 1; i <= n; ++i)
			if (b[i] > a[Left(i)] + a[Right(i)]) mx = std :: max(mx, b[i]);
		printf("%d\n", mx);
	}
}
