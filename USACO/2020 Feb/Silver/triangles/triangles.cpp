#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
namespace fastIO{
#define getchar() my_getchar()
#define putchar(x) my_putchar(x)
	static const int IN_BUF = 1 << 23, OUT_BUF = 1 << 23;
	char buf[IN_BUF], *ps = buf, *pt = buf;
	inline char my_getchar() {
		return ps == pt && (pt = (ps = buf) + fread(buf, 1, IN_BUF, stdin), ps == pt) ? EOF : *ps++;
	}
	template<typename T> inline bool read(T &x){
		char op = 0, ch = getchar();
		for (x = 0; !isdigit(ch) && ch != EOF; ch = getchar()) if (ch == '-') op ^= 1;
		if (ch == EOF) return false;
		for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ '0');
		if (ch != '.') return op ? x = -x : 0, true; else ch = getchar();
		T t = 1;
		for (; isdigit(ch); ch = getchar()) t /= 10, x += (ch ^ '0') * t;
		return op ? x = -x : 0, true;
	}
	inline int reads(char *s){
		int n = 0;
		char ch = getchar();
		for (; isspace(ch) && ch != EOF; ch = getchar()) ;
		for (; !isspace(ch) && ch != EOF; ch = getchar()) s[n++] = ch;
		return s[n] = '\0', n;
	}
	char pbuf[OUT_BUF], *pp = pbuf;
	struct _flusher{ ~_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } OutputFlusher;
	inline void my_putchar(char x){
		pp == pbuf + OUT_BUF ? fwrite(pbuf, 1, OUT_BUF, stdout), pp = pbuf : 0, *pp++ = x;
	}
	template<typename T> inline void print_(T x){
		if (x == 0) return putchar('0'), void(0);
		std::vector<int> num;
		for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num.push_back(x % 10);
		while (!num.empty()) putchar(num.back() ^ '0'), num.pop_back();
	}
	template<typename T> inline void print(T x, char ch = '\n'){
		print_(x), putchar(ch);
	}
	inline void prints_(const char *s, int n = -1){
		if (n == -1) n = strlen(s);
		for (register int i = 0; i < n; ++i) putchar(s[i]);
	}
	inline void prints(const char *s, int n = -1, char ch = '\n'){
		prints_(s, n), putchar(ch);
	}
	template<typename T> inline void printd_(T x, int n){
		if (x < 0) x = -x, putchar('-');
		long long a, b;
		for (register int i = 0; i < n; ++i) x *= 10;
		x = (long long)(x + 0.5);
		for (register int i = 0; i < n; ++i) x /= 10;
		a = x, x -= a;
		for (register int i = 0; i < n; ++i) x *= 10;
		b = x;
		print_(a);
		if (n) putchar('.'); else return;
		std::vector<int> num(n);
		for (register int i = 0; i < n; ++i) num[i] = b % 10, b /= 10;
		while (!num.empty()) putchar(num.back() ^ '0'), num.pop_back();
	}
	template<typename T> inline void printd(T x, int n, char ch = '\n'){
		printd_(x, n), putchar(ch);
	}
}
using namespace fastIO;
const int N = 100005, P = 1000000007;
int n, x[N], y[N], ans;
struct node{
	int x, y, sx, sy;
}a[N];
std::vector< std::pair<int, int> > X[N], Y[N];
int main(){
	freopen("triangles.in", "r", stdin);
	freopen("triangles.out", "w", stdout);
	read(n);
	for (register int i = 1; i <= n; ++i) read(a[i].x), read(a[i].y), x[i] = a[i].x, y[i] = a[i].y;
	std::sort(x + 1, x + 1 + n), std::sort(y + 1, y + 1 + n);
	int mx = std::unique(x + 1, x + 1 + n) - x - 1, my = std::unique(y + 1, y + 1 + n) - y - 1;
	for (register int i = 1; i <= n; ++i){
		int px = std::lower_bound(x + 1, x + 1 + mx, a[i].x) - x;
		int py = std::lower_bound(y + 1, y + 1 + my, a[i].y) - y;
		X[py].push_back(std::make_pair(a[i].x, i)), Y[px].push_back(std::make_pair(a[i].y, i));
	}
	for (register int i = 1; i <= my; ++i){
		std::sort(X[i].begin(), X[i].end());
		int sz = X[i].size(), sum = 0, now = 0;
		for (register int j = 0; j < sz; ++j) sum += X[i][j].first;
		for (register int j = 0; j < sz; ++j)
			a[X[i][j].second].sx = X[i][j].first * (2 * j - sz) - now * 2 + sum, now += X[i][j].first;
	}
	for (register int i = 1; i <= mx; ++i){
		std::sort(Y[i].begin(), Y[i].end());
		int sz = Y[i].size(), sum = 0, now = 0;
		for (register int j = 0; j < sz; ++j) sum += Y[i][j].first;
		for (register int j = 0; j < sz; ++j)
			a[Y[i][j].second].sy = Y[i][j].first * (2 * j - sz) - now * 2 + sum, now += Y[i][j].first;
	}
	for (register int i = 1; i <= n; ++i)
		ans = (ans + 1ll * a[i].sx * a[i].sy) % P;
	print(ans);
}