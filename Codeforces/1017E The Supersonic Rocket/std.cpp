#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

#define int long long

#define debug(...) fprintf(stderr, __VA_ARGS__)

#ifndef AT_HOME
#define getchar() IO::myGetchar()
#define putchar(x) IO::myPutchar(x)
#endif

namespace IO {
	static const int IN_BUF = 1 << 23, OUT_BUF = 1 << 23;

	inline char myGetchar() {
		static char buf[IN_BUF], *ps = buf, *pt = buf;
		if (ps == pt) {
			ps = buf, pt = buf + fread(buf, 1, IN_BUF, stdin);
		}
		return ps == pt ? EOF : *ps++;
	}

	template<typename T>
	inline bool read(T &x) {
		bool op = 0;
		char ch = getchar();
		x = 0;
		for (; !isdigit(ch) && ch != EOF; ch = getchar()) {
			op ^= (ch == '-');
		}
		if (ch == EOF) {
			return false;
		}
		for (; isdigit(ch); ch = getchar()) {
			x = x * 10 + (ch ^ '0');
		}
		if (op) {
			x = -x;
		}
		return true;
	}

	inline int readStr(char *s) {
		int n = 0;
		char ch = getchar();
		for (; isspace(ch) && ch != EOF; ch = getchar())
			;
		for (; !isspace(ch) && ch != EOF; ch = getchar()) {
			s[n++] = ch;
		}
		s[n] = '\0';
		return n;
	}

	inline void myPutchar(char x) {
		static char pbuf[OUT_BUF], *pp = pbuf;
		struct _flusher {
			~_flusher() {
				fwrite(pbuf, 1, pp - pbuf, stdout);
			}
		};
		static _flusher outputFlusher;
		if (pp == pbuf + OUT_BUF) {
			fwrite(pbuf, 1, OUT_BUF, stdout);
			pp = pbuf;
		}
		*pp++ = x;
	}

	template<typename T>
	inline void print_(T x) {
		if (x == 0) {
			putchar('0');
			return;
		}
		std::vector<int> num;
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		for (; x; x /= 10) {
			num.push_back(x % 10);
		}
		while (!num.empty()) {
			putchar(num.back() ^ '0');
			num.pop_back();
		}
	}

	template<typename T>
	inline void print(T x, char ch = '\n') {
		print_(x);
		putchar(ch);
	}

	inline void printStr_(const char *s, int n = -1) {
		if (n == -1) {
			n = strlen(s);
		}
		for (int i = 0; i < n; ++i) {
			putchar(s[i]);
		}
	}

	inline void printStr(const char *s, int n = -1, char ch = '\n') {
		printStr_(s, n);
		putchar(ch);
	}
}
using namespace IO;

const int N = 100005;

int n, m;

const double eps = 1e-9;

int sgn(double a) {
	return a <= -eps ? -1 : (a >= eps ? 1 : 0);
}

struct Point {
	long long x, y;
	
	Point operator + (const Point &rhs) const {
		return {x + rhs.x, y + rhs.y};
	}
	
	Point operator - (const Point &rhs) const {
		return {x - rhs.x, y - rhs.y};
	}
};

long long dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

long long cross(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

long long dis2(const Point &a, const Point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double angle(const Point &a, const Point &b) {
	return atan2(cross(a, b), dot(a, b));
}

typedef std::vector<Point> polygon;

polygon convex(polygon f) {
	int n = f.size();
	int mn = std::min_element(f.begin(), f.end(), [&](const Point &a, const Point &b) {
		return a.y < b.y || (a.y == b.y && a.x < b.x);
	}) - f.begin();
	std::swap(f[0], f[mn]);
	std::sort(f.begin() + 1, f.end(), [&](const Point &a, const Point &b) {
		long long t = cross(a - f[0], b - f[0]);
		if (t != 0) {
			return t > 0;
		}
		return dis2(a, f[0]) < dis2(b, f[0]);
	});
	polygon g(1, f[0]);
	for (int i = 1; i < n; ++i) {
		while ((int)g.size() > 1 && cross(g.back() - g[(int)g.size() - 2], f[i] - g.back()) <= 0) {
			g.pop_back();
		}
		g.push_back(f[i]);
	}
	return g;
}

template<typename T, typename Comp>
int minpos(const std::vector<T> &a, Comp cmp) {
	int n = a.size();
	int k = 0, i = 0, j = 1;
	while (k < n && i < n && j < n) {
		T x = a[(i + k) % n], y = a[(j + k) % n];
		if (!cmp(x, y) && !cmp(y, x)) {
			++k;
		} else {
			if (cmp(x, y)) {
				std::swap(i, j);
			}
			i = i + k + 1;
			if (i == j) {
				++i;
			}
			k = 0;
		}
	}
	return std::min(i, j);
}

void solve() {
	read(n), read(m);
	polygon a(n), b(m);
	for (int i = 0; i < n; ++i) {
		read(a[i].x), read(a[i].y);
	}
	for (int i = 0; i < m; ++i) {
		read(b[i].x), read(b[i].y);
	}
	a = convex(a), b = convex(b);
	n = a.size(), m = b.size();
	debug("\n");
	for (int i = 0; i < n; ++i) {
		debug("%lld %lld\n", a[i].x, a[i].y);
	}
	debug("\n");
	for (int i = 0; i < m; ++i) {
		debug("%lld %lld\n", b[i].x, b[i].y);
	}
	if (n != m) {
		printStr("NO");
		return;
	}
	bool fla = 1, flb = 1;
	std::vector<long long> sda(n), sdb(n);
	for (int i = 0; i < n; ++i) {
		sda[i] = dis2(a[i], a[(i + 1) % n]);
		sdb[i] = dis2(b[i], b[(i + 1) % n]);
		fla &= sda[i] == sda[0];
		flb &= sdb[i] == sdb[0];
	}
	if (fla || flb) {
		if (!fla || !flb || sda[0] != sdb[0]) {
			printStr("NO");
			return;
		}
		auto cmp_db = [&](double a, double b) {
			return sgn(a - b) < 0;
		};
		std::vector<double> ana(n), anb(n);
		for (int i = 0; i < n; ++i) {
			ana[i] = angle(a[(i + n - 1) % n] - a[i], a[(i + 1) % n] - a[i]);
			anb[i] = angle(b[(i + n - 1) % n] - b[i], b[(i + 1) % n] - b[i]);
		}
		int pa = minpos(ana, cmp_db), pb = minpos(anb, cmp_db);
		for (int i = 0; i < n; ++i) {
			if (sgn(ana[(pa + i) % n] - anb[(pb + i) % n])) {
				printStr("NO");
				return;
			}
		}
		printStr("YES");
		return;
	}
	auto cmp_ll = [&](long long a, long long b) {
		return a < b;
	};
	int pa = minpos(sda, cmp_ll), pb = minpos(sdb, cmp_ll);
	for (int i = 0; i < n; ++i) {
		if (sda[(pa + i) % n] != sdb[(pb + i) % n]) {
			printStr("NO");
			return;
		}
	}
	printStr("YES");
}

signed main() {
	int T = 1;
//	read(T);
	while (T--) {
		solve();
	}
}

