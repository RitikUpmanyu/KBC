
#include <stdio.h>
#include <string.h>
#define SPACE else{printf("                    ");
#define QUES_POINTER printf("   You are here ->  ")

struct question{
    char question[200];
    char option1[200];
    char option2[200];
    char option3[200];
    char option4[200];
    int answer;
};

int display_question(int, struct question questions);




int main()
{


struct question questions[15]={
    {
     "who was what and when q1?","this is option 1","this is option 2","this is option 3","this is option 4",1
 },{
     "who was what and when q2?","this is option 1","this is option 2","this is option 3","this is option 4",2
 },{
     "who was what and when q3?","this is option 1","this is option 2","this is option 3","this is option 4",3
 },{
     "who was what and when q4?","this is option 1","this is option 2","this is option 3","this is option 4",4
 },{
     "who was what and when q5?","this is option 1","this is option 2","this is option 3","this is option 4",1
 },{
     "who was what and when q6?","this is option 1","this is option 2","this is option 3","this is option 4",2
 },{
     "who was what and when q7?","this is option 1","this is option 2","this is option 3","this is option 4",3
 },{
     "who was what and when q8?","this is option 1","this is option 2","this is option 3","this is option 4",4
 },{
     "who was what and when q9?","this is option 1","this is option 2","this is option 3","this is option 4",1
 },{
     "who was what and when q10?","this is option 1","this is option 2","this is option 3","this is option 4",2
 },{
     "who was what and when q11?","this is option 1","this is option 2","this is option 3","this is option 4",3
 },{
     "who was what and when q12?","this is option 1","this is option 2","this is option 3","this is option 4",4
 },{
     "who was what and when q13?","this is option 1","this is option 2","this is option 3","this is option 4",1
 },{
     "who was what and when q14?","this is option 1","this is option 2","this is option 3","this is option 4",1
 },{
     "who was what and when q15?","this is option 1","this is option 2","this is option 3","this is option 4",3
 }
};
char money[15];
money_board(3, money);
int c = 0;
int pre=0;
int locked=0;

        c = 0;
        c=getchar();
        switch((c)) {
        case 49:
            locked=display_question(0, questions[0]);
            pre=1;
            printf("%d\n",c);
            break;
        case 50:
            locked=display_question(0, questions[0]);
            pre=2;
            printf("%d\n",c);
            break;
        case 51:
            locked=display_question(0, questions[0]);
            pre=3;
            printf("%d\n",c);
            break;
        case 52:
            locked=display_question(0, questions[0]);
            pre=4;
            printf("%d\n",c);
            break;
        default:
            locked=display_question(0, questions[0]);
            pre=0;
            printf("%d\n",c);
            break;
        }

    if (locked==questions[0].answer){
                printf("correct answer!!!");
            } else{
            printf("%d %d Better luck next time :(",locked,questions[0].answer);}
    return 0;
}

int display_question_locked(int num,struct question questions,int v){
    int selected=0;
    printf("----------------------------------------------------\n");
    printf("question %d-->\n",num);
    printf("question %s\n",questions.question);
    printf("----------------------------------------------------\n");
    switch(v) {
        case 1:
            selected=1;
            printf(" ____________________\n");
            printf("| 1. %s|\t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf(" ____________________\n");
            printf("3. %s\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
            break;

        case 2:
            selected=2;
            printf("                      \t\t ____________________\n");
            printf("1. %s\t\t",questions.option1);
            printf("|2. %s|\n",questions.option2);
            printf("                      \t\t ____________________\n");
            printf("3. %s\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
            break;


        case 3:
            selected=3;
            printf("1. %s\t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf(" ____________________\n");
            printf("|3. %s|\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
            printf(" ____________________\n");
            break;


        case 4:
            selected=4;
            printf("1. %s\t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf("                      \t\t ____________________\n");
            printf("3. %s\t\t",questions.option3);
            printf("|4. %s|\n",questions.option4);
            printf("                      \t\t ____________________\n");
            break;


        default:
            selected=0;
            printf("1. %s\t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf("3. %s\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
            break;

        }
    printf("----------------------------------------------------\n");
    return selected;
}
int display_question(int num,struct question questions){
    int selected=0;
    printf("----------------------------------------------------\n");
    printf("question %d-->\n",num);
    printf("question %s\n",questions.question);
    printf("----------------------------------------------------\n");
            selected=1;
            printf("1. %s\t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf("3. %s\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
    printf("----------------------------------------------------\n");
    return selected;
}

int money_board(int ques_num,char money[15]){
    if (ques_num==15){printf(" You are HERE!!! -> ");strcpy(money, "Rs. 7,00,00,000");}SPACE}
    printf("< 15 <> Rs. 7,00,00,000 >\n");
    if (ques_num==14){QUES_POINTER;strcpy(money, "Rs. 5,00,00,000");}SPACE}
    printf("  14 <> Rs. 5,00,00,000\n");
    if (ques_num==13){QUES_POINTER;strcpy(money, "Rs. 3,00,00,000");}SPACE}
    printf("  13 <> Rs. 3,00,00,000\n");
    if (ques_num==12){QUES_POINTER;strcpy(money, "Rs. 1,00,00,000");}SPACE}
    printf("< 12 <> Rs. 1,00,00,000 >\n");
    if (ques_num==11){QUES_POINTER;strcpy(money, "Rs. 50,00,000");}SPACE}
    printf("  11 <> Rs. 50,00,000\n");
    if (ques_num==10){QUES_POINTER;strcpy(money, "Rs. 25,00,000");}SPACE}
    printf("  10 <> Rs. 25,00,000\n");
    if (ques_num==9){QUES_POINTER;strcpy(money, "Rs. 12,50,000");}SPACE}
    printf("  9  <> Rs. 12,50,000\n");
    if (ques_num==8){QUES_POINTER;strcpy(money, "Rs. 6,40,000");}SPACE}
    printf("< 8  <> Rs. 6,40,000 >\n");
    if (ques_num==7){QUES_POINTER;strcpy(money, "Rs. 3,20,000");}SPACE}
    printf("  7  <> Rs. 3,20,000\n");
    if (ques_num==6){QUES_POINTER;strcpy(money, "Rs. 1,60,000");}SPACE}
    printf("  6  <> Rs. 1,60,000\n");
    if (ques_num==5){QUES_POINTER;strcpy(money, "Rs. 80,000");}SPACE}
    printf("  5  <> Rs. 80,000\n");
    if (ques_num==4){QUES_POINTER;strcpy(money, "Rs. 40,000");}SPACE}
    printf("  4  <> Rs. 40,000\n");
    if (ques_num==3){QUES_POINTER;strcpy(money, "Rs. 20,000");}SPACE}
    printf("< 3  <> Rs. 20,000 >\n");
    if (ques_num==2){QUES_POINTER;strcpy(money, "Rs. 10,000");}SPACE}
    printf("  2  <> Rs. 10,000\n");
    if (ques_num==1){QUES_POINTER;strcpy(money, "Rs. 5,000");}SPACE}
    printf("  1  <> Rs. 5,000\n");
    return 0;
}
