#include <bits/stdc++.h>

#define debug(...) fprintf(stderr, __VA_ARGS__)

namespace IO {
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

std::mt19937_64 generator(time(0));

inline unsigned long long rnd() {
	return generator();
}

template<typename T>
inline T rnd(T a, T b) {
	return rnd() % (b - a + 1) + a;
}

char name[105], input[105], output[105], run[305];

void start(int id) {
	sprintf(name, "data%d", id);
	sprintf(input, "%s.in", name);
	sprintf(output, "%s.ans", name);
	freopen(input, "w", stdout);
}

void finish() {
	fclose(stdout);
	sprintf(run, "std < %s > %s", input, output);
	system(run);
	sprintf(run, "wfr %s -r:\"\\r\\n\" -t:\"\\n\"", input);
	system(run);
	sprintf(run, "wfr %s -r:\"\\r\\n\" -t:\"\\n\"", output);
	system(run);
}
