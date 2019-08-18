#include <cstdio>
#include <cstring>
using namespace std;
const int d[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
int n,m,l,a[35][35][35],h,t,ans[35][35][35];
char s[35];
struct node{
	int x,y,z;
}S,E,q[100005];
int bfs(node u){
	h=0,t=1,q[t]=u,a[u.x][u.y][u.z]=1,ans[u.x][u.y][u.z]=0;
	while (h<t){
		u=q[++h];
		for (register int i=0;i<6;++i){
			node v=(node){u.x+d[i][0],u.y+d[i][1],u.z+d[i][2]};
			if (v.x<1||v.x>l||v.y<1||v.y>m||v.z<1||v.z>n||a[v.x][v.y][v.z]) continue;
			q[++t]=v,a[v.x][v.y][v.z]=1,ans[v.x][v.y][v.z]=ans[u.x][u.y][u.z]+1;
			if (v.x==E.x&&v.y==E.y&&v.z==E.z)
				return printf("Escaped in %d minute(s).\n",ans[E.x][E.y][E.z]),1;
		}
	}
	return 0;
}
int main(){
	while (1){
		scanf("%d%d%d",&l,&m,&n);
		if (l==0) return 0;
		for (register int i=1;i<=l;++i)
			for (register int j=1;j<=m;++j){
				scanf("%s",s+1);
				for (register int k=1;k<=n;++k){
					if (s[k]=='#') a[i][j][k]=1; else a[i][j][k]=0;
					if (s[k]=='S') S=(node){i,j,k};
					if (s[k]=='E') E=(node){i,j,k};
				}
			}
		if (!bfs(S)) printf("Trapped!\n");
	}
}
