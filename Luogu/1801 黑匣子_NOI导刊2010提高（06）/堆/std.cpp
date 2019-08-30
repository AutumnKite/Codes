#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <functional>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
int n, m, a[200005], b[200005];
struct Heap{
	int size, a[200005];
	typedef bool (*func)(int, int);
	func cmp;
	void clear(func Cmp){ memset(a, 0, sizeof a), size = 0, cmp = Cmp; }
	void push(int x){ a[++size] = x, std :: push_heap(a + 1, a + 1 + size, cmp); }
	int top(){ return a[1]; }
	int pop(){ return std :: pop_heap(a + 1, a + 1 + size, cmp), a[size--]; }
}H1, H2;
bool cmp1(int a, int b){ return a < b; }
bool cmp2(int a, int b){ return a > b; }
void Add(int x){
	if (x >= H1.top()) H2.push(x);
	else H2.push(H1.pop()), H1.push(x);
}
int Get(){
	int ret = H2.pop();
	return H1.push(ret), ret;
}
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= m; ++i) b[i] = read();
	register int x = 1;
	H1.clear(cmp1), H2.clear(cmp2);
	for (register int i = 1; i <= n; ++i){
		Add(a[i]);
		while (b[x] == i) printf("%d\n", Get()), ++x;
	}
	getchar();
}