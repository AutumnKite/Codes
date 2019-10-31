#include <cstdio>
int n, a[105];
int main(){
	printf("get_num\n"), fflush(stdout);
	scanf("%d", &n);
	for (register int i = 0; i < n; ++i){
		int l = 0, r = 1000000, md, x;
		while (l <= r){
			md = (l + r) >> 1;
			printf("guess %d %d\n", i, md), fflush(stdout);
			scanf("%d", &x);
			if (x == 0){ a[i] = md; break; }
			if (x == -1) l = md + 1;
			else r = md - 1;
		}
	}
	printf("submit");
	for (register int i = 0; i < n; ++i) printf(" %d", a[i]);
	putchar('\n'), fflush(stdout);
}