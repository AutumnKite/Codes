#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
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
const int N = 200005;
int n, m;
std::vector<int> E[N];
int fa[N], col[N];
void init(int n){
	for (register int i = 1; i <= n; ++i) fa[i] = i;
}
int find(int x){ return fa[x] == x ? x : (fa[x] = find(fa[x])); }
std::map<int, int> S;
int main(){
	freopen("fcolor.in", "r", stdin);
	freopen("fcolor.out", "w", stdout);
	read(n), read(m);
	for (register int i = 1; i <= m; ++i){
		int x, y;
		read(x), read(y);
		E[x].push_back(y);
	}
	for (register int i = 1; i <= n; ++i)
		if ((int)E[i].size() > 1) S[i] = E[i].size();
	init(n);
	while (!S.empty()){
		int u = S.begin()->first;
		for (register int i = 1; i < (int)E[u].size(); ++i){
			int x = E[u][i - 1], y = E[u][i];
			x = find(x), y = find(y);
			if (x == y) continue;
			if (E[x].size() < E[y].size()) std::swap(x, y);
			for (int v : E[y]) E[x].push_back(v);
			fa[y] = x, E[y].clear(), S.erase(y);
		}
		int v = find(E[u][0]);
		E[u].clear(), E[u].push_back(v), S.erase(u);
		if ((int)E[v].size() > 1) S[v] = E[v].size();
	}
	int cnt = 0;
	for (register int i = 1; i <= n; ++i){
		int x = find(i);
		if (!col[x]) col[x] = ++cnt;
		print(col[x]);
	}
}
