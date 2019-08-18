#include <cstdio>
#include <algorithm>
#define P 1000000007
int A, B, n, m, fac[200005], inv[200005], dp[50];
struct node{
	int x, y;
	bool operator < (const node &res) const {
		return x < res.x || x == res.x && y < res.y;
	}
	bool operator == (const node &res) const {
		return x == res.x && y == res.y;
	}
}p[50];
bool check(int m){
	return p[m].y <= p[m].x && p[m].y >= p[m].x - A + B;
}
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
void pre(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
	inv[n] = qpow(fac[n], P - 2);
	for (register int i = n; i; --i) inv[i - 1] = 1ll * inv[i] * i % P;
}
int F(node a, node b){
	if (a.x > b.x || a.y > b.y) return 0;
	return 1ll * fac[b.x - a.x + b.y - a.y] * inv[b.x - a.x] % P * inv[b.y - a.y] % P;
}
void add(int &x, int y){ (x += y) >= P ? x -= P : 0; }
void del(int &x, int y){ (x -= y) < 0 ? x += P : 0; }
int calc(node a, node b){
	int res = F(a, b), w = A - B + 2;
	for (register node c = (node){b.y - 1, b.x + 1}; c.x >= a.x; c.x -= w, c.y += w) del(res, F(a, c));
	for (register node c = (node){b.x - w, b.y + w}; c.x >= a.x; c.x -= w, c.y += w) add(res, F(a, c));
	for (register node c = (node){b.y + w - 1, b.x - w + 1}; c.y >= a.y; c.x += w, c.y -= w) del(res, F(a, c));
	for (register node c = (node){b.x + w, b.y - w}; c.y >= a.y; c.x += w, c.y -= w) add(res, F(a, c));
	return res;
}
int main(){
	scanf("%d%d%d", &A, &B, &n), pre(A + B);
	if (A == B) return printf("0\n"), 0;
	for (register int i = 1, x, y; i <= n; ++i){
		scanf("%d%d", &x, &y);
		if (!x && !y) return printf("0\n"), 0;
		if (x == A && x == B) return printf("0\n"), 0;
		p[++m] = (node){x, y}, !check(m) ? --m : 0;
		p[++m] = (node){A - x, B - y}, !check(m) ? --m : 0;
	}
	p[0] = (node){0, 0}, p[++m] = (node){A, B};
	std :: sort(p + 1, p + 1 + m);
	m = std :: unique(p + 1, p + 1 + m) - p - 1;
	for (register int i = 1; i <= m; ++i){
		dp[i] = calc(p[0], p[i]);
		for (register int j = 1; j < i; ++j)
			(dp[i] -= 1ll * dp[j] * calc(p[j], p[i]) % P) < 0 ? dp[i] += P : 0;
	}
	printf("%d\n", dp[m]);
}
