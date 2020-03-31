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
int n, m;
int vis[105], now[105], cnt, l, r;
char s[105];
struct node{
	int t, x, y;
	bool operator < (const node &rhs) const {
		return t < rhs.t;
	}
}a[255];
int main(){
	freopen("tracing.in", "r", stdin);
	freopen("tracing.out", "w", stdout);
	read(n), read(m);
	reads(s + 1);
	for (register int i = 1; i <= m; ++i)
		read(a[i].t), read(a[i].x), read(a[i].y);
	std::sort(a + 1, a + 1 + m);
	l = m + 1, r = 0;
	for (register int x = 1; x <= n; ++x){
		bool is_zero = 0;
		for (register int k = 0; k <= m + 1; ++k){
			for (register int i = 1; i <= n; ++i) vis[i] = 0, now[i] = 0;
			vis[x] = 1;
			for (register int i = 1; i <= m; ++i){
				int vx = vis[a[i].x], vy = vis[a[i].y];
				if (now[a[i].x] < k && vx) ++now[a[i].x], vis[a[i].y] = 1;
				if (now[a[i].y] < k && vy) ++now[a[i].y], vis[a[i].x] = 1;
			}
			bool flag = 1;
			for (register int i = 1; i <= n; ++i) flag &= (s[i] ^ '0') == vis[i];
			if (!flag) continue;
			l = std::min(l, k), r = std::max(r, k), is_zero = 1;
		}
		cnt += is_zero;
	}
	print(cnt, ' '), print(l, ' ');
	if (r <= m) print(r);
	else prints("Infinity");
}