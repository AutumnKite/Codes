#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
namespace fastIO{
#define getchar() my_getchar()
#define putchar(x) my_putchar(x)
#define debug(...) fprintf(stderr, __VA_ARGS__)
	static const int IN_BUF = 1 << 23, OUT_BUF = 1 << 23;
	char buf[IN_BUF], *ps = buf, *pt = buf;
	inline char my_getchar(){
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
const int N = 100005, INF = 0x3f3f3f3f;
int n, rt, d[N], f[N][2];
std::vector<std::pair<int, int>> E[N];
void dfs(int u, int fa = 0){
	std::vector<int> g;
	for (auto p : E[u]){
		int v = p.first, w = p.second;
		if (v == fa) continue;
		dfs(v, u), g.push_back(f[v][0] + w);
	}
	std::sort(g.begin(), g.end()), std::reverse(g.begin(), g.end());
	int n = g.size(), k = d[u] - (fa > 0), sum1 = 0, sum0 = 0;
	for (register int i = 0; i < k - 1 && i < n; ++i) sum1 += g[i];
	for (register int i = 0; i < k && i < n; ++i) sum0 += g[i];
	f[u][0] = sum0;
	if (k == 0) return f[u][1] = -INF, void(0);
	f[u][1] = sum1;
	for (auto p : E[u]){
		int v = p.first, w = p.second;
		if (v == fa) continue;
		int f0 = f[v][0] + w, f1 = f[v][1] + w;
		if (k <= n && f0 < g[k - 1]) f[u][1] = std::max(sum1 + f1, f[u][1]);
		else f[u][1] = std::max(sum0 - f0 + f1, f[u][1]);
	}
}
int main(){
#ifdef AT_HOME
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	read(n), read(rt);
	for (register int i = 1, u, v, w; i < n; ++i)
		read(u), read(v), read(w), E[u].push_back({v, w}), E[v].push_back({u, w});
	for (register int i = 1; i <= n; ++i) read(d[i]);
	dfs(rt);
	print(f[rt][1]);
}