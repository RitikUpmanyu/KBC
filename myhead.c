
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SPACE                           \
    else                                \
    {                                   \
        printf("                    "); \
    }

#define QUES_POINTER printf("   You are here ->  ")
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
// these colors get displayed on gcc so they can be used like this printf(RED "This text is RED!" COLOR_RESET "\n");
#define SP printf("    ")

//main formatting function, not to be directly called(use formatques to implement this)
int formattextq(char *str, int width, int num_lines, int num_lines_og, int og, int money_flag)
{

    int length_str = strlen(str);
    if (num_lines % 2 == 0)
    {
        ++num_lines;
    }
    if (num_lines_og % 2 == 0)
    {
        ++num_lines_og;
    }
    if (length_str <= width)
    {
        if (num_lines == 3)
        {
            printf("____");
        }
        else if (!money_flag)
            SP;
        for (int l = 0; l < ((num_lines - 1) * -1) / 2; l++)
        {
            printf(" ");
        }
        printf("\\ ");
        for (int j = 0; j < length_str; j++)
        {
            char d = str[j];
            printf("%c", d);
        }
        for (int m = 0; m < width - length_str; m++)
        {
            printf(" ");
        }
        for (int l = 0; l < (num_lines + num_lines_og - 3) / 2; l++)
        {
            printf(" ");
        }
        if (og % 2 == 0)
        {
            printf("  ");
        }

        printf("/");
        printf("\n");
        for (int l = 0; l < ((num_lines - 3) * -1) / 2; l++)
        {
            printf(" ");
        }
        if (money_flag)
        {
            printf("                    ");
        }
        else
            SP;
        for (int i = 0; i <= width; i++)
        {
            printf("^");
        }
        if (og % 2 == 0)
        {
            printf("^^");
        }

        return 0;
    }
    else
    {
        if (num_lines >= 3)
        {
            if (num_lines == 3)
            {
                printf("____");
            }
            else
                SP;
            for (int l = 0; l < (num_lines - 3) / 2; l++)
            {
                printf(" ");
            }
            printf("/ ");
            for (int l = 0; l < (num_lines_og - num_lines) / 2; l++)
            {
                printf(" ");
            }
        }
        else
        {
            SP;
            for (int l = 0; l < ((num_lines - 1) * -1) / 2; l++)
            {
                printf(" ");
            }
            printf("\\ ");
            for (int l = 0; l < (num_lines + num_lines_og - 3) / 2; l++)
            {
                printf(" ");
            }
        }
        int count;
        for (int i = 0; i < width; i++)
        {
            char c = str[i];
            if (c == ' ')
                count = i;
        }
        for (int j = 0; j <= count; j++)
        {
            char d = str[j];
            printf("%c", d);
        }
        //printing extra spaces to fill up width
        for (int m = 0; m < width - count; m++)
        {
            printf(" ");
        }
        if (num_lines >= 3)
        {
            for (int l = 0; l < (num_lines_og - num_lines) / 2; l++)
            {
                printf(" ");
            }
            printf(" \\");
            if (num_lines == 3)
            {
                printf("____");
            }
        }
        else
        {
            for (int l = 0; l < (num_lines + num_lines_og - 3) / 2; l++)
            {
                printf(" ");
            }

            printf(" /");
        }
        printf("\n");
        char remaining_str[length_str - count];
        for (int k = 0; k < length_str - count - 1; k++)
        {
            remaining_str[k] = str[count + k + 1];
        }
        remaining_str[length_str - count - 1] = '\0';
        num_lines -= 2;
        formattextq(remaining_str, width, num_lines, num_lines_og, og, 0); //recursion is awesome
    }
}

//a function which counts lines of a string which has to be fitted in a limited width-
void linecount(char *str, int width, int *num_lines)
{

    int length_str = strlen(str);
    if (length_str <= width)
    {
        ++(*num_lines);
        return;
    }
    else
    {
        int count;
        for (int i = 0; i < width; i++)
        {
            char c = str[i];
            if (c == ' ')
                count = i;
        }
        ++(*num_lines);
        char remaining_str[length_str - count];
        for (int k = 0; k < length_str - count - 1; k++)
        {
            remaining_str[k] = str[count + k + 1];
        }
        linecount(remaining_str, width, num_lines); //recursion here
    }
}

//formats question in a pretty box according to width
void formatques(char *str, int width, int money_flag)
{
    int lines = 0;
    int *linesptr = &lines;
    linecount(str, width, linesptr);
    if (lines % 2 == 0)
    {
        printf(" ");
    }
    if (!money_flag)
    {
        if (lines == 1)
        {
            printf("____");
        }
        else
            SP;
    }
    for (int i = 0; i < (lines - 1) / 2; i++)
    {
        printf(" ");
    }
    printf("/");
    for (int j = 0; j <= width; j++)
    {
        printf("^");
    }
    printf("\\");
    if (!money_flag)
    {
        if (lines == 1)
        {
            printf("____");
        }
    }
    printf("\n");
    if (money_flag)
        printf("                    ");
    formattextq(str, width, lines, lines, lines, money_flag); //yes i am indeed passing same three arguments
}

int formattexto(char *str1, char *str2, int width, int num_lines, int num_lines_og, int og)
{

    int length_str1 = strlen(str1);
    int length_str2 = strlen(str2);
    if (num_lines % 2 == 0)
    {
        ++num_lines;
    }
    if (num_lines_og % 2 == 0)
    {
        ++num_lines_og;
    }
    if (length_str1 <= width)
    {
        if (num_lines == 3)
        {
            printf("____");
        }
        else
            SP;
        for (int l = 0; l < ((num_lines - 1) * -1) / 2; l++)
        {
            printf(" ");
        }
        printf("\\ ");
        for (int j = 0; j < length_str1; j++)
        {
            char d = str1[j];
            printf("%c", d);
        }
        for (int m = 0; m < width - length_str1; m++)
        {
            printf(" ");
        }
        for (int l = 0; l < (num_lines + num_lines_og - 3) / 2; l++)
        {
            printf(" ");
        }
        if (og % 2 == 0)
        {
            printf("  ");
        }

        printf("/");
    }
    else
    {
        if (num_lines >= 3)
        {
            if (num_lines == 3)
            {
                printf("____");
            }
            else
                SP;
            for (int l = 0; l < (num_lines - 3) / 2; l++)
            {
                printf(" ");
            }
            printf("/ ");
            for (int l = 0; l < (num_lines_og - num_lines) / 2; l++)
            {
                printf(" ");
            }
        }
        else
        {
            SP;
            for (int l = 0; l < ((num_lines - 1) * -1) / 2; l++)
            {
                printf(" ");
            }
            printf("\\ ");
            for (int l = 0; l < (num_lines + num_lines_og - 3) / 2; l++)
            {
                printf(" ");
            }
        }
        int count;
        for (int i = 0; i < width; i++)
        {
            char c = str1[i];
            if (c == ' ')
                count = i;
        }
        for (int j = 0; j <= count; j++)
        {
            char d = str1[j];
            printf("%c", d);
        }
        //printing extra spaces to fill up width
        for (int m = 0; m < width - count; m++)
        {
            printf(" ");
        }
        if (num_lines >= 3)
        {
            for (int l = 0; l < (num_lines_og - num_lines) / 2; l++)
            {
                printf(" ");
            }
            printf(" \\");
            if (num_lines == 3)
            {
                printf("____");
            }
        }
        else
        {
            for (int l = 0; l < (num_lines + num_lines_og - 3) / 2; l++)
            {
                printf(" ");
            }

            printf(" /");
        }
        printf("\n");
        char remaining_str[length_str1 - count];
        for (int k = 0; k < length_str1 - count - 1; k++)
        {
            remaining_str[k] = str1[count + k + 1];
        }
        remaining_str[length_str1 - count - 1] = '\0';
        num_lines -= 2;

        formattextq(remaining_str, width, num_lines, num_lines_og, og, 0); //recursion is awesome
    }
    if (length_str2 <= width)
    {
        if (num_lines == 3)
        {
            printf("____");
            printf("____");
        }
        else
        {
            SP;
            SP;
        }
        for (int l = 0; l < ((num_lines - 1) * -1) / 2; l++)
        {
            printf(" ");
        }
        printf("\\ ");
        for (int j = 0; j < length_str2; j++)
        {
            char d = str2[j];
            printf("%c", d);
        }
        for (int m = 0; m < width - length_str2; m++)
        {
            printf(" ");
        }
        for (int l = 0; l < (num_lines + num_lines_og - 3) / 2; l++)
        {
            printf(" ");
        }
        if (og % 2 == 0)
        {
            printf("  ");
        }

        printf("/");
        printf("\n");
        SP;
        for (int l = 0; l < ((num_lines - 3) * -1) / 2; l++)
        {
            printf(" ");
        }
        for (int i = 0; i <= width; i++)
        {
            printf("^");
        }
        if (og % 2 == 0)
        {
            printf("^^");
        }
        SP;
        SP;
        for (int l = 0; l < ((num_lines - 5) * -1) / 2; l++)
        {
            printf(" ");
        }
        for (int i = 0; i <= width; i++)
        {
            printf("^");
        }
        if (og % 2 == 0)
        {
            printf("^^");
        }

        return 0;
    }
    else
    {
        if (num_lines >= 3)
        {
            if (num_lines == 3)
            {
                printf("____");
            }
            else
                SP;
            for (int l = 0; l < (num_lines - 3) / 2; l++)
            {
                printf(" ");
            }
            printf("/ ");
            for (int l = 0; l < (num_lines_og - num_lines) / 2; l++)
            {
                printf(" ");
            }
        }
        else
        {
            SP;
            for (int l = 0; l < ((num_lines - 1) * -1) / 2; l++)
            {
                printf(" ");
            }
            printf("\\ ");
            for (int l = 0; l < (num_lines + num_lines_og - 3) / 2; l++)
            {
                printf(" ");
            }
        }
        int count;
        for (int i = 0; i < width; i++)
        {
            char c = str2[i];
            if (c == ' ')
                count = i;
        }
        for (int j = 0; j <= count; j++)
        {
            char d = str2[j];
            printf("%c", d);
        }
        //printing extra spaces to fill up width
        for (int m = 0; m < width - count; m++)
        {
            printf(" ");
        }
        if (num_lines >= 3)
        {
            for (int l = 0; l < (num_lines_og - num_lines) / 2; l++)
            {
                printf(" ");
            }
            printf(" \\");
            if (num_lines == 3)
            {
                printf("____");
            }
        }
        else
        {
            for (int l = 0; l < (num_lines + num_lines_og - 3) / 2; l++)
            {
                printf(" ");
            }

            printf(" /");
        }
        printf("\n");
        char remaining_str[length_str2 - count];
        for (int k = 0; k < length_str2 - count - 1; k++)
        {
            remaining_str[k] = str2[count + k + 1];
        }
        remaining_str[length_str2 - count - 1] = '\0';
        num_lines -= 2;
        formattextq(remaining_str, width, num_lines, num_lines_og, og, 0); //recursion is awesome
    }
}

void formatopt(char *str1, char *str2, int width)
{
    int lines1 = 0;
    int *linesptr1 = &lines1;
    linecount(str1, width, linesptr1);
    int lines2 = 0;
    int *linesptr2 = &lines2;
    linecount(str2, width, linesptr2);
    int lines = lines1;
    if (lines1 < lines2)
        lines = lines2;
    if (lines < 2)
    {
        if (lines1 % 2 == 0)
        {
            printf(" ");
        }
        if (lines1 == 1)
        {
            printf("____");
        }
        else
            SP;
        for (int i = 0; i < (lines1 - 1) / 2; i++)
        {
            printf(" ");
        }
        printf("/");
        for (int j = 0; j <= width; j++)
        {
            printf("^");
        }
        printf("\\");
        if (lines1 == 1)
        {
            printf("____");
        }
        if (lines2 % 2 == 0)
        {
            printf(" ");
        }
        if (lines2 == 1)
        {
            printf("____");
        }
        else
            SP;
        for (int i = 0; i < (lines2 - 1) / 2; i++)
        {
            printf(" ");
        }
        printf("/");
        for (int j = 0; j <= width; j++)
        {
            printf("^");
        }
        printf("\\");
        if (lines2 == 1)
        {
            printf("____");
        }
        printf("\n");

        formattexto(str1, str2, width, lines, lines, lines);
        printf("\n");
    }
    else
    {
        int len = strlen(str1);
        if (strlen(str1) < strlen(str2))
            len = strlen(str2);
        formatques(str1, len, 0);
        printf("\n");
        formatques(str2, len, 0);
        printf("\n");
    }
}