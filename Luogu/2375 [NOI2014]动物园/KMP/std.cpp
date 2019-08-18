#include <cstdio>
#include <cstring>
char a[1000005];
int T, n, fail[1000005], s[1000005];
int main(){
    scanf("%d", &T);
    while (T--){
        scanf("%s", a + 1), n = strlen(a + 1), fail[1] = 0, s[1] = 1;
        for (register int i = 2, j = 0; i <= n; ++i){
            while (j && a[i] != a[j + 1]) j = fail[j];
            j += a[i] == a[j + 1], fail[i] = j, s[i] = s[j] + 1;
        }
        int ans = 1;
        for (register int i = 2, j = 0; i <= n; ++i){
            while (j && a[i] != a[j + 1]) j = fail[j];
            j += a[i] == a[j + 1];
            while ((j << 1) > i) j = fail[j];
            ans = 1ll * ans * (s[j] + 1) % 1000000007;
        }
        printf("%d\n", ans);
    }
}