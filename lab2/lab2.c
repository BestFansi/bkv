#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// 根据 Readme.txt 的要求定义结构体
typedef struct word {
    int count;
    char *Word; // 这里为了与模板一致使用 Word，Readme中提到的是 w
} WORD;

// 比较函数的声明 (注意 qsort 传入的是指向数组元素的指针，即 WORD **)
int cmpword_alpha(const void *a, const void *b);
int cmpword_quant(const void *a, const void *b);
char *getword(FILE *F);

// 根据  要求，使用指向 WORD 的指针数组
WORD *words[100000];
int totalw = 0;

int main(int ac, char *av[]) {
    FILE *OUT1, *OUT2, *IN;
    char *pword;
    int i, j, found;

    if (ac < 2) {
        printf("Вы забыли указать список файлов!\n"); 
        exit(0);
    }

    // 循环处理命令行传入的每一个文件 [cite: 5, 11]
    for (i = 1; i < ac; i++) {
        IN = fopen(av[i], "r");
        if (!IN) {
            printf("Не удалось открыть файл %s\n", av[i]);
            continue;
        }
        printf("Обрабатывается файл %s\n", av[i]);

        // 获取单词并处理
        while ((pword = getword(IN)) != NULL) {
            found = 0;
            // 查找单词是否已存在于字典中
            for (j = 0; j < totalw; j++) {
                if (strcmp(words[j]->Word, pword) == 0) {
                    words[j]->count++;
                    found = 1;
                    free(pword); // 已经存在的单词，释放刚才 getword 里分配的内存
                    break;
                }
            }

            // 如果是新单词，分配结构体并加入数组 [cite: 9, 13]
            if (!found) {
                if (totalw < 100000) {
                    words[totalw] = (WORD *)malloc(sizeof(WORD));
                    words[totalw]->count = 1;
                    words[totalw]->Word = pword; // 关联 getword 分配的字符串指针
                    totalw++;
                } else {
                    free(pword); // 防止超出数组越界
                }
            }
        }
        fclose(IN);
    }

    // 打开输出文件
    OUT1 = fopen("output_alpha.txt", "w");
    OUT2 = fopen("output_quant.txt", "w");
    if (!OUT1 || !OUT2) {
        printf("Ошибка создания выходных файлов!\n");
        return 1;
    }

    // 1. 按字母顺序排序并输出 [cite: 6, 12]
    qsort(words, totalw, sizeof(WORD *), cmpword_alpha);
    for (i = 0; i < totalw; i++) {
        fprintf(OUT1, "%s: %d\n", words[i]->Word, words[i]->count);
    }

    // 2. 按频率降序排序并输出 [cite: 6, 12]
    qsort(words, totalw, sizeof(WORD *), cmpword_quant);
    for (i = 0; i < totalw; i++) {
        fprintf(OUT2, "%s: %d\n", words[i]->Word, words[i]->count);
    }

    fclose(OUT1);
    fclose(OUT2);

    // 释放动态分配的内存
    for (i = 0; i < totalw; i++) {
        free(words[i]->Word);
        free(words[i]);
    }

    printf("Обработка завершена. Результаты в output_alpha.txt и output_quant.txt\n");
    return 0;
}

// 获取单词：以字母开头，仅由字母和数字组成，并转为小写 [cite: 2, 4]
char *getword(FILE *F) {
    int c;
    char buffer[256];
    int len = 0;

    // 跳过前面的非字母字符
    while ((c = fgetc(F)) != EOF) {
        if (isalpha(c)) {
            buffer[len++] = tolower(c); // 统一转为小写 
            break;
        }
    }

    if (c == EOF) return NULL; // 文件结束

    // 继续读取字母或数字
    while ((c = fgetc(F)) != EOF) {
        if (isalnum(c)) {
            if (len < 255) { // 防止缓冲区溢出
                buffer[len++] = tolower(c);
            }
        } else {
            break; // 遇到非字母数字字符，单词结束
        }
    }

    buffer[len] = '\0'; // 字符串结尾

    // 为新单词分配内存空间并复制内容
    char *s = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(s, buffer);
    
    return s;
}

// 按字母顺序比较 (升序)
int cmpword_alpha(const void *a, const void *b) {
    WORD *w1 = *(WORD **)a;
    WORD *w2 = *(WORD **)b;
    return strcmp(w1->Word, w2->Word);
}

// 按频率大小比较 (降序)
int cmpword_quant(const void *a, const void *b) {
    WORD *w1 = *(WORD **)a;
    WORD *w2 = *(WORD **)b;
    // 如果想要降序排列，w2 的 count 减去 w1 的 count
    if (w1->count != w2->count) {
        return w2->count - w1->count; 
    }
    // 如果频率相同，则按字母顺序排列
    return strcmp(w1->Word, w2->Word);
}