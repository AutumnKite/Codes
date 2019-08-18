#include <cstdio>
long long l,r,pow[20],a[10],b[10];
void solve(long long a[],long long n){
	int num[20],m=0;
	long long pre=0,suf=n;
	for (;n;n/=10) num[++m]=n%10,a[0]-=pow[m-1];
	for (register int i=m;i;--i){
		for (register int j=0;j<=9;++j) a[j]+=pow[i-1]*pre;
		for (register int j=0;j<num[i];++j) a[j]+=pow[i-1];
		a[num[i]]+=(suf-=num[i]*pow[i-1])+1,pre=pre*10+num[i];
	}
}
int main(){
	scanf("%lld%lld",&l,&r),pow[0]=1;
	for (register int i=1;i<=18;++i) pow[i]=pow[i-1]*10;
	solve(a,l-1),solve(b,r);
	for (register int i=0;i<=9;++i) printf("%lld ",b[i]-a[i]);
}
