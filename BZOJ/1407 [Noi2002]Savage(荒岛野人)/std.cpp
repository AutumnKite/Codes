#include <cstdio>
#include <algorithm>
const int N=20;
int n,mx,c[N],p[N],L[N];
int exgcd(int a,int b,int &x,int &y){
	if (!b) return x=1,y=0,a;
	int x0,y0,g=exgcd(b,a%b,x0,y0);
	return x=y0,y=x0-a/b*y0,g;
}
int abs(int a){return a>0?a:-a;}
int check(int m){
	for (register int i=1;i<=n;++i)
		for (register int j=i+1;j<=n;++j){
			int A,C;
			if (p[i]>p[j]) A=p[i]-p[j],C=c[j]-c[i];
			else A=p[j]-p[i],C=c[i]-c[j];
			int x,y,g=exgcd(A,m,x,y);
			if (C%g) continue; else x*=C/g;
			g=m/g,x=(x%g+g)%g;
			if (x>std::min(L[i],L[j])) continue;
			return 0;
		}
	return 1;
}
int main(){
	scanf("%d",&n);
	for (register int i=1;i<=n;++i) scanf("%d%d%d",c+i,p+i,L+i),mx=std::max(mx,c[i]);
	for (register int M=mx;M<=1000000;++M) if (check(M)) return printf("%d",M),0; 
}
