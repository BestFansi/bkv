#include <stdio.h>
#include <stdlib.h>
int main(){
    //step 1
    int i, n;
    printf("n = ");
    scanf("%d", &n);
    int P[n];
    for (i = 0; i < n-1; i++) {
        P[i] = i + 2;
    }
    for (i = 0; i < n-1; i++) {
        printf("%d, ", P[i]);
    } 
    printf("\n");
    //step2
    int p = 2;

    //algorithm 1
    //step 5
    while (p < n) {
        //step 3
        for (i = 0; i < n-1; i++) {
            if (P[i] % p == 0 && P[i] >= 2*p && P[i] <= n) {
                P[i] = 0;
            }
        }
        for (i = 0; i < n -1; i++) {
            printf("%d, ", P[i]);
        }
        printf("\n");
        //step 4
        for (i = 0; i < n; i++) {
            if (P[i] != 0 && P[i] > p) {
                p = P[i];
                printf("p = %d\n", p);
                break;
            }
        }
    }
    
    return 0;
}