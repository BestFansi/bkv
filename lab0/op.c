#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "op.h"
int* step1(int n){
    int* P = (int*)malloc(sizeof(int) * (n-1));
    if (P == NULL) {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }
    //assign
    for (int i = 0; i < n-1; i++) {
        P[i] = i + 2;
    }
    return P;
}

//step 3, 4, 5
int* algorithm_1(int* P, int p, int n) {
    //step 5
    int i;
    bool found = true;
    printf("\n*process*\n");
    while (p <= n) {
        found = false;
        //step 3
        for (int val = 2 * p; val <= n; val += p) {
            int index = val - 2;
            P[index] = 0;
        }
        //step 4
        for (i = 0; i < n-1; i++) {
            if (P[i] != 0 && P[i] > p) {
                p = P[i];
                printf("p = %d, ", p);
                found = true;
                break;
            }
        }  
        if (!found) {
            break;
        }     
        printf("{");
        for (i = 0; i < n-2; i++) {
            printf("%d, ", P[i]);
        } 
        i = n-2;
        printf("%d}", P[i]);
        printf("\n");
    }
    printf("*process*\n\n");
    return P;
}

//step 3, 4, 5 (only changed step 3 and the condition for ending the loop (p > n and p*p > n))
int *algorithm_2(int* P, int p, int n) {
    int i;
    printf("\n*process*\n");
    while (p*p <= n) {
        //step 3
        for (int val = p * p; val <= n; val += p) {
            int index = val - 2; 
            P[index] = 0;        
        }
        //step 4
        for (i = 0; i < n-1; i++) {
            if (P[i] != 0 && P[i] > p) {
                p = P[i];
                printf("p = %d, ", p);
                break;
            }
        }
        //check array
        printf("{");
        for (i = 0; i < n-2; i++) {
            printf("%d, ", P[i]);
        } 
        i = n-2;
        printf("%d}", P[i]);
        printf("\n");
    }
    printf("*process*\n\n");
    return P;
}
int* step7(int* P, int n) {
    int count = 0;
    for (int i = 0; i < n-1; i++) { 
        if (P[i] != 0) {
            P[count] = P[i];
            count++;
        }
    }  
    P = (int *)realloc(P, count * sizeof(int));
    if (P == NULL) {
        printf("Ошибка перераспределения памяти\n");
        return NULL;
    }
    //output
    printf("Prime numbers: {");
    for (int i = 0; i < count-1; i++) {
        printf("%d, ", P[i]);
    } 
    int i = count-1;
    printf("%d}\n", P[i]);
    return P;
}