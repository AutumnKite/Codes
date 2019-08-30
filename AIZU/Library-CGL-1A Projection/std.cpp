#include <cstdio>
#include <cmath>
struct point{
	double x, y;
	point(double _x = 0, double _y = 0){
		x = _x, y = _y;
	}
	point operator + (const point &rhs) const { return point(x + rhs.x, y + rhs.y); }
	point operator - (const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
}A, B, C, D;
int q;
double dot_product(point a, point b){
	return a.x * b.x + a.y * b.y;
}
point projection(point p, point a, point b){
	double l1 = dot_product(p - a, b - a);
	double l2 = dot_product(b - a, b - a);
	double d = l1 / l2;
	return point(a.x + (b.x - a.x) * d, a.y + (b.y - a.y) * d);
}
int main(){
	scanf("%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y);
	scanf("%d", &q);
	for (register int i = 1; i <= q; ++i){
		scanf("%lf%lf", &C.x, &C.y);
		D = projection(C, A, B);
		printf("%.10lf %.10lf\n", D.x, D.y);
	}
}
