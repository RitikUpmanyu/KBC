
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
int formattextq(char *str, int width, int num_lines, int num_lines_og, int og, int money_flag) //moneyflag is for putting the box on current money
{

    int length_str = strlen(str); //begin by checking the length of our string
    if (num_lines % 2 == 0)       //if number is even , add one so that symmetry can be maintained in the box
    {
        ++num_lines;
    }
    if (num_lines_og % 2 == 0) //same thing but num_lines_og will not be changed after this, and og doesn't change at all so it tracks the actual number of lines
    {
        ++num_lines_og;
    }
    if (length_str <= width) //this condition prints the last line, only executes when this function is called for the last time
    {
        if (num_lines == 3) //styling choice
        {
            printf("____");
        }
        else if (!money_flag) //don't need this space in money box, b/c we add more space later anyways
            SP;               //this is a MACRO(see the definition above)
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
        if (money_flag) //only happens when moneyflag in on
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
    else //this condition executes for all the above lines of code, using recursion
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
        for (int i = 0; i < width; i++) //this keeps track of the last space before the maximum width , so that we can split the string from there (to fit in the box)
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
        char remaining_str[length_str - count]; //making the remaining string for using recursion
        for (int k = 0; k < length_str - count - 1; k++)
        {
            remaining_str[k] = str[count + k + 1];
        }
        remaining_str[length_str - count - 1] = '\0';
        num_lines -= 2;
        formattextq(remaining_str, width, num_lines, num_lines_og, og, 0); //and here is RECURSION !!!
    }
}

//a function which counts lines of a string which has to be fitted in a box of limited width-
//takes a point num_lines and changes it by how many times the fuction is called which basically tells the number of lines the given string will require
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
        char remaining_str[length_str - count]; //using the same logic of putting remaining string in the recursive loop
        for (int k = 0; k < length_str - count - 1; k++)
        {
            remaining_str[k] = str[count + k + 1];
        }
        linecount(remaining_str, width, num_lines); //recursion here
    }
}

//formats question in a pretty box according to width
//this fuction uses linecount function and formattextq both, and this is the fuction which gets called in the main file
//money_flag is for the case when this fuction is used in moneyboard, put money_flag = 0 as default
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
    formattextq(str, width, lines, lines, lines, money_flag); //yes i am indeed passing same three arguments(explained in formattextq)
}

//almost similar fuction as formattextq but uses the stategy twice for printing options side by side
// there are no multiple line so becomes a little easier (no resursion here)
int formattexto(char *str1, char *str2, int width)
{

    int length_str1 = strlen(str1); //for first option
    int length_str2 = strlen(str2); //for second option

    SP;

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

    printf("/");

    SP;
    SP;

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

    printf("/");
    printf("\n");
    SP;
    printf(" ");

    for (int i = 0; i <= width; i++)
    {
        printf("^");
    }
    SP;
    SP;

    printf("  ");

    for (int i = 0; i <= width; i++)
    {
        printf("^");
    }

    return 0;
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

        printf("____/");

        for (int j = 0; j <= width; j++)
        {
            printf("^");
        }

        printf("\\________/");

        for (int j = 0; j <= width; j++)
        {
            printf("^");
        }

        printf("\\____\n");

        formattexto(str1, str2, width);
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