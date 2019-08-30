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
#define N 2000005
int n,c,m,val[N],pre[N],last[N],ans[N];
struct node{
    int l,r,id;
}q[N];
bool cmp(node a,node b){
    return a.r<b.r;
}
int T[N];
inline int lowbit(int x){return x&-x;}
inline void modify(int x,int t){
    for(;x<=n;x+=lowbit(x)) T[x]+=t;
}
inline int query(int x){
    int sum=0;
    for(;x;x-=lowbit(x)) sum+=T[x];
    return sum;
}
int main(){
#ifdef ONLINE_JUDGE
#else
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    n=read();
    For(i,1,n) val[i]=read(),pre[i]=last[val[i]],last[val[i]]=i;
    m=read();
    For(i,1,m) q[i]=(node){read(),read(),i};
    sort(q+1,q+1+m,cmp);
    int now=1;
    For(i,1,n){
    	modify(pre[i]+1,1),modify(i+1,-1);
    	while(q[now].r==i) ans[q[now].id]=query(q[now].l),now++;
    	if(now>m) break;
    }
    For(i,1,m) write(ans[i]),putchar('\n');
    return 0;
}