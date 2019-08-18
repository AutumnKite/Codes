#include <cstdio>
#include <vector>
#include <cctype>
using namespace std;
inline int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^'0');
	return x*f;
}
const int N=100005,M=10005;
int n,a[N];
long long dp[N],c[M];
struct point{
	long long x,y;
};
vector<point> s[M]; //s-stack
inline long long sqr(long long x){return x*x;}
inline int find(int p,int l,int r,long long x){
	register int m,ans=r--;
	while (l<=r){
		m=(l+r)>>1;
		if (s[p][m+1].y-s[p][m].y>x*(s[p][m+1].x-s[p][m].x)) l=m+1;
		else ans=m,r=m-1;
	}
	return ans;
}
inline long long val(int p,int i,int j){
	return -2*p*c[p]*s[p][j].x+s[p][j].y+p*sqr(c[p])+2*p*c[p];
}
int main(){
	n=read();
	for (register int i=1;i<=n;++i) a[i]=read();
	dp[0]=0;
	for (register int i=1;i<=n;++i){
		register int p=a[i],tp=s[p].size()-1;
		++c[p];
		register long long x=c[p],y=dp[i-1]+p*sqr(c[p]-1);
		while (tp>0&&(y-s[p][tp].y)*(s[p][tp].x-s[p][tp-1].x)>=(s[p][tp].y-s[p][tp-1].y)*(x-s[p][tp].x)) --tp,s[p].pop_back();
		s[p].push_back((point){x,y});
		dp[i]=val(p,i,find(p,0,s[p].size()-1,2*p*c[p]));
	}
	return printf("%lld",dp[n]),0;
}
