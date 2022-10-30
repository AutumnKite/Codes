#include "integer.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>
namespace SampleIntegerGrader
{
	int n, p[1 << 21], S[1 << 21];
	int currentPopcnt, ops;
	double scoreof(const int s) {
		if(s < 800000) return 1;
		if(s <= 2000000) return 800000.0 / s;
		if(s > 200000000) return 0;
		return (9 - log10(s * 5)) / 5;
	}
	void reportResult(const std::vector<int> &answer) {
		if((int)answer.size() != n)
			puts("WA"), (void)printf("Invalid Answer length: expected %d, found %d\n", n, (int)answer.size()), exit(-1);
		for(int i=0; i<n; i++)
			if(answer[i] != p[i])
				puts("WA"), (void)printf("Incorrect answer: p_%d is expected to be %d but found %d\n", i, p[i], answer[i]), exit(-1);
		puts("OK"), (void)printf("Passed using %d operation(s): scoring %.3lf\n", ops, scoreof(ops));
	}
	void quitHalf(const int kth) {
		puts("WA"), printf("Invalid query: Operation on %d violates range [0,%d]\n", kth, n - 1);
		exit(-1);
	}
	int operate(const int kth) {
		if(kth < 0 || kth >= n)
			quitHalf(kth);
		ops++;
		S[p[kth]]++, currentPopcnt++;
		for(int i = p[kth]; S[i] == 2; i++)
			S[i] = 0, S[i + 1]++, currentPopcnt--;
		return currentPopcnt;
	}
	void main() {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%d", p + i);
		auto vans = findPermutation(n);
		reportResult(vans);
	}
}
int operate(const int kth) {
	return SampleIntegerGrader::operate(kth);
}
int main() {
	SampleIntegerGrader::main();
	return 0;
}
