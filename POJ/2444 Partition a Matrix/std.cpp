#include <cstdio>
using namespace std;
int n,m,a[505][505];
long long s[505][505],ans;
long long min(long long a,long long b){return a<b?a:b;}
long long abs(long long a){return a>0?a:-a;}
long long calc(long long a,long long b,long long c){return abs(a-b)+abs(a-c)+abs(b-c);}
int main(){
	while (1){
		scanf("%d%d",&n,&m);
		if (n==0) return 0;
		ans=1000000000000000000ll;
		for (register int i=1;i<=n;++i)
			for (register int j=1;j<=m;++j){
				scanf("%d",&a[i][j]);
				s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
			}
		for (register int i=1;i<n;++i)
			for (register int j=i+1;j<=n;++j)
				ans=min(ans,calc(s[i][m],s[j][m]-s[i][m],s[n][m]-s[j][m]));
		for (register int i=1;i<m;++i)
			for (register int j=i+1;j<=m;++j)
				ans=min(ans,calc(s[n][i],s[n][j]-s[n][i],s[n][m]-s[n][j]));
		for (register int i=1;i<=n;++i)
			for (register int j=1;j<=m;++j)
				ans=min(ans,calc(s[i][j],s[n][j]-s[i][j],s[n][m]-s[n][j])),
				ans=min(ans,calc(s[n][j],s[i][m]-s[i][j],s[n][m]-s[n][j]-s[i][m]+s[i][j])),
				ans=min(ans,calc(s[i][j],s[i][m]-s[i][j],s[n][m]-s[i][m])),
				ans=min(ans,calc(s[i][m],s[n][j]-s[i][j],s[n][m]-s[n][j]-s[i][m]+s[i][j]));
		printf("%lld\n",ans);
	}
}
