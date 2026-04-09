#include <stdio.h>
#include <ctype.h>
int isvowel(int c);
int main(int argc, char **argv)
{
    FILE *F;
    int c, total=0, line=0, digit=0, punct=0, space=0, letter=0, lower=0, upper=0, vowel=0, cons=0;
    char filename[256];
    printf("Please enter a file name: ");
    scanf("%s", filename);
    F = fopen(filename, "r");
    if (F == NULL)
    {
        printf("Unable to open");
        return 1;
    }

   	while ( (c=fgetc(F))!=EOF)
   	{
		total++;
        if (c == '\n') line++;
        if (isdigit(c)) digit++;
        if (ispunct(c)) punct++;
        if (isspace(c)) space++;

        if (isalpha(c)) {
            letter++;
            if (islower(c)) lower++;
            if (isupper(c)) upper++;
   	        if (isvowel(c)) vowel++;
   	        else cons++;
	    }
   	}
    fclose(F);
   	printf("file: %s\ntotal=%d\nline=%d\ndigit=%\npunct=%d\nspace=%d\nletters=%d\nlower=%d\nupper=%d\nvowel=%d\ncons=%d\n",filename,total,line,digit,punct,space,letter,lower,upper,vowel,cons);
 	return 0;
}

int isvowel(int c)
{
	switch(tolower(c))
	{
		case 'a': 
		case 'e':
		case 'i': 
		case 'o': 
		case 'u':
		case 'y': return 1;
	}
	return 0;
}