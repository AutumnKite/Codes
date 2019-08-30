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
#define N 500005
int n,k,L,R,sum[N],st[N][25],Log[N];LL ans;
struct node{
    int L,l,r,p;
    bool operator <(const node&b)const{return sum[p]-sum[L-1]<sum[b.p]-sum[b.L-1];}
};
priority_queue<node>H;
inline int Maxp(int a,int b){return sum[a]>sum[b]?a:b;}
inline int query(int l,int r){
    int len=Log[r-l+1];
    return Maxp(st[l][len],st[r-(1<<len)+1][len]);
}
int main(){
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    n=read(),k=read(),L=read(),R=read();
    For(i,1,n) sum[i]=sum[i-1]+read(),st[i][0]=i;
    For(j,1,20){
        for(int i=1;i+(1<<j)-1<=n;i++){
            st[i][j]=Maxp(st[i][j-1],st[i+(1<<j-1)][j-1]);
        }
    }
    Log[1]=0;For(i,2,n) Log[i]=Log[i>>1]+1;
    for(int i=1;i+L-1<=n;i++) H.push((node){i,i+L-1,Min(i+R-1,n),query(i+L-1,Min(i+R-1,n))});
    while(k--){
        node T=H.top();H.pop();
        ans+=sum[T.p]-sum[T.L-1];
        if(T.l<=T.p-1) H.push((node){T.L,T.l,T.p-1,query(T.l,T.p-1)});
        if(T.p+1<=T.r) H.push((node){T.L,T.p+1,T.r,query(T.p+1,T.r)});
    }
    write(ans);
    return 0;
}
