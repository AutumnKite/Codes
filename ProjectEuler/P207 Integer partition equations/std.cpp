
#include <cstdio>
#include <cmath>
double p;
long long s1 = 0, s2 = 0, a = 0, n, m;
int main(){
    scanf("%lld", &m);
    while (s2 == 0 || 1.0 * s1 / s2 >= 1.0 / m){
        ++a;
        p = log(a + 1) / log(2);
        if (int(p) == p) ++s1, ++s2;
        else if (int(a) == a) ++s2;
    }
    return printf("%lld", a * (a + 1)), 0;
}
/*
#include <cstdio>
#include <cmath>
double a, p, t;
long long s1 = 0, s2 = 0, n = 0, m;
int main(){
    scanf("%lld", &m);
    while (s2 == 0 || 1.0 * s1 / s2 >= 1.0 / m){
        ++n;
        t = sqrt(1 + 4 * n);
        a = (1 + t) / 2;
        p = log(a) / log(2);
        if (int(p) == p) ++s1, ++s2;
        else if (int(t) == t) ++s2;
    }
    return printf("%lld", n), 0;
}
*/
