#include <cstdio>
#include <cctype>
#include <algorithm>
const int N=10005,M=1005;
int n,m,h,t,q[N];
long long dp[N],dp1[N],a[N];
inline int read(){
	int x=0,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar());
	for (;isdigit(ch);ch=getchar()) x=((x+(x<<2))<<1)+(ch^'0');
	return x;
}
inline long long X(int i,int j){
	return a[i+1]-a[j+1];
}
inline long long Y(int i,int j){
	return dp1[i]+a[i+1]*a[i+1]-dp1[j]-a[j+1]*a[j+1];
}
inline long long Val(int i,int j){
	return dp1[j]+(a[i]-a[j+1])*(a[i]-a[j+1]);
}
int main(){
	n=read(),m=read();
	for (register int i=1;i<=n;++i) a[i]=read();
	std::sort(a+1,a+1+n);
	for (register int i=1;i<=n;++i) dp1[i]=(a[i]-a[1])*(a[i]-a[1]);
	for (register int j=2;j<=m;++j){
		h=1,t=1,q[t]=j-1;
		for (register int i=1;i<=n;++i) dp[i]=1000000000000000000ll;
		for (register int i=j;i<=n;++i){
			while (h<t&&Y(q[h+1],q[h])<2*a[i]*X(q[h+1],q[h])) ++h;
			dp[i]=Val(i,q[h]);
			while (h<t&&Y(i,q[t])*X(q[t],q[t-1])<=Y(q[t],q[t-1])*X(i,q[t])) --t;
			q[++t]=i;
		}
		for (register int i=1;i<=n;++i) dp1[i]=dp[i];
	}
	return printf("%lld",dp1[n]),0;
}
