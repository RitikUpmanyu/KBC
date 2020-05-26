
#include <stdio.h>

#include <curses.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

/* get a single char from stdin    */











struct question{
    char question[200];
    char option1[200];
    char option2[200];
    char option3[200];
    char option4[200];
    int answer;
};

int display_question(int, struct question questions, int);




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
void clear()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}
int c = 0;
int pre=0;
int locked=0;
while(1){

        c = 0;

        getch();
        c=getch();
        switch((c)) {
        case KEY_UP:
            clear();
            switch(pre){
                case 1:locked=display_question(0, questions[0], 1);break;
                case 2:locked=display_question(0, questions[0], 2);break;
                case 3:locked=display_question(0, questions[0], 1);break;
                case 4:locked=display_question(0, questions[0], 2);break;
                default:display_question(0, questions[0], 1);break;
            }
            pre=1;
            printf("%d\n",c);
            break;
        case KEY_DOWN:
            clear();
            switch(pre){
                case 1:locked=display_question(0, questions[0], 2);break;
                case 2:locked=display_question(0, questions[0], 2);break;
                case 3:locked=display_question(0, questions[0], 3);break;
                case 4:locked=display_question(0, questions[0], 3);break;
                default:display_question(0, questions[0], 2);break;
            }
            pre=2;
            printf("%d\n",c);
            break;
        case KEY_LEFT:
            clear();
            switch(pre){
                case 1:locked=display_question(0, questions[0], 1);break;
                case 2:locked=display_question(0, questions[0], 2);break;
                case 3:locked=display_question(0, questions[0], 2);break;
                case 4:locked=display_question(0, questions[0], 1);break;
                default:display_question(0, questions[0], 2);break;
            }
            pre=3;
            printf("%d\n",c);
            break;
        case KEY_RIGHT:
            clear();
            switch(pre){
                case 1:locked=display_question(0, questions[0], 4);break;
                case 2:locked=display_question(0, questions[0], 3);break;
                case 3:locked=display_question(0, questions[0], 3);break;
                case 4:locked=display_question(0, questions[0], 4);break;
                default:display_question(0, questions[0], 4);break;
            }
            pre=4;
            printf("%d\n",c);
            break;
        case 13:
            if (locked==questions[0].answer){
                printf("correct answer!!!");
            } else{
            printf("%d %d Better luck next time :(",locked,questions[0].answer);}
            break;


        default:
            clear();
            switch(pre){
                case 1:locked=display_question(0, questions[0], 1);break;
                case 2:locked=display_question(0, questions[0], 1);break;
                case 3:locked=display_question(0, questions[0], 4);break;
                case 4:locked=display_question(0, questions[0], 4);break;
                default:locked=display_question(0, questions[0], 1);break;
            }
            pre=0;
            printf("%d\n",c);
            break;
        }

}

    return 0;
}

int display_question(int num,struct question questions,int v){
    int selected=0;
    printf("----------------------------------------------------\n");
    printf("question %d-->\n",num);
    printf("question %s\n",questions.question);
    printf("----------------------------------------------------\n");
    switch(v) {
        case 1:
            selected=1;
            printf(" ____________________\n");
            printf("| 1. %s | \t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf(" ____________________\n");
            printf("3. %s\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
            break;

        case 2:
            selected=3;
            printf("1. %s\t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf(" ____________________\n");
            printf("|3. %s|\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
            printf(" ____________________\n");
            break;

        case 3:
            selected=4;
            printf("1. %s\t\t",questions.option1);
            printf("2. %s\n",questions.option2);
            printf("                      \t\t ____________________\n");
            printf("3. %s\t\t",questions.option3);
            printf("|4. %s|\n",questions.option4);
            printf("                      \t\t ____________________\n");
            break;

        case 4:
            selected=2;
            printf("                      \t\t ____________________\n");
            printf("1. %s\t\t",questions.option1);
            printf("|2. %s|\n",questions.option2);
            printf("                      \t\t ____________________\n");
            printf("3. %s\t\t",questions.option3);
            printf("4. %s\n",questions.option4);
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
