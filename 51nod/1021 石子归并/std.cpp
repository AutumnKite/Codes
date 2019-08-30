#include <cstdio>
#include <cstring>
using namespace std;
const int N=105;
int n,a[N],pre[N],dp[N][N];
int min(int a,int b){return a<b?a:b;}
int main(){
	scanf("%d",&n);
	for (register int i=1;i<=n;++i)
		for (register int j=1;j<=n;++j)
			dp[i][j]=1000000000;
	for (register int i=1;i<=n;++i) scanf("%d",a+i),dp[i][i]=0,pre[i]=pre[i-1]+a[i];
	for (register int i=2;i<=n;++i)
		for (register int j=1;j<=n-i+1;++j)
			for (register int k=j;k<j+i-1;++k)
				dp[j][j+i-1]=min(dp[j][j+i-1],dp[j][k]+dp[k+1][j+i-1]+pre[j+i-1]-pre[j-1]);
	printf("%d",dp[1][n]);
}
