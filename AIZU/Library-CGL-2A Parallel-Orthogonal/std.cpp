#include <cstdio>
#include <cmath>
struct point{
	double x, y;
	point(double _x = 0, double _y = 0){ x = _x, y = _y; }
	void read(){ scanf("%lf%lf", &x, &y); }
	void print(char ch = '\n'){ printf("%.10lf %.10lf", x, y), putchar(ch); }
	point operator + (const point &rhs) const { return point(x + rhs.x, y + rhs.y); }
	point operator - (const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
}A, B, C, D;
int q;
double dot_product(point a, point b){
	return a.x * b.x + a.y * b.y;
}
double cross_product(point a, point b){
	return a.x * b.y - a.y * b.x;
}
bool parallel(point p1, point p2, point p3, point p4){
	return cross_product(p1 - p2, p3 - p4) == 0;
}
bool orthogonal(point p1, point p2, point p3, point p4){
	return dot_product(p1 - p2, p3 - p4) == 0;
}
int main(){
	scanf("%d", &q);
	for (register int i = 1; i <= q; ++i){
		A.read(), B.read(), C.read(), D.read();
		if (parallel(A, B, C, D)) printf("2\n");
		else if (orthogonal(A, B, C, D)) printf("1\n");
		else printf("0\n");
	}
}
