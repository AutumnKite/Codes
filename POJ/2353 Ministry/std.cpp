#include <cstdio>
#include <cctype>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
const int N=110,M=510;
struct node{
	int x,y;
}pre[N][M];
int n,m,pos,a[N][M];
long long ans,dp[N][M];
inline void print(int x,int y){
	if (pre[x][y].x) print(pre[x][y].x,pre[x][y].y);
	printf("%d\n",y);
}
int main(){
	n=read(),m=read();
	for (register int i=1;i<=n;++i)
		for (register int j=1;j<=m;++j)
			a[i][j]=read();
	for (register int i=1;i<=m;++i) dp[1][i]=a[1][i];
	for (register int i=2;i<=n;++i){
		for (register int j=1;j<=m;++j)
			dp[i][j]=dp[i-1][j]+a[i][j],pre[i][j]=(node){i-1,j};
		for (register int j=2;j<=m;++j)
			if (dp[i][j-1]+a[i][j]<dp[i][j]) dp[i][j]=dp[i][j-1]+a[i][j],pre[i][j]=(node){i,j-1};
		for (register int j=m-1;j;--j)
			if (dp[i][j+1]+a[i][j]<dp[i][j]) dp[i][j]=dp[i][j+1]+a[i][j],pre[i][j]=(node){i,j+1};
	}
	ans=1e18;
	for (register int i=1;i<=m;++i)
		if (dp[n][i]<ans) ans=dp[n][i],pos=i;
	print(n,pos);
}
