#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
const int N=100005;
int n,m,a[N],edge,to[N<<1],pr[N<<1],hd[N],d[N],dp[N][3];
void addedge(int u,int v){
	to[++edge]=v,pr[edge]=hd[u],hd[u]=edge,++d[u];
}
void DP(int u,int fa){
	for (register int i=hd[u],v;i;i=pr[i]) if ((v=to[i])!=fa) DP(v,u);
	if (d[u]==1) dp[u][0]=dp[u][1]=1,dp[u][2]=0;
	else if (a[u]){
		for (register int i=hd[u],v;i;i=pr[i]) if ((v=to[i])!=fa) dp[u][1]+=min(dp[v][0],dp[v][1]);
		dp[u][0]=dp[u][2]=10000000;
	}
	else{
		int s=1,s0=0,s1=0,s2=0;
		for (register int i=hd[u],v;i;i=pr[i])
			if ((v=to[i])!=fa)
				s+=min(dp[v][0],min(dp[v][1],dp[v][2])),s0+=dp[v][0],
				s1+=min(dp[v][0],dp[v][1]),s2+=min(dp[v][0],dp[v][2]);
		dp[u][0]=min(s,s0),dp[u][1]=min(s,s1),dp[u][2]=min(s,s2);
	}
}
int main(){
	n=read()+1,m=read();
	for (register int i=1;i<n;++i){
		int u=read()+1,v=read()+1;
		addedge(u,v),addedge(v,u);
	}
	for (register int i=1;i<=m;++i){
		int u=read()+1;
		if (d[u]==1) return printf("-1"),0;
		a[u]=1;
	}
	for (register int i=1;i<=n;++i)
		if (d[i]>1) return DP(i,-1),printf("%d",min(dp[i][0],min(dp[i][1],dp[i][2]))),0;
}
