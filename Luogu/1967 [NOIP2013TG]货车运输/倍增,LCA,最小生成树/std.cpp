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
#define N 10005
#define M 50005
#define INF 1000000000
int n,m;
struct node{
    int x,y,z;
    bool operator < (const node&b)const{
        return z>b.z;
    }
}a[M];
int edge,hd[N],to[N<<1],tw[N<<1],pr[N<<1];
inline void addedge(int u,int v,int w){
    to[++edge]=v,tw[edge]=w,pr[edge]=hd[u],hd[u]=edge;
}
int fa[N];
inline int find(int u){return fa[u]==u?u:fa[u]=find(fa[u]);}
inline void merge(int u,int v,int w){
    int fu=find(u),fv=find(v);
    if(fu==fv) return;
    fa[fv]=fu,addedge(u,v,w),addedge(v,u,w);
}
inline void kruskal(){
    sort(a+1,a+1+m);
    For(i,1,n) fa[i]=i;
    For(i,1,m) merge(a[i].x,a[i].y,a[i].z);
}
int vis[N],dep[N],f[N][25][2];
inline void dfs(int u,int fa){
    vis[u]=1,dep[u]=dep[fa]+1;
    cross(i,u){
        int v=to[i],w=tw[i];
        if(v==fa) continue;
        f[v][0][0]=u,f[v][0][1]=w,dfs(v,u);
    }
}
inline void work(){
    For(j,1,20) For(i,1,n){
        f[i][j][0]=f[f[i][j-1][0]][j-1][0];
        f[i][j][1]=Min(f[i][j-1][1],f[f[i][j-1][0]][j-1][1]);
    }
}
inline int lca(int u,int v){
    if(find(u)!=find(v)) return -1;
    int ans=INF;
    if(dep[u]>dep[v]) swap(u,v);
    int d=dep[v]-dep[u];
    for(int i=0;d;i++,d>>=1) if(d&1) ans=Min(ans,f[v][i][1]),v=f[v][i][0];
    if(u==v) return ans;
    DFor(i,20,0) if(f[u][i][0]!=f[v][i][0]){
        ans=Min(ans,Min(f[u][i][1],f[v][i][1]));
        u=f[u][i][0],v=f[v][i][0];
    }
    return Min(ans,Min(f[u][0][1],f[v][0][1]));
}
int main(){
//#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#else
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    n=read(),m=read();
    For(i,1,m) a[i].x=read(),a[i].y=read(),a[i].z=read();
    kruskal();
    For(i,1,n) if(!vis[i]) f[i][0][0]=i,f[i][0][1]=INF,dfs(i,0);
    work();
    for(int q=read();q--;putchar('\n')){
        int x=read(),y=read();
        write(lca(x,y));
    }
    return 0;
}
