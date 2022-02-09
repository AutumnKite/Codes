#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI=acos(-1.0);
struct Point{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y){}
	friend Point operator + (const Point &a,const Point &b){
		return Point(a.x+b.x,a.y+b.y);
	}
	friend Point operator - (const Point &a,const Point &b){
		return Point(a.x-b.x,a.y-b.y);
	}
	friend double operator % (const Point &a,const Point &b){
		return a.x*b.y-a.y*b.x;
	}
	friend bool operator < (const Point &a,const Point &b){
		return a.x==b.x?a.y<b.y:a.x<b.x;
	}
	inline bool Quad(){
		return y>0||(y==0&&x>=0);
	}
	inline double len(){
		return sqrt(x*x+y*y);
	}
};
inline bool Para(Point a,Point b){
	return a%b==0;
}
inline bool Left(Point a,Point b){
	return b%a>0;
}
typedef vector<Point> poly;
poly Convex(poly a){
	poly st;
	Point LTL=(*min_element(a.begin(),a.end()));
	sort(a.begin(),a.end(),[&](Point a,Point b){
		a=a-LTL,b=b-LTL;
		return Para(a,b)?a.len()<b.len():Left(a,b);
	});
	for(int i=0;i<a.size();++i){
		while(st.size()>1&&!Left(st.back()-st[st.size()-2],a[i]-st[st.size()-2]))st.pop_back();
		st.push_back(a[i]);
	}
	return st;
}
struct Cir{
	int x,y,r;
	void init(){
		cin>>x>>y>>r;
	}
	void Get(poly &A){
		for(int i=0;i<36000;++i){
			A.push_back(Point(x+cos(i/18000.0*PI)*r,y+sin(i/18000.0*PI)*r));
		}
	}
}A,B,C;
void Solve(){
	A.init(),B.init(),C.init();
	poly P;
	A.Get(P),B.Get(P),C.Get(P);
	P=Convex(P);
	double ans=0;
	for(int i=0;i<(int)P.size();++i){
		ans+=P[(i+1)%P.size()]%P[i];
	}
	cout<<ans/2<<'\n';
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.setf(ios::fixed);
	cout.precision(10);
	int T;
	cin>>T;
	while(T--){
		Solve();
	}
	return 0;
}