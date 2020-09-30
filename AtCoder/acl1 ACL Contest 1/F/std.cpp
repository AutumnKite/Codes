#include <bits/stdc++.h>
#include <atcoder/all>

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
		if (n < 0) {
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

const int M = 33, N = M * 3, INF = 0x3f3f3f3f;

int n, m, a[N], b[N];
std::vector<int> pa[M], pb[M];

int solve(int l, int r) {
	auto check_type = [&](int x) {
		return x < l ? -1 : (x >= r ? 1 : 0);
	};
	std::vector<int> type(m, -1);
	std::vector<std::pair<int, int>> line;
	for (int i = 0; i < m; ++i) {
		if (check_type(pb[i][2]) < 0 || check_type(pb[i][0]) > 0) { // LLL or RRR
			return INF;
		}
		if (check_type(pb[i][1]) < 0 && check_type(pb[i][2]) > 0) { // LLR
			type[i] = 1;
			continue;
		}
		if (check_type(pb[i][0]) < 0 && check_type(pb[i][1]) > 0) { // LRR
			type[i] = 2;
			continue;
		}
		if (check_type(pb[i][0]) < 0 && check_type(pb[i][1]) == 0 && check_type(pb[i][2]) > 0) { // LMR
			type[i] = 0;
			continue;
		}
		if (check_type(pb[i][0]) == 0 && check_type(pb[i][1]) > 0) { // MRR
			line.push_back({pa[i][0], pb[i][0]});
			continue;
		}
		if (check_type(pb[i][1]) < 0 && check_type(pb[i][2]) == 0) { // LLM
			line.push_back({pa[i][2], pb[i][2]});
			continue;
		}
		if (check_type(pb[i][0]) == 0 && check_type(pb[i][2]) == 0) { // MMM
			line.push_back({pa[i][0], pb[i][0]});
			line.push_back({pa[i][1], pb[i][1]});
			line.push_back({pa[i][2], pb[i][2]});
			continue;
		}
		if (check_type(pb[i][0]) < 0 && check_type(pb[i][1]) == 0 && check_type(pb[i][2]) == 0) { // LMM
			line.push_back({pa[i][0], pb[i][1]});
			line.push_back({pa[i][2], pb[i][2]});
			continue;
		}
		if (check_type(pb[i][0]) == 0 && check_type(pb[i][1]) == 0 && check_type(pb[i][2]) > 0) { // MMR
			line.push_back({pa[i][0], pb[i][0]});
			line.push_back({pa[i][2], pb[i][1]});
			continue;
		}
	}
	for (int i = 0; i < (int)line.size(); ++i) {
		for (int j = i + 1; j < (int)line.size(); ++j) {
			if ((line[i].first < line[j].first) ^ (line[i].second < line[j].second)) {
				return INF;
			}
		}
	}
	atcoder::two_sat G(m);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (~type[i] && ~type[j] && pb[j][0] < pb[i][0] && pb[j][2] < pb[i][2]) {
				G.add_clause(i, 0, j, 1);
			}
		}
		bool flag0 = type[i] == 2, flag1 = type[i] == 1;
		if (type[i] == 0) {
			for (int j = 0; j < (int)line.size(); ++j) {
				if ((pa[i][2] < line[j].first) ^ (pb[i][1] < line[j].second)) {
					flag0 = true;
				}
				if ((pa[i][0] < line[j].first) ^ (pb[i][1] < line[j].second)) {
					flag1 = true;
				}
			}
			for (int j = 0; j < i; ++j) {
				if (type[j] == 0) {
					if ((pa[i][2] < pa[j][2]) ^ (pb[i][1] < pb[j][1])) {
						G.add_clause(i, 1, j, 1);
					}
					if ((pa[i][0] < pa[j][2]) ^ (pb[i][1] < pb[j][1])) {
						G.add_clause(i, 0, j, 1);
					}
					if ((pa[i][2] < pa[j][0]) ^ (pb[i][1] < pb[j][1])) {
						G.add_clause(i, 1, j, 0);
					}
					if ((pa[i][0] < pa[j][0]) ^ (pb[i][1] < pb[j][1])) {
						G.add_clause(i, 0, j, 0);
					}
				}
			}
		}
		if (flag1) {
			G.add_clause(i, 1, i, 1);
		}
		if (flag0) {
			G.add_clause(i, 0, i, 0);
		}
	}
	if (!G.satisfiable()) {
		return INF;
	} else {
		debug("%d %d\n", l, r);
		return n - (r - l);
	}
}

int main() {
	read(m), n = m * 3;
	for (int i = 0; i < n; ++i) {
		read(a[i]);
		--a[i];
		pa[a[i]].push_back(i);
	}
	for (int i = 0; i < n; ++i) {
		read(b[i]);
		--b[i];
		pb[b[i]].push_back(i);
	}
	int ans = INF;
	for (int i = 0; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			ans = std::min(ans, solve(i, j));
		}
	}
	if (ans == INF) {
		print(-1);
	} else {
		print(ans);
	}
}
