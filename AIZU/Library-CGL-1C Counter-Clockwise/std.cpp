#include <cstdio>
#include <cmath>
struct point{
	double x, y;
	point(double _x = 0, double _y = 0){ x = _x, y = _y; }
	void read(){ scanf("%lf%lf", &x, &y); }
	void print(char ch = '\n'){ printf("%.10lf %.10lf", x, y), putchar(ch); }
	point operator + (const point &rhs) const { return point(x + rhs.x, y + rhs.y); }
	point operator - (const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
}A, B, C;
int q;
double dot_product(point a, point b){
	return a.x * b.x + a.y * b.y;
}
double cross_product(point a, point b){
	return a.x * b.y - a.y * b.x;
}
int main(){
	A.read(), B.read();
	scanf("%d", &q);
	for (register int i = 1; i <= q; ++i){
		C.read();
		if (cross_product(B - A, C - A) > 0) puts("COUNTER_CLOCKWISE");
		else if (cross_product(B - A, C - A) < 0) puts("CLOCKWISE");
		else if (dot_product(B - A, C - A) < 0) puts("ONLINE_BACK");
		else if (dot_product(B - A, B - A) < dot_product(C - A, C - A)) puts("ONLINE_FRONT");
		else puts("ON_SEGMENT");
	}
}
