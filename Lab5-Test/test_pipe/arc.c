#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    long long N, M;
    scanf("%lld %lld", &N, &M);

    long long num = N * M;
    long long den = M - N;

    long long g = gcd(num, den);

    printf("%lld/%lld\n", num / g, den / g);

    return 0;
}
