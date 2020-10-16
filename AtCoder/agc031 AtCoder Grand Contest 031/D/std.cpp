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

const int N = 100005;

typedef std::vector<int> Perm;

int n, k;

Perm Inv(const Perm &a) {
	Perm res(a.size());
	for (int i = 0; i < (int)a.size(); ++i) {
		res[a[i]] = i;
	}
	return res;
}

Perm Mul(const Perm &a, const Perm &b) {
	Perm res(a.size());
	for (int i = 0; i < (int)a.size(); ++i) {
		res[i] = b[a[i]];
	}
	return res;
}

Perm Pow(const Perm &a, int k) {
	int n = a.size();
	Perm res(n);
	std::vector<bool> vis(n);
	for (int i = 0; i < n; ++i) {
		if (!vis[i]) {
			std::vector<int> cyc;
			for (int j = i; !vis[j]; j = a[j]) {
				vis[j] = 1;
				cyc.push_back(j);
			}
			for (int i = 0; i < (int)cyc.size(); ++i) {
				res[cyc[i]] = cyc[(i + k) % (int)cyc.size()];
			}
		}
	}
	return res;
}

int main() {
	read(n), read(k), --k;
	Perm p(n), q(n);
	for (int i = 0; i < n; ++i) {
		read(p[i]);
		--p[i];
	}
	for (int i = 0; i < n; ++i) {
		read(q[i]);
		--q[i];
	}
	std::vector<Perm> a(6);
	a[0] = p, a[1] = q;
	for (int i = 2; i < 6; ++i) {
		a[i] = Mul(Inv(a[i - 2]), a[i - 1]);
	}
	Perm A = Mul(Mul(Inv(q), p), Mul(q, Inv(p)));
	Perm res = Mul(Mul(Pow(A, k / 6), a[k % 6]), Pow(Inv(A), k / 6));
	for (int v : res) {
		print(v + 1, ' ');
	}
	putchar('\n');
}
