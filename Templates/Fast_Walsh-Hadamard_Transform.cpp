#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
char buf[1 << 23], *ps = buf, *pt = buf, pbuf[1 << 23], *pp = pbuf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
#define flush() (fwrite(pbuf, 1, pp - pbuf, stdout))
void print(int x){
	register int num[30], cnt = 0;
	if (!x) putchar('0');
	else{
		for (x = x < 0 ? -x : x; x; x /= 10) num[++cnt] = x % 10 ^ '0';
		while (cnt) putchar(num[cnt]), --cnt;
	}
}
typedef std :: vector<int> poly;
#define P 998244353
#define Inv2 499122177
int n;
poly A, B;
namespace Fast_Walsh_Transform{
	void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
	void dec(int &a, int b){ (a -= b) < 0 ? a += P : 0; }
	int plus(int a, int b){ return (a += b) >= P ? a - P : a; }
	int minus(int a, int b){ return (a -= b) < 0 ? a + P : a; }
	int get(int n){
		int res = 1;
		while (res < n) res <<= 1;
		return res;
	}
	void FWT_or(poly &a, int op = 1){
		int n = a.size();
		for (register int m = 1; m < n; m <<= 1)
			for (register int l = m << 1, p = 0; p < n; p += l)
				for (register int i = p; i < p + m; ++i)
					if (~op) inc(a[i + m], a[i]);
					else dec(a[i + m], a[i]);
	}
	poly mul_or(poly a, poly b){
		int m = std :: max(a.size(), b.size()), n = get(m);
		a.resize(n), b.resize(n);
		FWT_or(a), FWT_or(b);
		for (register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * b[i] % P;
		FWT_or(a, -1);
		return a;
	}
	void FWT_and(poly &a, int op = 1){
		int n = a.size();
		for (register int m = 1; m < n; m <<= 1)
			for (register int l = m << 1, p = 0; p < n; p += l)
				for (register int i = p; i < p + m; ++i)
					if (~op) inc(a[i], a[i + m]);
					else dec(a[i], a[i + m]);
	}
	poly mul_and(poly a, poly b){
		int m = std :: max(a.size(), b.size()), n = get(m);
		a.resize(n), b.resize(n);
		FWT_and(a), FWT_and(b);
		for (register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * b[i] % P;
		FWT_and(a, -1);
		return a;
	}
	void FWT_xor(poly &a, int op = 1){
		int n = a.size();
		for (register int m = 1; m < n; m <<= 1)
			for (register int l = m << 1, p = 0; p < n; p += l)
				for (register int i = p; i < p + m; ++i){
					int t0 = plus(a[i], a[i + m]), t1 = minus(a[i], a[i + m]);
					if (~op) a[i] = t0, a[i + m] = t1;
					else a[i] = 1ll * t0 * Inv2 % P, a[i + m] = 1ll * t1 * Inv2 % P;
				}
	}
	poly mul_xor(poly a, poly b){
		int m = std :: max(a.size(), b.size()), n = get(m);
		a.resize(n), b.resize(n);
		FWT_xor(a), FWT_xor(b);
		for (register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * b[i] % P;
		FWT_xor(a, -1);
		return a;
	}
}
using Fast_Walsh_Transform :: mul_or;
using Fast_Walsh_Transform :: mul_and;
using Fast_Walsh_Transform :: mul_xor;
void print_poly(poly a){
	for (register int i = 0; i < a.size(); ++i) print(a[i]), putchar(' ');
	putchar('\n');
}
int main(){
	n = read(), A.resize(1 << n), B.resize(1 << n);
	for (register int i = 0; i < (1 << n); ++i) A[i] = read();
	for (register int i = 0; i < (1 << n); ++i) B[i] = read();
	print_poly(mul_or(A, B)), print_poly(mul_and(A, B)), print_poly(mul_xor(A, B));
	flush();
}