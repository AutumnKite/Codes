#include <cstdio>
#include <cmath>
struct point{
	double x, y;
	point(double _x = 0, double _y = 0){ x = _x, y = _y; }
	void read(){ scanf("%lf%lf", &x, &y); }
	void print(char ch = '\n'){ printf("%.10lf %.10lf", x, y), putchar(ch); }
	point operator + (const point &rhs) const { return point(x + rhs.x, y + rhs.y); }
	point operator - (const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
}A, B, C, D, E;
int q;
point cross_point(point a, point b, point c, point d){
	double k1, b1, k2, b2, x, y;
	if (a.x == b.x){
		k2 = (c.y - d.y) / (c.x - d.x), b2 = c.y - k2 * c.x;
		x = a.x, y = k2 * x + b2;
	}
	else if (c.x == d.x){
		k1 = (a.y - b.y) / (a.x - b.x), b1 = a.y - k1 * a.x;
		x = c.x, y = k1 * x + b1;
	}
	else{
		k1 = (a.y - b.y) / (a.x - b.x), b1 = a.y - k1 * a.x;
		k2 = (c.y - d.y) / (c.x - d.x), b2 = c.y - k2 * c.x;
		x = (b2 - b1) / (k1 - k2), y = k1 * x + b1;
	}
	return point(x, y);
}
int main(){
	scanf("%d", &q);
	for (register int i = 1; i <= q; ++i){
		A.read(), B.read(), C.read(), D.read();
		E = cross_point(A, B, C, D);
		E.print();
	}
}
