#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main() {
    long long N, M;
    scanf("%lld %lld", &N, &M);
    long long numer = N * M;
    long long denom = M - N;
    long long comm_div = gcd(numer, denom);
    printf("%lld/%lld\n", numer /  comm_div, denom / comm_div);
    return 0;
}