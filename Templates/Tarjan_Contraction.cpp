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
#define N 100105
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
int n,m,cnt,val[N],x[N],y[N],hd[N],pr[N],to[N],ans,f[N];
int idx,dfn[N],low[N],vis[N],top,sta[N],col[N],sum[N];
void add(int u,int v){
    to[++cnt]=v,pr[cnt]=hd[u],hd[u]=cnt;
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
int dp(int u){
    if(f[u]) return f[u];
    f[u]=sum[u];
    int ans=0;
    cross(i,u) ans=Max(ans,dp(to[i]));
    return f[u]+=ans;
}
int main(){
    n=read(),m=read();
    For(i,1,n) val[i]=read();
    For(i,1,m) add(x[i]=read(),y[i]=read());
    cnt=0;
    For(i,1,n) if(!dfn[i]) tarjan(i);
    memset(hd,0,sizeof hd);
    memset(pr,0,sizeof pr);
    memset(to,0,sizeof to);
    n=cnt,cnt=0;
    For(i,1,m) if(col[x[i]]!=col[y[i]]) add(col[x[i]],col[y[i]]);
    For(i,1,n) if(!f[i]) dp(i),ans=max(ans,f[i]);
    write(ans);
    return 0;
}
