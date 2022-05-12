#include <cstdio>
#include <cstdlib>

class trilib
{
public:
	trilib() {
		n = 0; inited = false;
		queries = 0;
	}
	int get_n() {
		init();
		return n;
	}
	bool is_clockwise(int a, int b, int c) {
		init();
		checkArgs(1 <= a && a <= n, -1);
		checkArgs(1 <= b && b <= n, -1);
		checkArgs(1 <= c && c <= n, -1);
		checkArgs(a != b && b != c && c != a, -1);
		queries++;
		checkArgs(queries <= 1000000, -2);
		return (x[b] - x[a]) * (y[c] - y[a]) - (x[c] - x[a]) * (y[b] - y[a]) < 0;
	}
	void give_answer(int s) {
		init(); long long x;
		printf("%d\n", s); fflush(stdout);
		checkArgs(scanf("%lld", &x) == 1, -3);
		checkArgs(x == 1145141919810LL, -3);
		printf("%d queries\n", queries); fflush(stdout);
		return ;
	}
private:
	#define N 40001
	int n, queries; bool inited;
	long long x[N], y[N];
	void init() {
		if (inited)
			return;
		checkArgs(scanf("%d", &n) == 1, -3);
		for (int i = 1; i <= n; i++)
			checkArgs(scanf("%lld %lld", &x[i], &y[i]) == 2, -3);
		inited = true;
		return ;
	}
	void checkArgs(bool cond, int fail) {
		if (!cond) {
			printf("%d\n", fail); fflush(stdout);
			exit(0);
		}
	}
	#undef N
}___lib____;

int get_n() {
	return ___lib____.get_n();
}

bool is_clockwise(int a, int b, int c) {
	return ___lib____.is_clockwise(a, b, c);
}

void give_answer(int s) {
	___lib____.give_answer(s);
	return ;
}
