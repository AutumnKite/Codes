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
const int N=2005;
int n,k,edge,to[N<<1],pr[N<<1],tw[N<<1],hd[N],sz[N],w[N];
long long dp[N][N];
void addedge(int u,int v,int w){
	to[++edge]=v,tw[edge]=w,pr[edge]=hd[u],hd[u]=edge;
}
void DP(int u,int fa){
	sz[u]=1;
	for (register int e=hd[u],v;e;e=pr[e])
		if ((v=to[e])!=fa){
			w[v]=tw[e],DP(v,u);
			for (register int i=min(sz[u],k);i>=0;--i)
				for (register int j=min(sz[v],k-i);j>=0;--j)
					dp[u][i+j]=max(dp[u][i+j],dp[u][i]+dp[v][j]);
			sz[u]+=sz[v];
		}
	for (register int i=k+sz[u]-n;i<=k&&i<=sz[u];++i)
		dp[u][i]+=(1ll*i*(k-i)+1ll*(sz[u]-i)*(n-k-sz[u]+i))*w[u];
}
int main(){
	n=read(),k=read();
	for (register int i=1;i<n;++i){
		int u=read(),v=read(),w=read();
		addedge(u,v,w),addedge(v,u,w);
	}
	if (2*k>n) k=n-k;
	w[1]=0,DP(1,0);
	printf("%lld",dp[1][k]);
}
