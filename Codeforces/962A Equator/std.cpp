#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <bitset>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#define LL long long
#define For(i,a,b) for(register int i=(int)(a),i_E=(int)(b);i<=i_E;++i)
#define Fod(i,a,b) for(register int i=(int)(a),i_E=(int)(b);i>=i_E;--i)
#define cross(i,a) for(register int i=hd[(a)];i;i=pr[i])
using namespace std;
inline LL Max(LL a,LL b){return a>b?a:b;}
inline LL Min(LL a,LL b){return a<b?a:b;}
inline LL Abs(LL a){return a>=0?a:-a;}
#define IN_MAX 1000000
inline char GetChar(){
    static char buf[IN_MAX],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,IN_MAX,stdin),p1==p2)?EOF:*p1++;
}
#define CH ch=getchar()
inline LL read(){
    LL x=0;int f=1,ch;
    for(CH;!isdigit(ch)&&ch!='-'&&ch!=EOF;CH);
    if(ch=='-') f=-1,CH;
    for(;isdigit(ch);CH) x=(x<<3)+(x<<1)+ch-48;
    return x*f;
}
inline void write(LL x){
    if(x<0) putchar('-'),x=-x;
    if(x<10) putchar(x+48);
    else write(x/10),putchar(x%10+48);
}
int n,a[200005],s,s2,ans;
int main(){
#ifndef ONLINE_JUDGE
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
#endif
    n=read();
    For(i,1,n) s+=a[i]=read();
    s=(s-1)>>1;
    For(i,1,n) if((s2+=a[i])>s){ans=i;break;}
    return printf("%d",ans),0;
}
