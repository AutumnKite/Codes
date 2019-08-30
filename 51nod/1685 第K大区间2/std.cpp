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
#define N 200010
#define M (n+1)
int n,a[N],c1[N],c2[N];LL m,k;
inline int lowbit(int x){return x&-x;}
inline void add1(int x){for(;x<=n+M;x+=lowbit(x)) c1[x]++;}
inline void add2(int x){for(;x<=n+M;x+=lowbit(x)) c2[x]++;}
inline int query1(int x){int s=0;for(;x;x-=lowbit(x)) s+=c1[x];return s;}
inline int query2(int x){int s=0;for(;x;x-=lowbit(x)) s+=c2[x];return s;}
inline int check(LL x){
    memset(c1,0,sizeof c1);
    memset(c2,0,sizeof c2);
    LL sum=0,ans=0;
    add2(M);
    For(i,1,n){
        sum+=a[i]>=x?1:-1;
        if(i&1) ans+=query2(sum+M-1),add1(sum+M);
        else ans+=query1(sum+M-1),add2(sum+M);
    }
    return ans>=k;
}
int main(){
    n=read(),k=read(),m=0;
    For(i,1,n) m=Max(m,a[i]=read());
    LL l=0,r=m,mid,ans;
    while(l<=r) if(check(mid=l+r>>1)) ans=mid,l=mid+1;else r=mid-1;
    write(ans);
    return 0;
}
