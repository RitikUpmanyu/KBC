
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "formatting.c"

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

struct question
{
    char *question;
    char *option1;
    char *option2;
    char *option3;
    char *option4;
    int answer;
};
struct question questions[30];

// these four functions are declared here and defined at the end
int display_question(int, struct question);
int display_question_locked(int, struct question, int);
int money_board(int, char[15]);
int frame(int, struct question, int, int, int);
int read_questions(struct question[], size_t, char[]); //this function takes 3 arguments array of stucts, size of that array, and name of the file where questions are stored
void moneyfield(int, int, char **, char *);            // this is a helper function for moneyboard
int formattext(char *, int);
int formattextq(char *str, int width, int, int, int, int);
void linecount(char *str, int width, int *num_lines);
void formatques(char *str, int width, int);
int formattexto(char *str1, char *str2, int width);
void formatopt(char *str1, char *str2, int width);
//NOTE - ques.txt currently have 30 questions (even numbered questions are the main ones and odd numbered ones are their alternates for flip the question lifeline)
//main function still needs work
int main()
{
    //getting rid of segmentation fault-->allocate memory
    for (int i = 0; i < 30; i++)
    {
        questions[i].question = malloc(500);
        questions[i].option1 = malloc(500);
        questions[i].option2 = malloc(500);
        questions[i].option3 = malloc(500);
        questions[i].option4 = malloc(500);
    }
    printf(RED "This text is RED!" COLOR_RESET "\n");
    int not_opened = read_questions(questions, 30, "ques.txt");
    if (not_opened)
        return 0;
    //pass the appropriate number in index of questions keeping in mind the alternates are at odd numbers
    //for reference --> frame(num,questions[2*num],life1,life2,options_selected)
    for (int u = 0; u < 15; u++)
    {
        frame(u, questions[u * 2], 0, 0, 0);
    }
    for (int u = 0; u < 15; u++)
    {
        frame(u, questions[u * 2 + 1], 0, 0, 0);
    }
    //never forget to free memory
    for (int i = 0; i < 30; i++)
    {
        free(questions[i].question);
        free(questions[i].option1);
        free(questions[i].option2);
        free(questions[i].option3);
        free(questions[i].option4);
    }
    return 0;
    //anything below this line in main function isn't doing anything as of now
    int c = 0;
    int pre = 0;
    int locked = 0;

    c = 0;
    c = getchar();
    switch ((c))
    {
    case 49:
        locked = display_question(0, questions[0]);
        pre = 1;
        printf("%d\n", c);
        break;
    case 50:
        locked = display_question(0, questions[0]);
        pre = 2;
        printf("%d\n", c);
        break;
    case 51:
        locked = display_question(0, questions[0]);
        pre = 3;
        printf("%d\n", c);
        break;
    case 52:
        locked = display_question(0, questions[0]);
        pre = 4;
        printf("%d\n", c);
        break;
    default:
        locked = display_question(0, questions[0]);
        pre = 0;
        printf("%d\n", c);
        break;
    }

    if (locked == questions[0].answer)
    {
        printf("correct answer!!!");
    }
    else
    {
        printf("%d %d Better luck next time :(", locked, questions[0].answer);
    }
}

int display_question_locked(int num, struct question questions, int v)
{
    int selected = 0;
    printf("----------------------------------------------------\n");
    printf("question %d-->\n", num + 1);
    printf("question %s\n", questions.question);
    printf("----------------------------------------------------\n");
    switch (v)
    {
    case 1:
        selected = 1;
        printf(" ____________________\n");
        printf("< 1. %s>\t\t", questions.option1);
        printf("2. %s\n", questions.option2);
        printf(" ^^^^^^^^^^^^^^^^^^^^\n");
        printf("3. %s\t\t", questions.option3);
        printf("4. %s\n", questions.option4);
        break;

    case 2:
        selected = 2;
        printf("                      \t\t ____________________\n");
        printf("1. %s\t\t", questions.option1);
        printf("<2. %s>\n", questions.option2);
        printf("                      \t\t ^^^^^^^^^^^^^^^^^^^^\n");
        printf("3. %s\t\t", questions.option3);
        printf("4. %s\n", questions.option4);
        break;

    case 3:
        selected = 3;
        printf("1. %s\t\t", questions.option1);
        printf("2. %s\n", questions.option2);
        printf(" ____________________\n");
        printf("<3. %s>\t\t", questions.option3);
        printf("4. %s\n", questions.option4);
        printf(" ^^^^^^^^^^^^^^^^^^^^\n");
        break;

    case 4:
        selected = 4;
        printf("1. %s\t\t", questions.option1);
        printf("2. %s\n", questions.option2);
        printf("                      \t\t ____________________\n");
        printf("3. %s\t\t", questions.option3);
        printf("<4. %s>\n", questions.option4);
        printf("                      \t\t ^^^^^^^^^^^^^^^^^^^^\n");
        break;

    default:
        selected = 0;
        printf("1. %s\t\t", questions.option1);
        printf("2. %s\n", questions.option2);
        printf("3. %s\t\t", questions.option3);
        printf("4. %s\n", questions.option4);
        break;
    }
    printf("----------------------------------------------------\n");
    return selected;
}
int display_question(int num, struct question questions)
{
    int selected = 0;
    printf("question %d-->\n", num + 1);
    formatques(questions.question, 50, 0);
    printf("\n");
    selected = 1;
    formatopt(questions.option1, questions.option2, 20);
    formatopt(questions.option3, questions.option4, 20);
    return selected;
}

int money_board(int ques_num, char money[15])
{
    char *moneyarr[30] = {"Rs. 5,000", "1 <~> Rs. 5,000",
                          "Rs. 10,000", "2 <~> Rs. 10,000",
                          "Rs. 20,000", "3 <~> Rs. 20,000",
                          "Rs. 40,000", "4 <~> Rs. 40,000",
                          "Rs. 80,000", "5 <~> Rs. 80,000",
                          "Rs. 1,60,000", "6 <~> Rs. 1,60,000",
                          "Rs. 3,20,000", "7 <~> Rs. 3,20,000",
                          "Rs. 3,20,000", "8 <~> Rs. 3,20,000",
                          "Rs. 12,50,000", "9 <~> Rs. 12,50,000",
                          "Rs. 25,00,000", "10 <~> Rs. 25,00,000",
                          "Rs. 50,00,000", "11 <~> Rs. 50,00,000",
                          "Rs. 1,00,00,000", "12 <~> Rs. 1,00,00,000",
                          "Rs. 3,00,00,000", "13 <~> Rs. 3,00,00,000",
                          "Rs. 5,00,00,000", "14 <~> Rs. 5,00,00,000",
                          "Rs. 7,00,00,000", "15 <~> Rs. 7,00,00,000"};
    for (int i = 14; i >= 0; i--)
    {
        moneyfield(ques_num, i, moneyarr, money);
    }
    return 0;
}
//just a helper function for moneyboard
void moneyfield(int ques_num_on, int ques_num_field, char **moneyarr, char *money)
{
    if (ques_num_field == ques_num_on)
    {
        if (ques_num_on == 14)
            printf(" You are HERE!!! -> ");
        else
            QUES_POINTER;
        strcpy(money, moneyarr[ques_num_field * 2]);
    }
    SPACE
    if (ques_num_field == ques_num_on)
    {
        formatques(moneyarr[(ques_num_field * 2) + 1], strlen(moneyarr[(ques_num_field * 2) + 1]), 1);
        printf("\n");
    }
    else
    {
        if (ques_num_on < ques_num_field)
        {
            if (ques_num_field == 2 || ques_num_field == 7 || ques_num_field == 11)
            {
                printf("< %d  <> %s >\n", ques_num_field + 1, moneyarr[ques_num_field * 2]);
            }
            else
            {
                printf("  %d  <> %s\n", ques_num_field + 1, moneyarr[ques_num_field * 2]);
            }
        }
        else
        {
            if (ques_num_field == 2 || ques_num_field == 7 || ques_num_field == 11)
            {
                printf("< %d  </> %s >\n", ques_num_field + 1, moneyarr[ques_num_field * 2]);
            }
            else
            {
                printf("  %d  </> %s\n", ques_num_field + 1, moneyarr[ques_num_field * 2]);
            }
        }
    }
}

//because main questions are even numbered (see ques.txt ) we multiply index of array of structs by 2
int frame(int ques_num, struct question questions, int life1, int life2, int option)
{
    char *money;
    money = (char *)malloc(15 * sizeof(char));
    printf("_____________________________________________________________\n\n");
    money_board(ques_num, money);
    printf("You currently have %s\n", money);
    if (option)
    {
        display_question_locked(ques_num, questions, option);
    }
    else
    {
        display_question(ques_num, questions);
    }
    return 0;
}

//basically fills the array of structure with the values on ques.txt
int read_questions(struct question questions[], size_t len, char ques_file[])
{

    FILE *fp = fopen(ques_file, "r");
    if (!fp)
    {
        printf("Can't open questions source file\n");
        return 1;
    }

    char *buf = malloc(1024);
    int ques_num = 0;
    int field_cnt = 0;
    while (fgets(buf, 1024, fp) != NULL)
    {
        field_cnt = 0;

        if (ques_num == len)
        {
            break;
        }
        char field[1024];
        int field_pos = 0;
        int i = 0;
        do
        {
            field[field_pos++] = buf[i];
            if ((buf[i] == ';' || buf[i] == '\n'))
            {
                field[field_pos - 1] = '\0';
                field_pos = 0;
                switch (field_cnt)
                {
                case 0:
                    strcpy(questions[ques_num].question, field);
                    break;
                case 1:
                    strcpy(questions[ques_num].option1, field);
                    break;
                case 2:
                    strcpy(questions[ques_num].option2, field);
                    break;
                case 3:
                    strcpy(questions[ques_num].option3, field);
                    break;
                case 4:
                    strcpy(questions[ques_num].option4, field);
                    break;
                case 5:
                    questions[ques_num].answer = atoi(field);
                }

                field_cnt++;
            }
        } while (buf[++i]);
        ques_num++;
    }
    fclose(fp);
    free(buf);
    return 0;
}
