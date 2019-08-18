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
int n,m;
struct node{
    int d,dl,dr,mk;
}tree[N<<2];
#define mid (l+r>>1)
#define len (r-l+1)
#define lson u<<1,l,mid
#define rson u<<1|1,mid+1,r
void build(int u,int l,int r){
    tree[u].dl=tree[u].dr=tree[u].d=len;
    tree[u].mk=-1;
    if(l==r) return;
    build(lson),build(rson);
}
void update(int u,int l,int r){
    if(tree[u<<1].d<mid-l+1) tree[u].dl=tree[u<<1].dl;
    else tree[u].dl=tree[u<<1].d+tree[u<<1|1].dl;
    if(tree[u<<1|1].d<r-mid) tree[u].dr=tree[u<<1|1].dr;
    else tree[u].dr=tree[u<<1|1].d+tree[u<<1].dr;
    tree[u].d=max(max(tree[u<<1].d,tree[u<<1|1].d),tree[u<<1].dr+tree[u<<1|1].dl);
}
void pushdown(int u,int l,int r){
    if(tree[u].mk==0){
        tree[u<<1].d=tree[u<<1].dl=tree[u<<1].dr=mid-l+1;
        tree[u<<1|1].d=tree[u<<1|1].dl=tree[u<<1|1].dr=r-mid;
        tree[u<<1].mk=tree[u<<1|1].mk=0;
    }
    else{
        tree[u<<1].d=tree[u<<1].dl=tree[u<<1].dr=0;
        tree[u<<1|1].d=tree[u<<1|1].dl=tree[u<<1|1].dr=0;
        tree[u<<1].mk=tree[u<<1|1].mk=1;
    }
    tree[u].mk=-1;
}
void modify(int u,int l,int r,int L,int R,int x){
    if(l>=L&&r<=R){
        if(x==1) tree[u].d=tree[u].dl=tree[u].dr=0;
        else tree[u].d=tree[u].dl=tree[u].dr=len;
        tree[u].mk=x;
        return;
    }
    if(tree[u].mk!=-1) pushdown(u,l,r);
    if(L<=mid) modify(lson,L,R,x);
    if(R>mid) modify(rson,L,R,x);
    update(u,l,r);
}
int query(int u,int l,int r,int x){
    if(l==r) return l;
    if(tree[u].mk!=-1) pushdown(u,l,r);
    if(tree[u<<1].d>=x) return query(lson,x);
    if(tree[u<<1].dr+tree[u<<1|1].dl>=x) return mid-tree[u<<1].dr+1;
    return query(rson,x);
}
int main(){
    n=read(),m=read();
    build(1,1,n);
    For(i,1,m){
        int k=read(),x,y;
        if(k==2){
            x=read(),y=read();
            modify(1,1,n,x,x+y-1,0);
        }
        else{
            x=read();
            if(tree[1].d<x){
                printf("0\n");
                continue;
            }
            y=query(1,1,n,x);
            modify(1,1,n,y,y+x-1,1);
            printf("%d\n",y);
        }
    }
    return 0;
}
