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

typedef struct
{
    char *question;
    char *option1;
    char *option2;
    char *option3;
    char *option4;
    int answer;
}Question;
Question questions[30];


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
        if(ques_num_field!=0)
            strcpy(current_money, moneyarr[(ques_num_field * 2)-2]);
        else
            strcpy(current_money,"Nothing");
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
//function to display options
void display_options(Question questions,int space1, int space2, int selected, int green, int red)
{
    int green1=0,green2=0,red1=0,red2=0;
    char *spc=" ";
    char *option1=questions.option1;
    char *option2=questions.option2;
    char *option3=questions.option3;
    char *option4=questions.option4;
    //making spaces for 50-50
    switch(space1)
    {
        case 1:
            option1=spc;
            break;
        case 2:
            option2=spc;
            break;
        case 3:
            option3=spc;
            break;
        case 4:
            option4=spc;
            break;
    }
    switch(space2)
    {
        case 1:
            option1=spc;
            break;
        case 2:
            option2=spc;
            break;
        case 3:
            option3=spc;
            break;
        case 4:
            option4=spc;
            break;
    }
    if(selected)
    {
        if(selected<=2)
        {
            formatopt(option1,option2,30,selected,0,0);
            formatopt(option3,option4,30,0,0,0);
        }
        else if(selected>2)
        {
            selected-=2;
            formatopt(option1,option2,30,0,0,0);
            formatopt(option3,option4,30,selected,0,0);
        }
    }
    else
    {
        if(green<=2)
        {
            green1=green;
        }else {
            green-=2;
            green2=green;
        }
        if(red<=2)
        {
            red1=red;
        }else {
            red-=2;
            red2=red;
        }
        formatopt(option1,option2,30,0,green1,red1);
        formatopt(option3,option4,30,0,green2,red2);
    }
}
//Used for displaying the question state when the user has entered an answer
//Color coding is done to indicate the seleted option
int display_question(Question questions, int selected, int correct, int wrong, int life1random)
{
    char *spc = "    ";
    printf(YELLOW);
    formatques(questions.question, 71, 0);
    printf("\n");
    printf(COLOR_RESET);
    if(life1random==0)
    {
        display_options(questions,0,0,selected, correct, wrong);
    }
    else
    {
        int space1, space2;
        for(int i=1; i<=4; i++)
        {
            if(i!=questions.answer && i!=life1random)
                space1=i;
        }
        for(int j=1; j<=4; j++)
        {
            if(j!=questions.answer && j!=life1random && j!=space1)
                space2=j;
        }
        display_options(questions,space1,space2,selected, correct, wrong);
    }
    return 0;
}

