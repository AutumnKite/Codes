#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
char s[10];
int main(){
	scanf("%s", s);
	if (s[0] == 'S') puts("Cloudy");
	else if (s[0] == 'C') puts("Rainy");
	else puts("Sunny");
}