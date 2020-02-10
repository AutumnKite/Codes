#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <bitset>
char buf[1 << 23], *ps = buf, *pt = buf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
char pbuf[1 << 23], *pp = pbuf;
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 505, P = 998244353;
int n, T, p[N];
struct matrix{
	std::bitset<N> r[N], c[N];
	void set(int i, int j){ r[i][j] = c[j][i] = 1; }
	int get(int i, int j){ return r[i][j]; }
};
matrix A, e;
matrix operator * (const matrix &A, const matrix &B){
	matrix C;
	for (register int i = 0; i < n; ++i)
		for (register int j = 0; j < n; ++j)
			if ((A.r[i] & B.c[j]).count()) C.set(i, j);
	return C;
}
matrix qpow(matrix a, int b){
	matrix s = e;
	for (; b; b >>= 1, a = a * a) if (b & 1) s = s * a;
	return s;
}
int main(){
	n = read(), T = read();
	for (register int i = 0; i < n; ++i){
		p[i] = (P + 1 - read()) % P, e.set(i, i);
		int x = read();
		for (register int j = 0; j < x; ++j) A.set(i, read() - 1);
	}
	A = qpow(A, T);
	int ans = 0;
	for (register int i = 0; i < n; ++i){
		int s = 1;
		for (register int j = 0; j < n; ++j)
			if (A.get(i, j)) s = 1ll * s * p[j] % P;
		ans = (ans + P + 1 - s) % P;
	}
	print(ans);
}
