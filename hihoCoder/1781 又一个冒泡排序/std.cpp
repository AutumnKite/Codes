#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) ;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x;
}
namespace Work{
	#define N 100005
	int n, A[N], B[N];
	struct node{
		int x, id;
		bool operator < (const node &res) const {
			return x < res.x || x == res.x && id < res.id;
		}
	}a[N], b[N];
	struct Heap{
		int sz, a[N];
		void clear(){ sz = 0; }
		void push(int x){ a[++sz] = -x, std :: push_heap(a + 1, a + 1 + sz); }
		int top(){ return -a[1]; }
		int pop(){ return std :: pop_heap(a + 1, a + 1 + sz), -a[sz--]; }
	}H;
	int solve(){
		H.clear(), n = read();
		for (register int i = 1; i <= n; ++i) a[i] = (node){A[i] = read(), i};
		for (register int i = 1; i <= n; ++i) b[i] = (node){B[i] = read(), i};
		std :: sort(a + 1, a + 1 + n), std :: sort(b + 1, b + 1 + n);
		int k = 0;
		for (register int i = 1; i <= n; ++i)
			if (a[i].x == b[i].x) k = std :: max(k, a[i].id - b[i].id); else return -1;
		if (k <= 0) return k < 0 ? -1 : 0;
		for (register int i = 1; i <= k; ++i) H.push(A[i]);
		for (register int i = 1; i <= n; ++i){
			if (i + k <= n) H.push(A[i + k]);
			if (H.pop() != B[i]) return -1;
		}
		return k;
	}
}
int main(){
	int T = read();
	for (register int _ = 1; _ <= T; ++_)
		printf("Case #%d: %d\n", _, Work :: solve());
}
