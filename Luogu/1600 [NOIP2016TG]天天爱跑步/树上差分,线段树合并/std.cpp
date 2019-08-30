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
#define N 300005
#define M 300005
int n,m,w[N],s[M],t[M],LCA[M],dis[M];
int rt_a[N],rt_b[N],ans[N];
vector<int> pa[N];
int edge,to[N<<1],pr[N<<1],hd[N];
void addedge(int u,int v){
    to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
int size[N],dep[N],fa[N],son[N];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,size[u]=1;
    cross(i,u){
        int v=to[i];
        if(v==fa[u]) continue;
        fa[v]=u,dfs(v),size[u]+=size[v];
        if(!son[u]||size[v]>size[son[u]]) son[u]=v;
    }
}
int idc,top[N],idx[N],idt[N];
void dfs(int u,int tp){
    top[u]=tp,idx[u]=++idc,idt[idc]=u;
    if(!son[u]) return;
    dfs(son[u],tp);
    cross(i,u){
        int v=to[i];
        if(v==fa[u]||v==son[u]) continue;
        dfs(v,v);
    }
}
int lca(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u=fa[top[u]];
    }
    return dep[u]<dep[v]?u:v;
}
int cnt_a,cnt_b;
struct node{
    int lson,rson,sum;
}T_a[N<<5],T_b[N<<5];
#define mid (l+r>>1)
void insert_a(int &u,int l,int r,int q,int x){
    if(!u) u=++cnt_a;
    T_a[u].sum+=x;
    if(l==r) return;
    if(q<=mid) insert_a(T_a[u].lson,l,mid,q,x);
    else insert_a(T_a[u].rson,mid+1,r,q,x);
}
void insert_b(int &u,int l,int r,int q,int x){
    if(!u) u=++cnt_b;
    T_b[u].sum+=x;
    if(l==r) return;
    if(q<=mid) insert_b(T_b[u].lson,l,mid,q,x);
    else insert_b(T_b[u].rson,mid+1,r,q,x);
}
void merge_a(int &u1,int u2){
    if(!u2) return;
    if(!u1) {u1=u2;return;}
    merge_a(T_a[u1].lson,T_a[u2].lson);
    merge_a(T_a[u1].rson,T_a[u2].rson);
    T_a[u1].sum+=T_a[u2].sum;
}
void merge_b(int &u1,int u2){
    if(!u2) return;
    if(!u1) {u1=u2;return;}
    merge_b(T_b[u1].lson,T_b[u2].lson);
    merge_b(T_b[u1].rson,T_b[u2].rson);
    T_b[u1].sum+=T_b[u2].sum;
}
int query_a(int u,int l,int r,int q){
    if(l==r) return T_a[u].sum;
    if(q<=mid) return query_a(T_a[u].lson,l,mid,q);
    else return query_a(T_a[u].rson,mid+1,r,q);
}
int query_b(int u,int l,int r,int q){
    if(l==r) return T_b[u].sum;
    if(q<=mid) return query_b(T_b[u].lson,l,mid,q);
    else return query_b(T_b[u].rson,mid+1,r,q);
}
void count(int u){
    cross(i,u){
        int v=to[i];
        if(v==fa[u]) continue;
        count(v);
        merge_a(rt_a[u],rt_a[v]);
        merge_b(rt_b[u],rt_b[v]);
    }
    For(i,0,pa[u].size()-1) insert_b(rt_b[u],1,n+N,dis[pa[u][i]]-dep[t[pa[u][i]]]+N,-1);
    ans[u]=query_a(rt_a[u],1,n+N,w[u]+dep[u])+query_b(rt_b[u],1,n+N,w[u]-dep[u]+N);
    For(i,0,pa[u].size()-1) insert_a(rt_a[u],1,n+N,dep[s[pa[u][i]]],-1);
}
int main(){
//#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#else
    freopen("running.in","r",stdin);
    freopen("running.out","w",stdout);
#endif
    n=read(),m=read();
    For(i,1,n-1){
        int x=read(),y=read();
        addedge(x,y),addedge(y,x);
    }
    For(i,1,n) w[i]=read();
    fa[1]=0,dfs(1),dfs(1,1);
    For(i,1,m){
        s[i]=read(),t[i]=read();
        LCA[i]=lca(s[i],t[i]);
        dis[i]=dep[s[i]]+dep[t[i]]-(dep[LCA[i]]<<1);
        insert_a(rt_a[s[i]],1,n+N,dep[s[i]],1);
        insert_b(rt_b[t[i]],1,n+N,dis[i]-dep[t[i]]+N,1);
        pa[LCA[i]].push_back(i);
    }
    count(1);
    For(i,1,n) write(ans[i]),putchar(' ');
    return 0;
}