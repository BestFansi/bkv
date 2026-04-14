#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// здесь все что необходимо глобальное
typedef struct word {
  int count;
  char *Word;
 } WORD;
 
int cmpword_alpha(WORD *, WORD *);
int cmpword_quant(WORD *, WORD *);
char *getword(FILE *F);

WORD words[100000];

int totalw=0;

int main(int ac, char *av[])
{
  FILE *OUT1, *OUT2, *IN;
  char *pword;
  int i, found;

  OUT1 = fopen("dict_alpha.txt", "w");
  OUT2 = fopen("dict_quant.txt", "w");
  if (!OUT1 || !OUT2) {
      printf("Ошибка создания выходных файлов!\n");
      return 1;
  }

  if (ac<2)
  {
    printf ("Вы забыли указать список файлов!\n"); exit (0);
  }
  while (--ac) // идем по списку файлов
  {
   IN=fopen(av[ac],"r");
   printf("Обрабатывается файл %s\n",av[ac]);
   // открываем очередной файл
   while ((pword=getword(IN))!=NULL)
    { // .........................
      found = 0;
      for (i = 0; i < totalw; i++) {
          if (strcmp(words[i].Word, pword) == 0) {
              words[i].count++;
              found = 1;
              break;
          }
      }
      
      if (!found && totalw < 100000) {
          words[totalw].count = 1;
          words[totalw].Word = (char *)malloc(strlen(pword) + 1);
          strcpy(words[totalw].Word, pword);
          totalw++;
      }
    }
   fclose(IN);
  }
 qsort(words,totalw,sizeof(WORD),
        (int (*)(const void *, const void *))cmpword_alpha );
    for (i = 0; i < totalw; i++) {
        fprintf(OUT1, "%s : %d\n", words[i].Word, words[i].count);
    }
 qsort(words,totalw,sizeof(WORD),
        (int (*)(const void *, const void *))cmpword_quant );
    for (i = 0; i < totalw; i++) {
        fprintf(OUT2, "%s : %d\n", words[i].Word, words[i].count);
    }
return 0; 
}
char *getword(FILE *F)
{ 
 static char s[1024];
 int c, i = 0;
 while ((c = fgetc(F)) != EOF) {
     if (isalpha(c)) {
         s[i++] = tolower(c); 
         break;
     }
 }
 if (c == EOF) return NULL;


 while ((c = fgetc(F)) != EOF) {
     if (isalnum(c)) {
         s[i++] = tolower(c);
     } else {
         ungetc(c, F);
         break;
     }
 }
 s[i] = '\0';
 return s;
}
int cmpword_alpha(WORD *w1,  WORD *w2)
{
return strcmp(w1->Word, w2->Word);
}
int cmpword_quant(WORD *w1,  WORD *w2)
{
return w2->count - w1->count;
}
