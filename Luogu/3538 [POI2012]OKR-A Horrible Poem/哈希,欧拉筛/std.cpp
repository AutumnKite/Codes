#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
char buf[1 << 23], *ps = buf, *pt = buf, pbuf[1 << 23], *pp = pbuf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
void print(int x, int ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int num[30], cnt = 0;
	for (x < 0 ? x = -x, putchar('-') : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 500005;
int n, q;
char s[N];
struct Double_Hash{
	const static int base1 = 233, prime1 = 459346859, base2 = 331, prime2 = 939648961;
	int n;
	struct hash_node{
		int h1, h2;
		bool operator == (const hash_node &rhs) const {
			return h1 == rhs.h1 && h2 == rhs.h2;
		}
		hash_node operator * (const hash_node &rhs) const {
			return {int(1ll * h1 * rhs.h1 % prime1), int(1ll * h2 * rhs.h2 % prime2)};
		}
		hash_node operator - (const hash_node &rhs) const {
			return {(h1 - rhs.h1 + prime1) % prime1, (h2 - rhs.h2 + prime2) % prime2};
		}
		hash_node add(char ch){
			return {int((1ll * h1 * base1 + ch) % prime1), int((1ll * h2 * base2 + ch) % prime2)};
		}
	}pw[N], preh[N];
	void init(int _n, char *s){
		n = _n, preh[0] = {0, 0}, pw[0] = {1, 1};
		for (register int i = 1; i <= n; ++i)
			preh[i] = preh[i - 1].add(s[i]), pw[i] = pw[i - 1].add(0);
	}
	hash_node hash(int l, int r){
		return preh[r] - preh[l - 1] * pw[r - l + 1];
	}
}T;
int cnt, prime[N], vis[N], minp[N], tot, res[N];
void init_prime(int n){
	cnt = 0;
	for (register int i = 2; i <= n; ++i){
		if (!vis[i]) prime[++cnt] = i, minp[i] = i;
		for (register int j = 1; j <= cnt && i * prime[j] <= n; ++j){
			vis[i * prime[j]] = 1, minp[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}
void get(int n){
	tot = 0;
	while (n > 1) res[++tot] = minp[n], n /= minp[n];
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) while (!islower(s[i] = getchar())) ;
	init_prime(n), T.init(n, s);
	q = read();
	while (q--){
		register int l = read(), r = read(), len = r - l + 1, tmp;
		get(len);
		for (register int i = 1; i <= tot; ++i){
			tmp = len / res[i];
			if (T.hash(l, r - tmp) == T.hash(l + tmp, r)) len = tmp;
		}
		print(len);
	}
}