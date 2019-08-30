#include <cstdio>
#include <algorithm>
long long x,y,m,n,L;
long long exgcd(long long a,long long b,long long &x,long long &y){
	if (!b) return x=1,y=0,a;
	long long x0,y0,g=exgcd(b,a%b,x0,y0);
	return x=y0,y=x0-a/b*y0,g;
}
int main(){
	scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&L);
	if (m==n) return printf("Impossible"),0;
	if (m<n) std::swap(n,m),std::swap(x,y);
	long long X,Y,g=exgcd(m-n,L,X,Y);
	if ((y-x)%g) return printf("Impossible"),0;
	else X*=(y-x)/g;
	g=L/g,X=(X%g+g)%g;
	printf("%lld",X);
}
/*
x+am=y+an (mod p)
(m-n)a=y-x (mod p)
(m-n)a+pb=y-x
*/
