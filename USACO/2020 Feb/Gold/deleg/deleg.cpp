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
const int N = 100005;
int n, k, ans[N];
std::vector<int> E[N];
int cnt[N], sz[N], mx[N];
void init(int u, int fa = 0){
	sz[u] = 1, mx[u] = 0;
	for (int v : E[u]) if (v != fa) init(v, u), sz[u] += sz[v], mx[u] = std::max(mx[u], mx[v] + 1);
}
bool dfs(int u, int fa = 0){
	std::vector<int> pa;
	for (int v : E[u])
		if (v != fa){
			if (!dfs(v, u)) return 0;
			else if (sz[v] % k) pa.push_back(sz[v] % k);
		}
	int s = pa.size();
	for (int v : pa) ++cnt[v];
	for (int v : pa) if ((v != k - v && cnt[v] && cnt[k - v]) || (v == k - v && cnt[v] >= 2)) --cnt[v], --cnt[k - v], s -= 2;
	for (int v : pa) cnt[v] = 0;
	return s <= 1;
}
int main(){
	freopen("deleg.in", "r", stdin);
	freopen("deleg.out", "w", stdout);
	read(n);
	for (register int i = 1, u, v; i < n; ++i)
		read(u), read(v), E[u].push_back(v), E[v].push_back(u);
	init(1);
	ans[1] = 1, k = 2;
	int lim = std::min(n, 2 * mx[1] + 1);
	while (k < lim){
		while (k < lim && (n - 1) % k) ++k;
		if (k == lim) break;
		ans[k] = dfs(1), ++k;
	}
	for (register int i = 1; i < n; ++i) putchar(ans[i] ^ '0');
	putchar('\n');
}