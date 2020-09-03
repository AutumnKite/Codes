#include <bits/stdc++.h>

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
		static int num[40];
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		for (*num = 0; x; x /= 10) {
			num[++*num] = x % 10;
		}
		while (*num){
			putchar(num[*num] ^ '0');
			--*num;
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

const int N = 200005;

const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n;

struct Node {
	int x, y, id;
	
	bool operator < (const Node &rhs) const {
		return x < rhs.x;
	}
} a[N];

long long ans[N];

std::vector<int> Y;

int myabs(int a) {
	return a > 0 ? a : -a;
}

int dist(int i, int j) {
	return myabs(a[i].x - a[j].x) + myabs(a[i].y - a[j].y);
}

void upd(long long &a, long long b) {
	a = std::min(a, b);
}

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i].x), read(a[i].y);
		a[i].id = i;
		Y.push_back(a[i].y);
		ans[i] = -1;
	}
	std::sort(a + 1, a + 1 + n);
	Y.push_back(0), Y.push_back(1000001);
	std::sort(Y.begin(), Y.end());

	for (int st = 1; st <= n; ++st) {
		if (~ans[a[st].id]) {
			continue;
		}

		int y = std::lower_bound(Y.begin(), Y.end(), a[st].y) - Y.begin();
		int L = st, R = st;
		int Ly = y - 1, Ry = y + 1;

		int lst = -1;
		std::vector<std::pair<int, int>> A;

		while (1) {
			bool flag = 0;
			for (int i : {L - 1, R + 1}) {
				if (1 <= i && i <= n) {
					bool fL = Y[Ly] == a[i].y;
					bool fR = Y[Ry] == a[i].y;
					if (fL || fR) {
						int d = fL ^ (i == L - 1);
						if (lst == -1) {
							lst = d;
						}
						if (lst != d) {
							A.push_back({L, R});
							lst = d;
						}
						if (fL) {
							--Ly;
						} else {
							++Ry;
						}
						if (i == L - 1) {
							--L;
						} else {
							++R;
						}
						flag = 1;
						break;
					}
				}
			}
			if (!flag) {
				break;
			}
		}
		if (A.empty() || A.back() != std::make_pair(L, R)) {
			A.push_back({L, R});
		}

		int t = A.size();
		std::vector<std::vector<long long>> f(t, std::vector<long long>(2, INF));
		f[t - 1][0] = f[t - 1][1] = 0;
		for (int i = t - 1; i; --i) {
			int L1 = A[i].first;
			int L2 = A[i - 1].first;
			int R1 = A[i - 1].second;
			int R2 = A[i].second;
			upd(f[i - 1][0], f[i][0] + (R1 == R2 ? dist(L1, L2) : dist(L2, R2) + dist(L1, R2)));
			upd(f[i - 1][1], f[i][0] + dist(R1, R2) + dist(L1, R2));
			upd(f[i - 1][0], f[i][1] + dist(L1, L2) + dist(L1, R2));
			upd(f[i - 1][1], f[i][1] + (L1 == L2 ? dist(R1, R2) : dist(L1, R1) + dist(L1, R2)));
		}
		// if (L == 1 && R == 5) {
		// 	debug("%lld %lld\n", f[0][0], f[0][1]);
		// }
		
		int l = A[0].first, r = A[0].second;
		for (int i = l; i <= r; ++i) {
			ans[a[i].id] = std::min(f[0][0] + dist(l, r) + dist(r, i), f[0][1] + dist(l, r) + dist(l, i)) - (R - L);
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		print(ans[i]);
	}
}
