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
#define N 200005
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
struct node{
    int val,id;
    bool operator < (const node&x)const{
        return val<x.val;
    }
    node(int x=0,int y=0){val=x,id=y;}
}data[N];
struct Tree{
    int ls,rs,sum;
}tree[N<<6];
int n,m,num[N],cnt,root[N];
#define mid (l+r>>1)
void build(int &u,int l,int r){
    tree[u=++cnt].sum=0;
    if(l==r) return;
    build(tree[u].ls,l,mid);
    build(tree[u].rs,mid+1,r);
}
void insert(int &u,int tu,int l,int r,int x){
    u=++cnt,tree[u]=tree[tu],tree[u].sum++;
    if(l==r) return;
    if(x<=mid) insert(tree[u].ls,tree[tu].ls,l,mid,x);
    else insert(tree[u].rs,tree[tu].rs,mid+1,r,x);
}
int query(int L,int R,int l,int r,int k){
    if(l==r) return l;
    int s=tree[tree[R].ls].sum-tree[tree[L].ls].sum;
    if(k<=s) return query(tree[L].ls,tree[R].ls,l,mid,k);
    else return query(tree[L].rs,tree[R].rs,mid+1,r,k-s);
}
int main(){
    int n=read(),m=read();
    For(i,1,n) data[i]=node(read(),i);
    sort(data+1,data+1+n);
    For(i,1,n) num[data[i].id]=i;
    cnt=0,build(root[0],1,n);
    For(i,1,n) insert(root[i],root[i-1],1,n,num[i]);
    For(i,1,m){
        int l=read(),r=read(),k=read();
        printf("%d\n",data[query(root[l-1],root[r],1,n,k)].val);
    }
    return 0;
}
