#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const int N=100005,M=320,mo=23333333;
int n,m,f[2][N],s[M],g[M][N],ans;
int main(){
	scanf("%d",&n),m=sqrt(n)+1;
	f[0][0]=g[0][0]=1;
	for (register int i=1;i<=m;++i){
		memset(s,0,sizeof s);
		for (register int j=0,k;j<=n;++j)
			k=j%i,(s[k]+=f[(i-1)&1][j])%=mo,f[i&1][j]=s[k],
			j>=i*i?s[k]=(s[k]-f[(i-1)&1][j-i*i]+mo)%mo:0;
	}
	for (register int i=1;i<=m;++i)
		for (register int j=0;j<=n;++j)
			(g[i][j]=(j>m?g[i-1][j-m-1]:0)+(j>=i&&i?g[i][j-i]:0))%=mo;
	for (register int i=0;i<=n;++i){
		register int sum=0;
		for (register int j=0;j<=m;++j) (sum+=g[j][n-i])%=mo;
		(ans+=1ll*f[m&1][i]*sum%mo)%=mo;
	}
	printf("%d",ans);
}
