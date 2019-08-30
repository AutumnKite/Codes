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
int l, r, s;
int main(){
	l = read(), r = read();
	for (register int i = l; i <= r; ++i){
		for (register int j = i; j <= r; ++j)
			if (j % i == (j ^ i)) ++s;
	}
	printf("%d\n", s);
}
