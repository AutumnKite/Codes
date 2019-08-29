#include <cstdio>
int m, d, s;
int main(){
	scanf("%d%d", &m, &d);
	for (register int i = 1; i <= m; ++i)
		for (register int j = 1; j <= d; ++j)
			if (j / 10 >= 2 && j % 10 >= 2 && (j / 10) * (j % 10) == i) ++s;
	printf("%d\n", s);
}