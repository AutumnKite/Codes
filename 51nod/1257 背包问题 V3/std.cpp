#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
const int N=50005;
int n,m;
double x,mid,ans;
struct node{
	int p,w,id;
	double t;
	bool operator <(const node&b)const{return t>b.t;}
}a[N];
long long gcd(long long a,long long b){
	if (!b) return a;
	else return gcd(b,a%b);
}
void print(long long a,long long b){
	register long long GCD=gcd(a,b);
	printf("%lld/%lld",a/GCD,b/GCD);
}
bool check(int o){
	for (register int i=1;i<=n;++i) a[i].t=a[i].p-a[i].w*x;
	sort(a+1,a+1+n);
	register long long P=0,W=0;
	for (register int i=1;i<=m;++i) P+=a[i].p,W+=a[i].w;
	if (o) print(P,W);
	return P-x*W>=0;
}
int main(){
	n=read(),m=read();
	for (register int i=1;i<=n;++i) a[i].w=read(),a[i].p=read(),a[i].id=i;
	long long l=0,r=250000000000000ll,mid;
	while (l<=r){
		mid=(l+r)>>1,x=mid/100000.;
		if (check(0)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	x=ans/100000.,check(1);
}
