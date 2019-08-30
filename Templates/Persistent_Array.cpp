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
#define N 1000005
int n,m,val[N],rt[N],cnt;
struct Tree{
    int ls,rs,d;
}T[N*20];
#define mid (l+r>>1)
inline void build(int &u,int l,int r){
    u=++cnt;
    if(l==r) {T[u].d=val[l];return;}
    build(T[u].ls,l,mid),build(T[u].rs,mid+1,r);
}
inline void ins(int &u,int tu,int l,int r,int q,int x){
    T[u=++cnt]=T[tu];
    if(l==r) {T[u].d=x;return;}
    if(q<=mid) ins(T[u].ls,T[tu].ls,l,mid,q,x);
    else ins(T[u].rs,T[tu].rs,mid+1,r,q,x);
}
inline int query(int u,int l,int r,int q){
    if(l==r) return T[u].d;
    if(q<=mid) return query(T[u].ls,l,mid,q);
    else return query(T[u].rs,mid+1,r,q);
}
int main(){
//#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#else
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    n=read(),m=read();
    For(i,1,n) val[i]=read();
    build(rt[0],1,n);
    For(i,1,m){
        int v=read(),k=read(),q=read();
        if(k==1){
            int x=read();
            ins(rt[i],rt[v],1,n,q,x);
        }
        else{
            write(query(rt[v],1,n,q));
            putchar('\n');
            rt[i]=rt[v];
        }
    }
    return 0;
}

