#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

int main()
{
    FILE *ptf;
    ptf = fopen ("wordlist.txt", "r+");
    if (ptf == NULL)
        ptf = fopen ("wordlist.txt", "w+");

    srand(time(NULL));
    int r=0;

    char word_name[50], word_description[901],c, user_continue = 'y';
    int user_answer=0, no_of_words, number_of_lines = 1, i=0,j=0;

    while (feof(ptf) == 0)
    {
        fscanf(ptf,"%c", &c);
        if (c == '\n')
        number_of_lines++;
    }

    rewind(ptf);

    int available_lines[number_of_lines/2], total_words = number_of_lines/2;

    printf("welcome, do you want to (1) Test or (2) Save a word? enter 1 or 2 to continue");
    printf("\nthere is currently %d words in the file, enter a number now:", total_words);
    scanf("%d", &user_answer);

    while (user_answer != 1 && user_answer != 2)
    {
        printf("\ninvalid input, enter again:");
        scanf("%d", &user_answer);
    }
    if (user_answer == 1)
    {
        printf("\nok! how many words do you want to review? enter a number:");
        scanf("%d", &no_of_words);

        while (no_of_words > total_words)
        {
            printf("\nthe file doesn't contain that many words! enter a number again:");
            scanf("%d", &no_of_words);
        }
        while (no_of_words <= 0)
        {
            printf("\ninvalid input, enter a number again:");
            scanf("%d", &no_of_words);
        }

        for (i=0;i < total_words; i++)
            available_lines[i] = i*2;

        for (i=0;i < no_of_words; i++)
            {
                r = rand()%total_words;
                while (available_lines[r] == -1)
                    {
                        r = rand()%total_words;
                    }
                if (available_lines[r] != -1)
                    {
                        j = 0;
                        while(j < available_lines[r])
                            {
                                fscanf(ptf,"%c", &c);
                                if (c == '\n')
                                j++;
                            }
                        fscanf(ptf,"%s", &word_name);

                        if (i == 0)
                        printf("%s", word_name);
                        else
                        printf("\n%s", word_name);

                        available_lines[r] = -1;
                        getch();
                        j = 0;
                        while(j < 1)
                            {
                                fscanf(ptf,"%c", &c);
                                if (c == '\n')
                                j++;
                            }
                        fscanf(ptf,"%[^\n]s", &word_description);
                        printf("\n%s", word_description);
                        rewind(ptf);
                    }
            }

    }
    if (user_answer == 2)
    {
        while (user_continue == 'y' || user_continue == 'Y')
        {
        fseek(ptf,0,SEEK_END);
        printf("\nenter the word you want to add to the collection:");
        scanf("%s", &word_name);
        fprintf(ptf, "\n%s\n",word_name);
        printf("\nnow enter its description up to 900 characters:\n");

        j = 0;
        c = 'a';
        while (c != '\n')
        {
            scanf("%c", &word_description[j]);
            c = word_description[j];
            j++;
        }

        scanf("%[^\n]s", &word_description);
        fprintf(ptf,"%s", word_description);

        printf("\nif you would like to enter another word, enter (y), otherwise exit the program with any other input");
        user_continue = getch();
        }
    }
    fclose (ptf);
    return 0;
}