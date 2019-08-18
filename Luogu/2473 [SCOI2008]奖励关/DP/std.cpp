#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
#define N 105
#define M 16
int n,m,p[M],pre[M];
double dp[N][1<<M];
int main(){
	n=read(),m=read();
	for (register int i=1;i<=m;++i){
		p[i]=read();
		int t=0,x=0;
		while ((x=read())!=0) t|=1<<(x-1);
		pre[i]=t;
	}
	for (register int i=n;i;--i)
		for (register int j=0;j<(1<<m);++j){
			for (register int k=1;k<=m;++k)
				if ((pre[k]&j)==pre[k]) dp[i][j]+=max(dp[i+1][j|(1<<(k-1))]+p[k],dp[i+1][j]);
				else dp[i][j]+=dp[i+1][j];
			dp[i][j]/=m;
		}
	printf("%.6lf",dp[1][0]);
}
