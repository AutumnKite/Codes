#include <cstdio>
#include <cmath>
#include <algorithm>
struct point{
	int x, y;
	point(int _x = 0, int _y = 0){ x = _x, y = _y; }
	void read(){ scanf("%d%d", &x, &y); }
	point operator + (const point &rhs) const { return point(x + rhs.x, y + rhs.y); }
	point operator - (const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
}A, B, C, D;
int q;
int dot_product(point a, point b){
	return a.x * b.x + a.y * b.y;
}
int cross_product(point a, point b){
	return a.x * b.y - a.y * b.x;
}
bool intersection(point a, point b, point c, point d){
	if (std :: min(a.x, b.x) > std :: max(c.x, d.x)) return 0;
	if (std :: min(c.x, d.x) > std :: max(a.x, b.x)) return 0;
	if (std :: min(a.y, b.y) > std :: max(c.y, d.y)) return 0;
	if (std :: min(c.y, d.y) > std :: max(a.y, b.y)) return 0;
	int p1 = cross_product(b - a, c - a), p2 = cross_product(b - a, d - a);
	if (1ll * p1 * p2 > 0) return 0;
	p1 = cross_product(d - c, a - c), p2 = cross_product(d - c, b - c);
	if (1ll * p1 * p2 > 0) return 0;
	return 1;
}
int main(){
	scanf("%d", &q);
	for (register int i = 1; i <= q; ++i){
		A.read(), B.read(), C.read(), D.read();
		if (intersection(A, B, C, D)) printf("1\n");
		else printf("0\n");
	}
}
