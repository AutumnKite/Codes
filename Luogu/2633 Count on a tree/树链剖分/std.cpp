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
#define N 100005
int n,m,num[N];
struct node{
    int id,val;
    bool operator < (const node&x)const{
        return val<x.val;
    }
}data[N];
int edge,to[N<<1],pr[N<<1],hd[N];
void addedge(int u,int v){
    to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
struct tree{
    int lson,rson,sum;
}T[N<<6];
int cnt,root[N];
#define mid (l+r>>1)
void insert(int &u,int tu,int l,int r,int x){
    T[u=++cnt]=T[tu],T[u].sum++;
    if(l==r) return;
    if(x<=mid) insert(T[u].lson,T[tu].lson,l,mid,x);
    else insert(T[u].rson,T[tu].rson,mid+1,r,x);
}
int size[N],son[N],dep[N],fa[N];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,size[u]=1;
    insert(root[u],root[fa[u]],1,n,num[u]);
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
int query(int L,int R,int LCA,int FA,int l,int r,int k){
    if(l==r) return l;
    int s=T[T[L].lson].sum+T[T[R].lson].sum-T[T[LCA].lson].sum-T[T[FA].lson].sum;
    if(k<=s) return query(T[L].lson,T[R].lson,T[LCA].lson,T[FA].lson,l,mid,k);
    else return query(T[L].rson,T[R].rson,T[LCA].rson,T[FA].rson,mid+1,r,k-s);
}
int main(){
//#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#else
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    n=read(),m=read();
    For(i,1,n) data[i]=(node){i,read()};
    sort(data+1,data+1+n);
    For(i,1,n) num[data[i].id]=i;
    For(i,1,n-1){
        int x=read(),y=read();
        addedge(x,y),addedge(y,x);
    }
    fa[1]=0,dfs(1),dfs(1,1);
    int ans=0;
    For(i,1,m){
        int x=read()^ans,y=read(),LCA=lca(x,y),k=read();
        ans=data[query(root[x],root[y],root[LCA],root[fa[LCA]],1,n,k)].val;
        write(ans),putchar('\n');
    }
    return 0;
}
