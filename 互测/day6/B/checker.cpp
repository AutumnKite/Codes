#include<bits/stdc++.h>

#define y1 dmytxdy
#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;

template <typename T> bool chkmin(T &x,T y){return x>y?x=y,1:0;}
template <typename T> bool chkmax(T &x,T y){return x<y?x=y,1:0;}

int readint(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,m;
int aans[11]={0,4,9,321,288,208,3935,2621,12386,11198,8486};
bitset<1005> c[1005],hv[1005];

int main(){
	double ans=0;
	for(int tt=1;tt<=10;tt++){
		char str[50];
		sprintf(str,"friends%d.in",tt);
		freopen(str,"r",stdin);
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++) c[i].reset(),hv[i].reset();
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d %d",&x,&y);
			c[x][y]=c[y][x]=1;
		}
		fclose(stdin);
		sprintf(str,"friends%d.out",tt);
		freopen(str,"r",stdin);
		int k,sum=0;
		printf("friends%d.out: ",tt);
		if(scanf("%d",&k)!=1){
			printf("%.3lf points.\n",0);
			continue;
		}
		if(k>m){
			printf("%.3lf points. (k should not greater than m.)\n",0);
			continue;
		}
		bool fl=0;
		for(int i=1;i<=k;i++){
			int t;
			if(scanf("%d",&t)!=1){
				fl=1;
				printf("%.3lf points.\n",0);
				break;
			}
			if(t<=0||t>n){
				fl=1;
				printf("%.3lf points. (The number of people in a celebration should not greater than n or less than 1.)\n",0);
				break;
			}
			sum+=t;
			if(sum>m+m){
				fl=1;
				printf("%.3lf points. (The total number of people in celebrations should not greater than m+m.)\n",0);
				break;
			}
			vector<int> vec(0);
			for(int j=1;j<=t;j++){
				int tmp;
				if(scanf("%d",&tmp)!=1){
					fl=1;
					printf("%.3lf points.\n",0);
					break;
				}
				if(tmp<1||tmp>n){
					fl=1;
					printf("%.3lf points. (The label should be between 1 and n.)\n",0);
					break;
				}
				vec.pb(tmp);
			}
			if(fl) break;
			for(int i1=0;i1<vec.size();i1++){
				for(int i2=i1+1;i2<vec.size();i2++){
					int p1=vec[i1],p2=vec[i2];
					if(p1==p2){
						fl=1;
						printf("%.3lf points. (The people in one celebration should be different.)\n",0);
						break;
					}
					if(!c[p1][p2]){
						fl=1;
						printf("%.3lf points. (Some pair of people became friends but they shouldn't.)\n",0);
						break;
					}
					hv[p1][p2]=hv[p2][p1]=1;
				}
				if(fl) break;
			}
			if(fl) break;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(c[i][j]!=hv[i][j]){
					fl=1;
					printf("%.3lf points. (Some pair of people didn't become friends but they should.)\n",0);
					break;
				}
			}
			if(fl) break;
		}
		if(fl) continue;
		double res=(1.0*aans[tt]/k)*(1.0*aans[tt]/k)*(1.0*aans[tt]/k)*10;
		printf("%.3lf points.\n",res);
		ans+=res;
	}
	printf("In total: %.3lf points.\n",ans);
	return 0;
}
