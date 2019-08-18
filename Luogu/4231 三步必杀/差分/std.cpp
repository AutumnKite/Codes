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
#define N 10000005
#define M 300005
int n,m;
LL c[N];
int main(){
    n=read(),m=read();
    For(i,1,m){
        int l=read(),r=read();LL s=read(),e=read(),t=(e-s)/(r-l);
        c[l]+=s,c[l+1]+=t-s,c[r+1]-=t+e,c[r+2]+=e;
    }
    For(i,1,n) c[i]+=c[i-1];For(i,1,n) c[i]+=c[i-1];
    LL sum=0,ans=0;
    For(i,1,n) sum^=c[i],ans=Max(ans,c[i]);
    write(sum),putchar(' '),write(ans);
    return 0;
}
