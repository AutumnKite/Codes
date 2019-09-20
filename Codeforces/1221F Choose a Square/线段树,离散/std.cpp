#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 1000005
int n, m, pos[N];
struct node{
	int x, y, w;
}p[N];
std :: vector< std :: pair<int, int> > a[N], b[N];
struct Binary_Indexed_Tree{
	long long c[N];
	void add(int x, int y){
		for (; x <= m; x += x & -x) c[x] += y;
	}
	long long query(int x){
		long long s = 0;
		for (; x; x -= x & -x) s += c[x];
		return s;
	}
};
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i)
		pos[i] = p[i].x = read(), pos[i + n] = p[i].y = read(), p[i].w = read();
	std :: sort(pos + 1, pos + 1 + (n << 1));
	m = std :: unique(pos + 1, pos + 1 + (n << 1)) - pos - 1;
	for (register int i = 1; i <= n; ++i){
		p[i].x = std :: lower_bound(pos + 1, pos + 1 + m, p[i].x) - pos;
		p[i].y = std :: lower_bound(pos + 1, pos + 1 + m, p[i].y) - pos;
		a[p[i].x].push_back(std :: make_pair(p[i].y, p[i].w));
		b[p[i].y].push_back(std :: make_pair(p[i].x, p[i].w));
	}
	
}