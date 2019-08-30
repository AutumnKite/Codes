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
#define For(i,a,b) for(int i=(int)(a);i<=(int)(b);i++)
#define DFor(i,a,b) for(int i=(int)(a);i>=(int)(b);i--)
#define cross(i,a) for(int i=hd[(a)];i;i=pr[i])
using namespace std;
inline LL Max(LL a,LL b){return a>b?a:b;}
inline LL Min(LL a,LL b){return a<b?a:b;}
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
#define N 5005
#define M 100005
int n,m;
int edge,to[M],pr[M],hd[N];
inline void addedge(int u,int v){
    to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
int vis[N],idx,dfn[N],low[N],top,sta[N],cnt,col[N],sum[N];
inline void tarjan(int u){
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
            sum[cnt]++;
            vis[sta[top--]]=0;
        }
    }
}
int main(){
//#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#else
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    n=read(),m=read();
    For(i,1,m){
        int x=read(),y=read(),t=read();
        addedge(x,y);if(t==2) addedge(y,x);
    }
    For(i,1,n) if(!dfn[i]) tarjan(i);
    int ans=0;
    For(i,1,n) if(!ans||sum[col[i]]>sum[ans]) ans=col[i];
    write(sum[ans]);putchar('\n');
    For(i,1,n) if(col[i]==ans) write(i),putchar(' ');
    return 0;
}