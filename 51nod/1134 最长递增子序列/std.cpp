#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
char buf[1000000], *ps = buf;
int read(){
	register int x = 0, f = 1;
	for (; !isdigit(*ps); ++ps) if (*ps == '-') f = !f;
	for (; isdigit(*ps); ++ps) x = (x << 1) + (x << 3) + (*ps ^ '0');
	return f ? x : -x;
}
int n;
int main(){
	buf[fread(buf, 1, 1000000, stdin)] = -1;

}