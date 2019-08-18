#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
struct BigInt{
	const static long long P = 1000000000;
	std :: vector<long long> a;
	BigInt operator = (int x){
		while (x) a.push_back(x % P), x /= P;
		return *this;
	}
	BigInt operator + (const BigInt &b) const {
		BigInt c;
		c.a.resize(std :: max(a.size(), b.a.size()) + 1);
		for (register int i = 0; i < a.size(); ++i) c.a[i] += a[i];
		for (register int i = 0; i < b.a.size(); ++i) c.a[i] += b.a[i];
		for (register int i = 0; i < c.a.size() - 1; ++i)
			c.a[i + 1] += c.a[i] / P, c.a[i] %= P;
		while (c.a.size() && !c.a[c.a.size() - 1]) c.a.pop_back();
		return c;
	}
	BigInt operator += (const BigInt &b){
		return *this = *this + b;
	}
	BigInt operator - (const BigInt &b) const {
		BigInt c;
		c.a.resize(a.size() + 1);
		for (register int i = 0; i < c.a.size() - 1; ++i){
			c.a[i] += a[i] - (i < b.a.size() ? b.a[i] : 0);
			if (c.a[i] < 0) --c.a[i + 1], c.a[i] += P;
		}
		while (c.a.size() && !c.a[c.a.size() - 1]) c.a.pop_back();
		return c;
	}
	BigInt operator -= (const BigInt &b){
		return *this = *this - b;
	}
	BigInt operator * (const BigInt &b) const {
		BigInt c;
		c.a.resize(a.size() + b.a.size());
		for (register int i = 0; i < a.size(); ++i)
			for (register int j = 0; j < b.a.size(); ++j)
				c.a[i + j] += a[i] * b.a[j], c.a[i + j + 1] += c.a[i + j] / P, c.a[i + j] %= P;
		while (c.a.size() && !c.a[c.a.size() - 1]) c.a.pop_back();
		return c;
	}
	void print(){
		if (!a.size()) return putchar('0'), void(0);
		printf("%lld", a[a.size() - 1]);
		for (register int i = a.size() - 2; ~i; --i){
			int x = a[i], cnt = 0, num[10];
			memset(num, 0, sizeof num);
			while (x) num[++cnt] = x % 10, x /= 10;
			for (register int j = 9; j; --j) putchar(num[j] + '0');
		}
	}
};
BigInt C[51][51], pow[1230], f[51];
int n;
int main(){
	C[0][0] = 1;
	for (register int i = 1; i <= 50; ++i){
		C[i][0] = C[i][i] = 1;
		for (register int j = 1; j < i; ++j)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
	pow[0] = 1;
	for (register int i = 1; i <= 1225; ++i) pow[i] = pow[i - 1] + pow[i - 1];
	for (register int i = 1; i <= 50; ++i){
		f[i] = pow[i * (i - 1) >> 1];
		// printf("%d ", i), f[i].print(), putchar(' ');
		for (register int j = 1; j < i; ++j)
			f[i] -= C[i - 1][j - 1] * f[j] * pow[(i - j) * (i - j - 1) >> 1];
		// f[i].print(), putchar('\n');
	}
	while (scanf("%d", &n), n) f[n].print(), putchar('\n');
}