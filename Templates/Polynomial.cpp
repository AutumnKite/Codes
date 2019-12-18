#include <cstdio>
#include <cctype>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
char buf[1 << 23], *ps = buf, *pt = buf, pbuf[1 << 23], *pp = pbuf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
namespace Random_Number{
	unsigned int seed = 19260817;
	void srnd(unsigned int x){ seed = x; }
	unsigned int rnd(){
		return seed ^= seed << 19, seed ^= seed >> 7, seed ^= seed << 1;
	}
}
using namespace Random_Number;
namespace Polynomial{
	typedef std :: vector<int> poly;
	const int P = 998244353, G = 3, I2 = 499122177;
	poly rev, omega;
	void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
	void dec(int &a, int b){ (a -= b) < 0 ? a += P : 0; }
	int plus(int a, int b){ return (a += b) >= P ? a - P : a; }
	int minus(int a, int b){ return (a -= b) < 0 ? a + P : a; }
	int qpow(int a, int b){
		int s = 1;
		for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
		return s;
	}
	int get(int n){
		int res = 1;
		while (res < n) res <<= 1;
		return res;
	}
	void init(int n){
		int k = 0;
		while ((1 << k) < n) ++k;
		rev.resize(n), rev[0] = 0, --k;
		for (register int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k);
		omega.resize(n);
		for (register int m = 1; m < n; m <<= 1){
			int _o = qpow(G, (P - 1) / (m << 1));
			omega[m] = 1;
			for (register int i = 1; i < m; ++i) omega[m + i] = 1ll * omega[m + i - 1] * _o % P;
		}
	}
	void DFT(poly &f, int n){
		f.resize(n);
		for (register int i = 0; i < n; ++i) if (i < rev[i]) std :: swap(f[i], f[rev[i]]);
		for (register int m = 1; m < n; m <<= 1){
			register int l = m << 1;
			for (poly :: iterator W = omega.begin() + m, F = f.begin(); F != f.end(); F += l)
				for (register int i = 0; i < m; ++i){
					register int t = 1ll * F[m + i] * W[i] % P;
					F[m + i] = minus(F[i], t), inc(F[i], t);
				}
		}
	}
	void IDFT(poly &f, int n){
		DFT(f, n), std :: reverse(f.begin() + 1, f.end());
		register int t = qpow(n, P - 2);
		for (register int i = 0; i < n; ++i) f[i] = 1ll * f[i] * t % P;
	}
	poly Plus(poly a, poly b){
		int n = std :: max(a.size(), b.size());
		a.resize(n), b.resize(n);
		poly res(n);
		for (register int i = 0; i < n; ++i) res[i] = plus(a[i], b[i]);
		return res;
	}
	poly Minus(poly a, poly b){
		int n = std :: max(a.size(), b.size());
		a.resize(n), b.resize(n);
		poly res(n);
		for (register int i = 0; i < n; ++i) res[i] = minus(a[i], b[i]);
		return res;
	}
	poly Multiply(poly a, poly b){
		if (!a.size() || !b.size()) return {};
		if (a.size() <= 30 && b.size() <= 30){
			poly res(a.size() + b.size() - 1);
			for (register int i = 0; i < a.size(); ++i)
				for (register int j = 0; j < b.size(); ++j)
					res[i + j] = (res[i + j] + 1ll * a[i] * b[j]) % P;
			return res;
		}
		int _n = a.size() + b.size() - 1, n = get(_n);
		init(n), DFT(a, n), DFT(b, n);
		for (register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * b[i] % P;
		IDFT(a, n), a.resize(_n);
		return a;
	}
	poly Pow2(poly a){
		int _n = a.size() * 2 - 1, n = get(_n);
		init(n), DFT(a, n);
		for (register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * a[i] % P;
		IDFT(a, n), a.resize(_n);
		return a;
	}
	poly Inverse(poly f, int _n){
		int n = get(_n);
		f.resize(n);
		poly g(1);
		g[0] = qpow(f[0], P - 2);
		for (register int m = 2; m <= n; ){
			poly tmp(m);
			for (register int i = 0; i < m; ++i) tmp[i] = f[i];
			m <<= 1;
			init(m), DFT(tmp, m), DFT(g, m);
			for (register int i = 0; i < m; ++i)
				g[i] = 1ll * g[i] * minus(2, 1ll * g[i] * tmp[i] % P) % P;
			IDFT(g, m), g.resize(m >> 1);
		}
		return g.resize(_n), g;
	}
	std :: pair<poly, poly> Divide(const poly &a, const poly &b){
		int n = a.size(), m = b.size();
		poly Q, R;
		if (n < m) return R = a, R.resize(m - 1), std :: make_pair(Q, R);
		poly A(a), B(b);
		std :: reverse(A.begin(), A.end()), A.resize(n - m + 1);
		std :: reverse(B.begin(), B.end()), B.resize(n - m + 1);
		Q = Multiply(A, Inverse(B, n - m + 1));
		Q.resize(n - m + 1), std :: reverse(Q.begin(), Q.end());
		R = Minus(a, Multiply(b, Q)), R.resize(m - 1);
		return std :: make_pair(Q, R);
	}
	poly Derivative(const poly &a){
		int n = a.size();
		poly res(n - 1);
		for (register int i = 1; i < n; ++i) res[i - 1] = 1ll * a[i] * i % P;
		return res;
	}
	poly Integral(const poly &a){
		int n = a.size();
		poly res(n + 1), inv(n + 1);
		res[0] = 0, inv[1] = 1;
		for (register int i = 2; i <= n; ++i) inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
		for (register int i = 1; i <= n; ++i) res[i] = 1ll * a[i - 1] * inv[i] % P;
		return res;
	}
	poly Ln(const poly &a, int n){
		poly res = Integral(Multiply(Derivative(a), Inverse(a, n)));
		return res.resize(n), res;
	}
	poly Exp(poly f, int _n){
		int n = get(_n);
		f.resize(n);
		poly g(1);
		g[0] = 1;
		for (register int m = 2; m <= n; ){
			poly tmp = Ln(g, m);
			for (register int i = 0; i < m; ++i) tmp[i] = minus(f[i], tmp[i]);
			inc(tmp[0], 1);
			m <<= 1, init(m), DFT(tmp, m), DFT(g, m);
			for (register int i = 0; i < m; ++i) g[i] = 1ll * g[i] * tmp[i] % P;
			IDFT(g, m), g.resize(m >> 1);
		}
		return g.resize(_n), g;
	}
	// void Exp_solve(const poly &a, poly &b, const poly &inv, int l, int r){
	// 	if (l + 1 == r) return l ? b[l] = 1ll * b[l] * inv[l] % P : b[l] = 1, void(0);
	// 	int md = (l + r + 1) >> 1;
	// 	Exp_solve(a, b, inv, l, md);
	// 	poly res = Multiply(poly(b.begin() + l, b.begin() + md), poly(a.begin(), a.begin() + r - l - 1));
	// 	for (register int i = md; i < r; ++i) inc(b[i], res[i - l - 1]);
	// 	Exp_solve(a, b, inv, md, r);
	// }
	// poly Exp(poly a, int _n){
	// 	a = Derivative(a), a.resize(_n);
	// 	poly b(_n), inv(_n);
	// 	inv[1] = 1;
	// 	for (register int i = 2; i < _n; ++i) inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	// 	return Exp_solve(a, b, inv, 0, _n), b;
	// }
	poly Pow(poly a, int k, int n){
		a.resize(n);
		int t = n;
		for (register int i = 0; i < n; ++i)
			if (a[i]){ t = i; break; }
		if (t == n) return !k ? a[0] = 1 : 0, a;
		int vi = qpow(a[t], P - 2), vk = qpow(a[t], k);
		for (register int i = 0; i < n - t; ++i) a[i] = 1ll * a[i + t] * vi % P;
		a.resize(n - t);
		t = std :: min(1ll * t * k, 1ll * n);
		a = Ln(a, n - t);
		for (register int i = 0; i < n - t; ++i) a[i] = 1ll * a[i] * k % P;
		a = Exp(a, n - t), a.resize(n);
		for (register int i = n - t - 1; ~i; --i) a[i + t] = 1ll * a[i] * vk % P;
		for (register int i = 0; i < t; ++i) a[i] = 0;
		return a;
	}
	struct Complex{
		int ii;
		struct node{
			int x, y;
			node(){}
			node(int _x, int _y){ x = _x, y = _y; }
		};
		node mul(const node &a, const node &b){
			return node((1ll * a.x * b.x + 1ll * ii * a.y % P * b.y) % P,
						(1ll * a.x * b.y + 1ll * a.y * b.x) % P);
		}
		node qpow(node a, int b){
			node s = node(1, 0);
			for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a);
			return s;
		}
	};
	int Sqrt(int n){
		if (qpow(n, (P - 1) >> 1) != 1) return -1;
		srnd(time(0));
		int a = rnd() % P;
		while (qpow((1ll * a * a + P - n) % P, (P - 1) >> 1) == 1) a = rnd() % P;
		Complex T;
		T.ii = (1ll * a * a + P - n) % P;
		int res = T.qpow(Complex :: node(a, 1), (P + 1) >> 1).x;
		return std :: min(res, P - res);
	}
	poly Sqrt(poly f, int _n){
		int n = get(_n);
		f.resize(n);
		poly g(1);
		g[0] = Sqrt(f[0]);
		for (register int m = 2; m <= n; m <<= 1){
			poly tmp(m);
			for (register int i = 0; i < m; ++i) tmp[i] = f[i];
			g = Multiply(Plus(Pow2(g), tmp), Inverse(g, m)), g.resize(m);
			for (register int i = 0; i < m; ++i) g[i] = 1ll * g[i] * I2 % P;
		}
		return g.resize(_n), g;
	}
	struct tree_node{
		int ls, rs;
		poly g;
	};
	int _T_cnt;
	std :: vector<tree_node> _T;
	int eval_inter_init(const poly &x, int l, int r){
		int u = _T_cnt++;
		_T[u].ls = _T[u].rs = -1, _T[u].g.resize(r - l + 1);
		if (l + 1 == r){
			_T[u].g[0] = minus(0, x[l]), _T[u].g[1] = 1;
			return u;
		}
		int md = (l + r + 1) >> 1;
		_T[u].ls = eval_inter_init(x, l, md);
		_T[u].rs = eval_inter_init(x, md, r);
		_T[u].g = Multiply(_T[_T[u].ls].g, _T[_T[u].rs].g);
		return u;
	}
	void Evaluate_solve(const poly &f, const poly &x, poly &y, int u, int l, int r){
		if (r - l <= 512){
			register int n = f.size();
			for (register int k = l; k < r; ++k){
				register int now = 0;
				register unsigned long long b[17], c1, c2, c3, c4;
				b[0] = 1;
				for (register int i = 1; i <= 16; ++i) b[i] = b[i - 1] * x[k] % P;
				for (register int i = n - 1; i - 15 >= 0; i -= 16){
					c1 = now * b[16] + f[i] * b[15] + f[i - 1] * b[14] + f[i - 2] * b[13];
					c2 = f[i - 3] * b[12] + f[i - 4] * b[11] + f[i - 5] * b[10] + f[i - 6] * b[9];
					c3 = f[i - 7] * b[8] + f[i - 8] * b[7] + f[i - 9] * b[6] + f[i - 10] * b[5];
					c4 = f[i - 11] * b[4] + f[i - 12] * b[3] + f[i - 13] * b[2] + f[i - 14] * b[1];
					now = (c1 + c2 + c3 + c4 + f[i - 15]) % P;
				}
				for (register int i = n % 16 - 1; ~i; --i) now = (1ll * now * x[k] + f[i]) % P;
				y[k] = now;
			}
			return;
		}
		int md = (l + r + 1) >> 1;
		poly R;
		R = Divide(f, _T[_T[u].ls].g).second;
		Evaluate_solve(R, x, y, _T[u].ls, l, md);
		R = Divide(f, _T[_T[u].rs].g).second;
		Evaluate_solve(R, x, y, _T[u].rs, md, r);
	}
	poly Evaluate(const poly &f, const poly &x){
		int m = x.size(), rt = -1;
		_T_cnt = 0, _T.resize(2 * m - 1), rt = eval_inter_init(x, 0, m);
		poly res(m);
		Evaluate_solve(f, x, res, rt, 0, m);
		return res;
	}
	poly Divide_2(poly a, int t){
		int n = a.size();
		poly b(n - 1);
		for (register int i = n - 1; i; --i){
			b[i - 1] = a[i];
			dec(a[i - 1], 1ll * a[i] * t % P);
		}
		return b;
	}
	poly Inter_solve(const poly &x, const poly &y, int u, int l, int r){
		if (r - l <= 64){
			poly f(r - l), g = _T[u].g;
			for (register int i = l; i < r; ++i){
				poly tmp = Divide_2(g, minus(0, x[i]));
				for (register int j = 0; j < r - l; ++j) f[j] = (f[j] + 1ll * tmp[j] * y[i]) % P;
			}
			return f;
		}
		int md = (l + r + 1) >> 1;
		poly A = _T[_T[u].rs].g, B = Inter_solve(x, y, _T[u].ls, l, md);
		poly C = _T[_T[u].ls].g, D = Inter_solve(x, y, _T[u].rs, md, r);
		int m = get(r - l);
		init(m), DFT(A, m), DFT(B, m), DFT(C, m), DFT(D, m);
		for (register int i = 0; i < m; ++i) A[i] = (1ll * A[i] * B[i] + 1ll * C[i] * D[i]) % P;
		IDFT(A, m), A.resize(r - l);
		return A;
	}
	poly Interpolation(poly x, poly y){
		int n = x.size(), rt = -1;
		_T_cnt = 0, _T.resize((n << 1) - 1), rt = eval_inter_init(x, 0, n);
		poly g = Derivative(_T[rt].g);
		poly res(n);
		Evaluate_solve(g, x, res, rt, 0, n);
		for (register int i = 0; i < n; ++i) y[i] = 1ll * y[i] * qpow(res[i], P - 2) % P;
		return Inter_solve(x, y, rt, 0, n);
	}
}
using Polynomial :: poly;
using Polynomial :: Interpolation;
int main(){
	int n = read();
	poly x(n), y(n);
	for (register int i = 0; i < n; ++i) x[i] = read(), y[i] = read();
	poly res = Interpolation(x, y);
	for (register int i = 0; i < n; ++i) print(res[i], ' ');
}