#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
int read(){
    int x=0,f=1,ch=getchar();
    for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
    for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
    return x*f;
}
const int N=100005;
int n,dp[N],cnt,m;
struct node{
    int x,y,s;
    bool operator <(const node&b) const{return y<b.y||y==b.y&&x<b.x;}
}a[N],b[N];
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
int find(int l,int r,int x){
    int mid,ans=0;
    while (l<=r){
        mid=(l+r)>>1;
        if (x<=b[mid].y) r=mid-1;
        else ans=mid,l=mid+1;
    }
    return ans;
}
int main(){
    n=read();
    for (register int i=1;i<=n;++i){
        register int p=read(),q=read();
        if (p+q<n) a[++cnt]=(node){p+1,n-q,1};
    }
    sort(a+1,a+1+cnt),b[++m]=a[1];
    for (register int i=2;i<=cnt;++i)
        if (a[i-1]<a[i]) b[++m]=a[i]; else ++b[m].s,b[m].s=min(b[m].y-b[m].x+1,b[m].s);
    dp[0]=0;
    for (register int i=1;i<=m;++i) dp[i]=max(dp[find(0,i-1,b[i].x)]+b[i].s,dp[i-1]);
    printf("%d",n-dp[m]);
}
