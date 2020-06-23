#include <cstdio>
#include <cctype>
#include <cstring>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>

#define debug(...) fprintf(stderr, __VA_ARGS__)

namespace generator{
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
	
	unsigned long long seed = 0x3C9FC1DA24BB75DFull;

	inline void srnd(unsigned long long _sd) {
		seed ^ _sd ? seed ^= _sd : 0;
	}

	inline unsigned long long rnd() {
		seed ^= seed << 13;
		seed ^= seed >> 7;
		seed ^= seed << 17;
		return seed + 0x764FF49E4F6C521Dull;
	}

	template<typename T>
	T rnd(T a, T b) {
		return rnd() % (unsigned long long)(b - a + 1) + a;
	}

	template<typename T>
	void myShuffle(T first, T last) {
		for (T i = first; i < last; ++i) {
			T j = first + rnd() % (i - first + 1);
			if (i != j) std::swap(*i, *j);
		}
	}
}
using namespace generator;

char name[105], input[105], run[305];

void start(int id) {
	sprintf(name, "data%d", id);
	sprintf(input, "%s.in", name);
	freopen(input, "w", stdout);
}

void finish() {
	fclose(stdout);
	sprintf(run, "./std < %s > %s.ans", input, name);
	system(run);
}
