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
#define N 100005
#define mid (l+r>>1)
#define writeln(a) write(a),putchar('\n')
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
int n,m,q,num[N],fa[N],root[N],cnt;
struct node{
    int ls,rs,d;
}tree[N<<5];
int find(int x){return fa[x]=fa[x]==x?x:find(fa[x]);}
void make(int &u,int l,int r,int x){
    if(!u) u=++cnt;
    tree[u].d++;
    if(l==r) return;
    if(x<=mid) make(tree[u].ls,l,mid,x);
    else make(tree[u].rs,mid+1,r,x);
}
void merge(int &u1,int u2){
    if(!u1) {u1=u2;return;}
    if(!u2) return;
    merge(tree[u1].ls,tree[u2].ls);
    merge(tree[u1].rs,tree[u2].rs);
    tree[u1].d+=tree[u2].d;
}
void add(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx==fy) return;
    merge(root[fx],root[fy]);
    fa[fy]=fx;
}
int query(int u,int l,int r,int k){
    if(l==r) return num[l];
    int lsum=tree[tree[u].ls].d;
    if(k<=lsum) return query(tree[u].ls,l,mid,k);
    else return query(tree[u].rs,mid+1,r,k-lsum);
}
int main(){
    n=read(),m=read();
    For(i,1,n){
        int x=read();
        num[x]=fa[i]=i;
        make(root[i],1,n,x);
    }
    For(i,1,m){
        int x=read(),y=read();
        add(x,y);
    }
    q=read();
    For(i,1,q){
        char s[20];scanf("%s",s);
        int x=read(),y=read();
        if(s[0]=='B') add(x,y);
        else{
            if(y>tree[root[find(x)]].d) writeln(-1);
            else writeln(query(root[find(x)],1,n,y));
        }
    }
    return 0;
}