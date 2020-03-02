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
int n, k, len[N];
std::vector<int> E[N];
bool work(std::vector<int> pa, int &res){
	std::vector<int> sta;
	while (pa.size() && pa.back() >= k) sta.push_back(pa.back()), pa.pop_back();
	int tmp = 0;
	for (register int i = 0; i < (int)pa.size(); ++i){
		// fprintf(stderr, "sta: ");
		// for (int v : sta) fprintf(stderr, "%d ", v);
		// fprintf(stderr, "\n");
		while (i < (int)pa.size() - 1 && pa[i] + pa.back() >= k) sta.push_back(pa.back()), pa.pop_back();
		if (sta.size()){ sta.pop_back(); continue; }
		if (tmp) return 0; else tmp = pa[i];
	}
	// fprintf(stderr, "sta: ");
	// for (int v : sta) fprintf(stderr, "%d ", v);
	// fprintf(stderr, "\n");
	while (sta.size() > 2) sta.pop_back(), sta.pop_back();
	if (sta.size() == 2){
		if (sta.back() < k) sta.pop_back(), sta.pop_back();
		else return res = sta[0], 1;
	}
	if (sta.size() == 1){
		if (tmp) return 0;
		else return res = sta[0], 1;
	}
	return res = tmp, 1;
}
bool dfs(int u, int fa = 0){
	std::vector<int> pa;
	for (int v : E[u])
		if (v != fa){
			if (!dfs(v, u)) return 0;
			else pa.push_back(len[v] + 1);
		}
	// fprintf(stderr, "u = %d\n", u);
	std::sort(pa.begin(), pa.end());
	int s1, s2;
	if (!work(pa, s1)) return 0;
	// else return len[u] = s1, 1;
	if (pa.empty() || pa.back() < k || s1) return len[u] = s1, 1;
	pa.pop_back();
	if (!work(pa, s2)) return len[u] = s1, 1;
	else return len[u] = std::max(s1, s2), 1;
}
bool check(int md){
	k = md;
	std::vector<int> pa;
	for (int v : E[1]){
		if (!dfs(v, 1)) return 0;
		else pa.push_back(len[v] + 1);
	}
	std::sort(pa.begin(), pa.end());
	if (!work(pa, len[1])) return 0;
	return !len[1] || len[1] >= k;
}
int main(){
	freopen("deleg.in", "r", stdin);
	freopen("deleg.out", "w", stdout);
	read(n);
	for (register int i = 1, u, v; i < n; ++i)
		read(u), read(v), E[u].push_back(v), E[v].push_back(u);
	// fprintf(stderr, "%d\n", check(3));
	int l = 1, r = n - 1, md, ans = 0;
	while (l <= r) if (check(md = (l + r) >> 1)) l = md + 1, ans = md; else r = md - 1;
	print(ans);
}