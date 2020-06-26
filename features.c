#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "formatting.c"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
// these colors get displayed on gcc so they can be used like this printf(RED "This text is RED!" COLOR_RESET "\n");
#define SP printf("    ")
#define SPACE                           \
    else                                \
    {                                   \
        printf("                    "); \
    }

#define QUES_POINTER printf("   You are here ->  ")

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

int lifeline1(struct question questions,int quesno, int random)
{
    char *spc = "    ";
    // Printing the question
    printf("question %d-->\n", quesno + 1);
    printf(YELLOW);
    formatques(questions.question, 71, 0);
    printf("\n");
    if(questions.answer==1)
    {
        switch(random)//printing the correct option and a randomly selected one.
        {
        case 2:
            formatopt(questions.option1, questions.option2, 30,0,0,0);
            formatopt(spc, spc, 30,0,0,0);
            break;
        case 3:
            formatopt(questions.option1, spc, 30,0,0,0);
            formatopt(questions.option3, spc, 30,0,0,0);
            break;
        case 4:
            formatopt(questions.option1, spc, 30,0,0,0);
            formatopt(spc, questions.option4, 30,0,0,0);
            break;
        }
    }
    else if(questions.answer==2)
    {
        switch(random)
        {
        case 1:
            formatopt(questions.option1, questions.option2, 30,0,0,0);
            formatopt(spc, spc, 30,0,0,0);
            break;
        case 3:
            formatopt(spc, questions.option2, 30,0,0,0);
            formatopt(questions.option3, spc, 30,0,0,0);
            break;
        case 4:
            formatopt(spc, questions.option2, 30,0,0,0);
            formatopt(spc, questions.option4, 30,0,0,0);
            break;
        }
    }
    else if(questions.answer==3)
    {
        switch(random)
        {
        case 1:
            formatopt(questions.option1, spc, 30,0,0,0);
            formatopt(questions.option3, spc, 30,0,0,0);
            break;
        case 2:
            formatopt(spc, questions.option2, 30,0,0,0);
            formatopt(questions.option3, spc, 30,0,0,0);
            break;
        case 4:
            formatopt(spc, spc, 30,0,0,0);
            formatopt(questions.option3, questions.option4, 30,0,0,0);
            break;
        }
    }
    else
    {
        switch(random)
        {
        case 1:
            formatopt(questions.option1, spc, 30,0,0,0);
            formatopt(spc, questions.option4, 30,0,0,0);
            break;
        case 2:
            formatopt(spc, questions.option2, 30,0,0,0);
            formatopt(spc, questions.option4, 30,0,0,0);
            break;
        case 3:
            formatopt(spc, spc, 30,0,0,0);
            formatopt(questions.option3, questions.option4, 30,0,0,0);
            break;
        }
    }
    return 0;
}
int display_question(int num, struct question questions)//used for displaying the question and it's options
{
    printf("question %d-->\n", num + 1);
    printf(YELLOW);
    formatques(questions.question, 71, 0);
    printf("\n");
    printf(COLOR_RESET MAGENTA);
    formatopt(questions.option1, questions.option2, 30,0,0,0);
    formatopt(questions.option3, questions.option4, 30,0,0,0);
    printf(COLOR_RESET);
    return 0;
}

//just a helper function for moneyboard
void moneyfield(int ques_num_on, int ques_num_field, char **moneyarr, char *money,char *current_money)
{
    if (ques_num_field == ques_num_on)
    {
        if (ques_num_on == 14)
            printf(" You are HERE!!! -> ");
        else
            QUES_POINTER;
        strcpy(money, moneyarr[ques_num_field * 2]);
        if(ques_num_field!=0)strcpy(current_money, moneyarr[(ques_num_field * 2)-2]);
        else strcpy(current_money,"Nothing");
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
                printf("< %-2d  <>  %s >\n",ques_num_field + 1, moneyarr[ques_num_field * 2]);
            }
            else
            {
                printf("  %-2d  <>  %s\n",ques_num_field + 1, moneyarr[ques_num_field * 2]);
            }
        }
        else
        {
            if (ques_num_field == 2 || ques_num_field == 7 || ques_num_field == 11)
            {
                printf("< %-2d  </>  %s >\n",ques_num_field + 1, moneyarr[ques_num_field * 2]);
            }
            else
            {
                printf("  %-2d  </>  %s\n",ques_num_field + 1, moneyarr[ques_num_field * 2]);
            }
        }
    }
}

//used for printing the money board and the postion of the player at the prize amount.
int money_board(int ques_num, char money[15],char current_money[15])
{
    char *moneyarr[30] = {"Rs. 5,000", "1   <~> Rs. 5,000",
                          "Rs. 10,000", "2   <~> Rs. 10,000",
                          "Rs. 20,000", "3   <~> Rs. 20,000",
                          "Rs. 40,000", "4   <~> Rs. 40,000",
                          "Rs. 80,000", "5   <~> Rs. 80,000",
                          "Rs. 1,60,000", "6   <~> Rs. 1,60,000",
                          "Rs. 3,20,000", "7   <~> Rs. 3,20,000",
                          "Rs. 6,40,000", "8   <~> Rs. 6,40,000",
                          "Rs. 12,50,000", "9   <~> Rs. 12,50,000",
                          "Rs. 25,00,000", "10  <~> Rs. 25,00,000",
                          "Rs. 50,00,000", "11  <~> Rs. 50,00,000",
                          "Rs. 1,00,00,000", "12  <~> Rs. 1,00,00,000",
                          "Rs. 3,00,00,000", "13  <~> Rs. 3,00,00,000",
                          "Rs. 5,00,00,000", "14  <~> Rs. 5,00,00,000",
                          "Rs. 7,00,00,000", "15  <~> Rs. 7,00,00,000"
                         };
    for (int i = 14; i >= 0; i--)
    {
        moneyfield(ques_num, i, moneyarr, money, current_money);
    }
    return 0;
}

//Used for displaying the question state when the user has entered an answer
//Color coding is done to indicate the seleted option
//Switch conditions are used to facilitate the selecting functionality when 50-50 lifeline is taken
int display_question_locked(int num, struct question questions, int selected, int correct, int wrong, int life1random)
{
    char *spc = "    ";
    printf("question %d-->\n", num + 1);
    printf(YELLOW);
    formatques(questions.question, 71, 0);
    printf("\n");
    printf(COLOR_RESET);
    if(life1random==0)
    {
        if(correct==0&&wrong==0)
        {
            if (selected==1||selected==2)
            {
                formatopt(questions.option1, questions.option2, 30, selected,0,0);
            }
            else
                formatopt(questions.option1, questions.option2, 30,0,0,0);
            if (selected==3||selected==4)
            {
                selected-=2;
                formatopt(questions.option3, questions.option4, 30,selected,0,0);
            }
            else
                formatopt(questions.option3, questions.option4, 30,0,0,0);
        }
        else
        {
            if (correct<=2)
            {
                if(wrong<=2)
                {
                    formatopt(questions.option1, questions.option2, 30,0,correct,wrong);
                    formatopt(questions.option3, questions.option4, 30,0,0,0);
                }
                else
                {
                    formatopt(questions.option1, questions.option2, 30,0,correct,0);
                    formatopt(questions.option3, questions.option4, 30,0,0,wrong-2);
                }
            }
            else
            {
                if(wrong<=2)
                {
                    formatopt(questions.option1, questions.option2, 30,0,0,wrong);
                    formatopt(questions.option3, questions.option4, 30,0,correct-2,0);
                }
                else
                {
                    formatopt(questions.option1, questions.option2, 30,0,0,0);
                    formatopt(questions.option3, questions.option4, 30,0,correct-2,wrong-2);
                }
            }
        }
        printf(COLOR_RESET);
    }
    else
    {
        if(correct==0&&wrong==0)
        {
            if(questions.answer==1)
            {
                switch(life1random)
                {
                case 2:
                    if(selected==questions.answer)
                    {
                        formatopt(questions.option1, questions.option2, 30,selected,0,0);
                        formatopt(spc, spc, 30,0,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(questions.option1, questions.option2, 30,selected,0,0);
                        formatopt(spc, spc, 30,0,0,0);
                    }
                    break;
                case 3:
                    if(selected==questions.answer)
                    {
                        formatopt(questions.option1, spc, 30,selected,0,0);
                        formatopt(questions.option3, spc, 30,0,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(questions.option1, spc, 30,0,0,0);
                        formatopt(questions.option3, spc, 30,selected-2,0,0);
                    }
                    break;

                case 4:
                    if(selected==questions.answer)
                    {
                        formatopt(questions.option1, spc, 30,selected,0,0);
                        formatopt(spc, questions.option4, 30,0,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(questions.option1, spc, 30,0,0,0);
                        formatopt(spc, questions.option4, 30,selected-2,0,0);
                    }
                    break;
                }
            }
            else if(questions.answer==2)
            {
                switch(life1random)
                {
                case 1:
                    if(selected==questions.answer)
                    {
                        formatopt(questions.option1, questions.option2, 30,selected,0,0);
                        formatopt(spc, spc, 30,0,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(questions.option1, questions.option2, 30,selected,0,0);
                        formatopt(spc, spc, 30,0,0,0);
                    }
                    break;
                case 3:
                    if(selected==questions.answer)
                    {
                        formatopt(spc, questions.option2, 30,selected,0,0);
                        formatopt(questions.option3, spc, 30,0,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(spc, questions.option2, 30,0,0,0);
                        formatopt(questions.option3, spc, 30,selected-2,0,0);
                    }
                    break;

                case 4:
                    if(selected==questions.answer)
                    {
                        formatopt(spc, questions.option2, 30,selected,0,0);
                        formatopt(spc, questions.option4, 30,0,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(spc, questions.option2, 30,0,0,0);
                        formatopt(spc, questions.option4, 30,selected-2,0,0);
                    }
                    break;
                }
            }
            else if(questions.answer==3)
            {
                switch(life1random)
                {
                case 1:
                    if(selected==questions.answer)
                    {
                        formatopt(questions.option1, spc, 30,0,0,0);
                        formatopt(questions.option3, spc, 30,selected-2,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(questions.option1, spc, 30,selected,0,0);
                        formatopt(questions.option3, spc, 30,0,0,0);
                    }
                    break;
                case 2:
                    if(selected==questions.answer)
                    {
                        formatopt(spc, questions.option2, 30,0,0,0);
                        formatopt(questions.option3, spc, 30,selected-2,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(spc, questions.option2, 30,selected,0,0);
                        formatopt(questions.option3, spc, 30,0,0,0);
                    }
                    break;

                case 4:
                    if(selected==questions.answer)
                    {
                        formatopt(spc, spc, 30,0,0,0);
                        formatopt(questions.option3, questions.option4, 30,selected-2,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(spc, spc, 30,0,0,0);
                        formatopt(questions.option3, questions.option4, 30,selected-2,0,0);
                    }
                    break;
                }
            }
            else
            {
                switch(life1random)
                {
                case 1:
                    if(selected==questions.answer)
                    {
                        formatopt(questions.option1, spc, 30,0,0,0);
                        formatopt(spc, questions.option4, 30,selected-2,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(questions.option1, spc, 30,selected,0,0);
                        formatopt(spc, questions.option4, 30,0,0,0);
                    }
                    break;
                case 2:
                    if(selected==questions.answer)
                    {
                        formatopt(spc, questions.option2, 30,0,0,0);
                        formatopt(spc, questions.option4, 30,selected-2,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(spc, questions.option2, 30,selected,0,0);
                        formatopt(spc, questions.option4, 30,0,0,0);
                    }
                    break;

                case 3:
                    if(selected==questions.answer)
                    {
                        formatopt(spc, spc, 30,0,0,0);
                        formatopt(questions.option3, questions.option4, 30,selected-2,0,0);
                    }
                    else if (selected==life1random)
                    {
                        formatopt(spc, spc, 30,0,0,0);
                        formatopt(questions.option3, questions.option4, 30,selected-2,0,0);
                    }
                    break;
                }
            }
        }
        else
        {
            if(questions.answer==1)
            {
                switch(life1random)
                {
                case 2:
                    if(wrong)
                    {
                        formatopt(questions.option1, questions.option2, 30,0,correct,wrong);
                        formatopt(spc, spc, 30,0,0,0);
                    }
                    else
                    {
                        formatopt(questions.option1, questions.option2, 30,0,correct,0);
                        formatopt(spc, spc, 30,0,0,0);
                    }
                    break;
                case 3:
                    if(wrong)
                    {
                        formatopt(questions.option1, spc, 30,0,correct,0);
                        formatopt(questions.option3, spc, 30,0,0,wrong-2);
                    }
                    else
                    {
                        formatopt(questions.option1, spc, 30,correct,0,0);
                        formatopt(questions.option3, spc, 30,0,0,0);
                    }
                    break;

                case 4:
                    if(wrong)
                    {
                        formatopt(questions.option1, spc, 30,0,correct,0);
                        formatopt(spc, questions.option4, 30,0,0,wrong-2);
                    }
                    else
                    {
                        formatopt(questions.option1, spc, 30,0,correct,0);
                        formatopt(spc, questions.option4, 30,0,0,0);
                    }
                    break;
                }
            }
            else if(questions.answer==2)
            {
                switch(life1random)
                {
                case 1:
                    if(wrong)
                    {
                        formatopt(questions.option1, questions.option2, 30,0,correct,wrong);
                        formatopt(spc, spc, 30,0,0,0);
                    }
                    else
                    {
                        formatopt(questions.option1, questions.option2, 30,0,correct,0);
                        formatopt(spc, spc, 30,0,0,0);
                    }
                    break;
                case 3:
                    if(wrong)
                    {
                        formatopt(spc, questions.option2, 30,0,correct,0);
                        formatopt(questions.option3, spc, 30,0,0,wrong-2);
                    }
                    else
                    {
                        formatopt(spc, questions.option2, 30,0,correct,0);
                        formatopt(questions.option3, spc, 30,0,0,0);
                    }
                    break;

                case 4:
                    if(wrong)
                    {
                        formatopt(spc, questions.option2, 30,0,correct,0);
                        formatopt(spc, questions.option4, 30,0,0,wrong-2);
                    }
                    else
                    {
                        formatopt(spc, questions.option2, 30,0,correct,0);
                        formatopt(spc, questions.option4, 30,0,0,0);
                    }
                    break;
                }
            }
            else if(questions.answer==3)
            {
                switch(life1random)
                {
                case 1:
                    if(wrong)
                    {
                        formatopt(questions.option1, spc, 30,0,0,wrong);
                        formatopt(questions.option3, spc, 30,0,correct-2,0);
                    }
                    else
                    {
                        formatopt(questions.option1, spc, 30,0,0,0);
                        formatopt(questions.option3, spc, 30,0,correct-2,0);
                    }
                    break;
                case 2:
                    if(wrong)
                    {
                        formatopt(spc, questions.option2, 30,0,0,wrong);
                        formatopt(questions.option3, spc, 30,0,correct-2,0);
                    }
                    else
                    {
                        formatopt(spc, questions.option2, 30,0,0,0);
                        formatopt(questions.option3, spc, 30,0,correct-2,0);
                    }
                    break;

                case 4:
                    if(wrong)
                    {
                        formatopt(spc, spc, 30,0,0,0);
                        formatopt(questions.option3, questions.option4, 30,0,correct-2,wrong-2);
                    }
                    else
                    {
                        formatopt(spc, spc, 30,0,0,0);
                        formatopt(questions.option3, questions.option4, 30,0,correct-2,0);
                    }
                    break;
                }
            }
            else
            {
                switch(life1random)
                {
                case 1:
                    if(wrong)
                    {
                        formatopt(questions.option1, spc, 30,0,0,wrong);
                        formatopt(spc, questions.option4, 30,0,correct-2,0);
                    }
                    else
                    {
                        formatopt(questions.option1, spc, 30,0,0,0);
                        formatopt(spc, questions.option4, 30,0,correct-2,0);
                    }
                    break;
                case 2:
                    if(wrong)
                    {
                        formatopt(spc, questions.option2, 30,0,0,wrong);
                        formatopt(spc, questions.option4, 30,0,correct-2,0);
                    }
                    else
                    {
                        formatopt(spc, questions.option2, 30,0,0,0);
                        formatopt(spc, questions.option4, 30,0,correct-2,0);
                    }
                    break;

                case 3:
                    if(wrong)
                    {
                        formatopt(spc, spc, 30,0,0,0);
                        formatopt(questions.option3, questions.option4, 30,0,correct-2,wrong-2);
                    }
                    else
                    {
                        formatopt(spc, spc, 30,0,0,0);
                        formatopt(questions.option3, questions.option4, 30,0,correct-2,0);
                    }
                    break;
                }
            }
        }
        printf(COLOR_RESET);
    }
    return 0;
}