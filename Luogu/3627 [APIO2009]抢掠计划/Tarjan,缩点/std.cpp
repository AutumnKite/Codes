#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#define LL long long
#define For(i,a,b) for(int i=a;i<=b;i++)
#define DFor(i,a,b) for(int i=a;i>=b;i--)
#define cross(i,a) for(int i=hd[a];i;i=pr[i])
#define Min(a,b) a<b?a:b
#define Max(a,b) a>b?a:b
#define N 500005
#define M 500005
using namespace std;
inline LL read(){
    LL x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-') f=-1,ch=getchar();
    while (isdigit(ch)) x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return x*f;
}
inline void write(LL x){
    if (x<0) putchar('-'),x=-x;
    if (x>=10) write(x/10),putchar(x%10+'0');
    else putchar(x+'0');
}
int n,m,s,p,val[N],x[M],y[M],b[N];
int edge,hd[N],to[M],pr[M];
int top,sta[N],idx,dfn[N],low[N],vis[N],cnt,col[N],sum[N];
int h,t,que[N],dis[N];
void addedge(int u,int v){
    to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
void tarjan(int u){
    vis[sta[++top]=u]=1,dfn[u]=low[u]=++idx;
    cross(i,u){
        int v=to[i];
        if(!dfn[v]) tarjan(v),low[u]=Min(low[u],low[v]);
        else if(vis[v]) low[u]=Min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        sum[++cnt]=0;
        while(sta[top+1]!=u){
            col[sta[top]]=cnt;
            sum[cnt]+=val[sta[top]];
            vis[sta[top--]]=0;
        }
    }
}
void SPFA(int u){
    memset(vis,0,sizeof vis);
    memset(dis,-1,sizeof dis);
    h=0,vis[que[t=1]=u]=1,dis[u]=sum[u];
    while(h<t){
        int u=que[++h];vis[u]=0;
        cross(i,u){
            int v=to[i];
            if(dis[u]+sum[v]<=dis[v]) continue;
            dis[v]=dis[u]+sum[v];
            if(vis[v]) continue;
            vis[que[++t]=v]=1;
        }
    }
}
int main(){
    n=read(),m=read();
    For(i,1,m) x[i]=read(),y[i]=read(),addedge(x[i],y[i]);
    For(i,1,n) val[i]=read();
    For(i,1,n) if(!dfn[i]) tarjan(i);
    memset(hd,0,sizeof hd);
    memset(pr,0,sizeof pr);
    memset(to,0,sizeof to);
    edge=0;
    For(i,1,m) if(col[x[i]]!=col[y[i]]) addedge(col[x[i]],col[y[i]]);
    s=col[read()],p=read();
    For(i,1,p) b[col[read()]]=1;
    SPFA(s);
    int ans=0;
    For(i,1,cnt) if(b[i]) ans=Max(ans,dis[i]);
    write(ans);
    return 0;
}
