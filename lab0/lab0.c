#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
Алгоритм Эратосфена.

Для нахождения всех простых чисел не больше заданного числа n, следуя методу Эратосфена, нужно выполнить следующие шаги:

1. Выписать подряд все целые числа от двух до n (2, 3, 4, …, n). Записать их в массив
   целых чисел int P[n];
2. Пусть переменная p изначально равна двум — первому простому числу.
3. Вычеркнуть из списка все числа от 2p до n, делящиеся на p (то есть, числа 2p, 3p, 4p, …)
   то есть соответствующим элементам массива присвоить значение 0.
4. Найти первое не вычеркнутое число (не равное 0), большее чем p, и присвоить значению переменной p это число.
5. Повторять шаги 3 и 4 до тех пор, пока p не станет больше, чем n
6. Все не вычеркнутые числа в списке — простые числа.
7. Удалить из массива все значения, равные 0.

На практике, алгоритм можно немного улучшить следующим образом. На шаге №3, числа можно вычеркивать, 
начиная сразу с числа p2, потому что все составные числа меньше его уже будут вычеркнуты к этому времени. 
И, соответственно, останавливать алгоритм можно, когда p*p станет больше, чем n.

Должны вычисляться простые числа и сохраняться в массиве int P[n];
*/
int main(){
    //step 1
    int i, a, n;
    printf("n = ");
    scanf("%d", &n);
    int l = n-1; // l = length of array, n =
    int* P = (int*)malloc(sizeof(int) * (n-1));
    if (P == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }
    //assignment
    for (i = 0; i < l; i++) {
        P[i] = i + 2;
    }

    printf("Array: {");
    for (i = 0; i < l-1; i++) {
        printf("%d, ", P[i]);
    } 
    i = l-1;
    printf("%d}", P[i]);
    printf("\n");

    //step2
    int p = 2;

    printf("\n*check*\n");
    //algorithm 1
    //step 5
    while (p < n) {
        //step 3
        for (i = 0; i < l; i++) {
            if (P[i] % p == 0 && P[i] >= 2*p && P[i] <= n) {
                P[i] = 0;
            }
        }
        //step 4
        for (i = 0; i < l; i++) {
            if (P[i] != 0 && P[i] > p) {
                p = P[i];
                printf("p = %d, ", p);
                break;
            }
        }
        //update the value of the last number n in the array
        for (i = l-1; i > 0; i--) {
            if (P[i] != 0) {
                n = P[i];
                printf("n = %d\n", n);
                break;
            }
        }
        
        printf("{");
        for (i = 0; i < l-1; i++) {
            printf("%d, ", P[i]);
        } 
        i = l-1;
        printf("%d}", P[i]);
        printf("\n");
    }
    printf("*check*\n\n");

    //step 7
    int count = 0;
    for (int i = 0; i < l; i++) { 
        if (P[i] != 0) {
            P[count] = P[i];
            count++;
        }
    }  
    P = (int *)realloc(P, count * sizeof(int));
    if (P == NULL) {
        printf("Ошибка перераспределения памяти\n");
        return 1;
    }

    //output
    printf("Prime numbers: {");
    for (i = 0; i < count-1; i++) {
        printf("%d, ", P[i]);
    } 
    i = count-1;
    printf("%d}", P[i]);
    printf("\n");

    return 0;
}