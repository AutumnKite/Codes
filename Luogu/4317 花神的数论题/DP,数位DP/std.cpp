#include <cstdio>
#define N 60
#define mo 10000007
long long n,dp[N][N][2];
int m,a[N],ans;
int qpow(int a,long long b){
	int s=1;
	for (;b;b&1?s=1ll*s*a%mo:0,b>>=1,a=1ll*a*a%mo) ;
	return s;
}
int main(){
	scanf("%lld",&n);
	for (;n;n>>=1) a[++m]=n&1;
	dp[m+1][0][1]=1;
	for (register int i=m;i;--i){
		dp[i][0][0]=1,dp[i][0][1]=0;
		for (register int j=1;j<=m;++j)
			dp[i][j][0]=dp[i+1][j-1][0]+dp[i+1][j][0]+(a[i]==1?dp[i+1][j][1]:0),
			dp[i][j][1]=(a[i]==1?dp[i+1][j-1][1]:dp[i+1][j][1]);
	}
	ans=1;
	for (register int i=1;i<=m;++i) ans=1ll*ans*qpow(i,dp[1][i][0]+dp[1][i][1])%mo;
	printf("%d",ans);
}
/*
1
1
2
1
2
2
*/
