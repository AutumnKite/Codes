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
const int N=400005,M=2000005;
int n,m,Q,s,a[N],x[M],y[M];
int edge,hd[N],pr[M],to[M];
int idx,dfn[N],low[N],vis[N],top,sta[N],cnt,col[N],mx[N],cmx[N];
int in[N],h,t,q[N],id[N],dp[N],dpc[N];
void addedge(int u,int v){
    to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
void tarjan(int u){
    vis[sta[++top]=u]=1,dfn[u]=low[u]=++idx;
    for (register int i=hd[u],v;i;i=pr[i])
        if (!dfn[v=to[i]]) tarjan(v),low[u]=min(low[u],low[v]);
        else if (vis[v]) low[u]=min(low[u],dfn[v]);
    if (dfn[u]==low[u]){
        for (++cnt,mx[cnt]=cmx[cnt]=0;sta[top+1]!=u;--top){
            col[sta[top]]=cnt;
            a[sta[top]]>mx[cnt]?(cmx[cnt]=mx[cnt],mx[cnt]=a[sta[top]])
			:(a[sta[top]]>cmx[cnt]&&a[sta[top]]<mx[cnt]?cmx[cnt]=a[sta[top]]:0);
            vis[sta[top]]=0;
        }
    }
}
void init(){
	n=read(),m=read(),Q=read(),s=read();
	for (register int i=1;i<=n;++i) a[i]=read();
	for (register int i=1;i<=m;++i) x[i]=read(),y[i]=read(),addedge(x[i],y[i]);
	for (register int i=1;i<=n;++i) if (!dfn[i]) tarjan(i);
	memset(hd,0,sizeof hd),memset(pr,0,sizeof pr),n=cnt,edge=0;
	for (register int i=1;i<=m;++i)
		if (col[x[i]]!=col[y[i]]) addedge(col[x[i]],col[y[i]]),++in[col[y[i]]];
}
void bfs(){
	memset(vis,0,sizeof vis);
	h=0,t=1,q[t]=col[s],vis[col[s]]=1;
	while (h<t) for (register int i=hd[q[++h]],v;i;i=pr[i]) if (!vis[v=to[i]]) q[++t]=v,vis[v]=1;
	for (register int i=1;i<=n;++i)
		if (!vis[i]) for (register int j=hd[i];j;j=pr[j]) --in[to[j]];
		else dp[i]=mx[i],dpc[i]=cmx[i];
}
void toposort(){
	h=0,t=1,q[t]=col[s];
	while (h<t) for (register int i=hd[q[++h]],v;i;i=pr[i]) if (!(--in[v=to[i]])&&v!=col[s]) q[++t]=v;
}
void DP(){
	bfs(),toposort();
	for (register int i=1;i<=t;++i){
		int u=q[i];
		for (register int j=hd[u],v;j;j=pr[j]){
			v=to[j];
			cmx[v]=max(cmx[v],cmx[u]);
			if (mx[v]==dp[u]) cmx[v]=max(cmx[v],dpc[u]);
			else cmx[v]=max(cmx[v],min(mx[v],dp[u]));
			if (dp[u]>dp[v]) dpc[v]=dp[v],dp[v]=dp[u];
			else if (dp[u]<dp[v]&&dp[u]>dpc[v]) dpc[v]=dp[u];
			if (dpc[u]>dp[v]) dpc[v]=dp[v],dp[v]=dpc[u];
		}
	}
}
int main(){
	init(),DP();
	while (Q--){
		int x=read();
		if (!vis[col[x]]) printf("-1 ");
		else printf("%d ",cmx[col[x]]);
	}
}
