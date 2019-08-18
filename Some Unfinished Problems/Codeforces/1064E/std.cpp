#include <cstdio>
#include <cctype>
int read(){
	register int x = 0;
	register char ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, l = 0, r = 1000000000;
char ch;
int gcd(int a, int b){
	return !b ? a : gcd(b, a % b);
}
char get(){
	char c = getchar();
	while (c != 'b' && c != 'w') c = getchar();
	return c == 'b' ? gcd(c, r), c : c;
}
int main(){
	n = read(), --n;
	printf("0 100\n"), fflush(stdout); 
	ch = get();
	for (register int i = 1, mid; i <= n; ++i){
		mid = (l + r) >> 1;
		printf("%d 100\n", mid), fflush(stdout);
		if (get() != ch) r = mid - 1; else l = mid + 1;
	}
	printf("%d 99 %d 101\n", l, r), fflush(stdout);
}