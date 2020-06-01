
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SPACE else{printf("                    ");
#define QUES_POINTER printf("   You are here ->  ")
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
// these colors get displayed on gcc so they can be used like this printf(RED "This text is RED!" COLOR_RESET "\n");


struct question{
    char question[200];
    char option1[200];
    char option2[200];
    char option3[200];
    char option4[200];
    int answer;
};
struct question questions[30];
// these four functions are declared here and defined at the end
int display_question(int, struct question);
int display_question_locked(int ,struct question,int );
int money_board(int ,char[15]);
int frame(int,struct question, int, int,int);
int read_questions (struct question [], size_t , char []); //this function takes 3 arguments array of stucts, size of that array, and name of the file where questions are stored

//NOTE - ques.txt currently have 30 questions (even numbered questions are the main ones and odd numbered ones are their alternates for flip the question lifeline
//main function still needs work
int main()
{

int not_opened = read_questions(questions,30,"ques.txt");
if (not_opened)return 0;
//pass the appropriate number in index of questions keeping in mind the alternates are at odd numbers
//for reference --> frame(num,questions[2*num],life1,life2,options_selected)
frame(13,questions[26],0,0,3);
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
    printf("question %d-->\n",num+1);
    printf("question %s\n",questions.question);
    printf("----------------------------------------------------\n");
    switch(v) {
        case 1:
            selected=1;
            printf(" ____________________\n");
            printf("< 1. %s>\t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf(" ^^^^^^^^^^^^^^^^^^^^\n");
            printf("3. %s\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
            break;

        case 2:
            selected=2;
            printf("                      \t\t ____________________\n");
            printf("1. %s\t\t",questions.option1);
            printf("<2. %s>\n",questions.option2);
            printf("                      \t\t ^^^^^^^^^^^^^^^^^^^^\n");
            printf("3. %s\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
            break;


        case 3:
            selected=3;
            printf("1. %s\t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf(" ____________________\n");
            printf("<3. %s>\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
            printf(" ^^^^^^^^^^^^^^^^^^^^\n");
            break;


        case 4:
            selected=4;
            printf("1. %s\t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf("                      \t\t ____________________\n");
            printf("3. %s\t\t",questions.option3);
            printf("<4. %s>\n",questions.option4);
            printf("                      \t\t ^^^^^^^^^^^^^^^^^^^^\n");
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
    printf("question %d-->\n",num+1);
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

//because main questions are even numbered (see ques.txt ) we multiply ques_num by 2
int frame(int ques_num,struct question questions, int life1, int life2,int option){
char money[15];
money_board(ques_num, money);
printf("\nYou currently have %s\n", money);
if(option){
        display_question_locked(ques_num,questions,option);
} else{
     display_question(ques_num,questions);
}
return 0;
}

//basically fills the array of structure with the values on ques.txt
int read_questions (struct question questions[], size_t len, char ques_file[]){

    FILE *fp=fopen(ques_file,"r");
        if (!fp) {
            printf("Can't open questions source file\n");
            return 1;
        }

        char *buf=malloc(1024);
        int ques_num = 0;
        int field_cnt = 0;
        while (fgets(buf, 1024, fp)!=NULL) {
            field_cnt = 0;


            if (ques_num == len) {
                break;
            }
            char field[1024];
            int field_pos =0;
            int i=0;
            do {
                    field[field_pos++] = buf[i];
                    if ((buf[i] == ',' || buf[i] == '\n')) {
                        field[field_pos - 1] = 0;
                        field_pos = 0;
                    switch(field_cnt){
                        case 0:
                            strcpy(questions[ques_num].question,field);
                            break;
                        case 1:
                            strcpy(questions[ques_num].option1,field);
                            break;
                        case 2:
                            strcpy(questions[ques_num].option2,field);
                            break;
                        case 3:
                            strcpy(questions[ques_num].option3,field);
                            break;
                        case 4:
                            strcpy(questions[ques_num].option4,field);
                            break;
                        case 5:
                            questions[ques_num].answer=atoi(field);

                }

                field_cnt++;
            }}while (buf[++i]);
            ques_num++;
        }
        fclose(fp);
        free(buf);
        return 0;
}


