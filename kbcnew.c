#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "features.c"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
#define BoldBlue "\x1b[1;34m"
// these colors get displayed on gcc so they can be used like this printf(RED "This text is RED!" COLOR_RESET "\n");
#define SP printf("    ")
//////////////////////SCREEN CLEARING LOGIC//////////////////////////
#if defined(_WIN32) || defined(_WIN64)
const char* os = "win";
#else
#ifdef __linux
const char* os = "linux";
#else
#if defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
const char* os = "linux";
#else
const char* os = "unknown";
#endif
#endif
#endif // defined
// To use time library of C
#include <time.h>

//provide agrument in miliseconds
void delay(int trigger)
{
    int msec = 0; /* 10ms */
    clock_t before = clock();

    do
    {
        /*
         * Do something to busy the CPU just here while you drink a coffee
         * Be sure this code will not take more than `trigger` ms
         */

        clock_t difference = clock() - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
    }
    while ( msec < trigger );
    return;
}
//function to clear the terminal
void clear_screen()
{
    if(os=="win")
    {
        system("cls");
    }
    else if(os=="linux")
    {
        system("clear");
    }
    else
    {
        printf("\n___________________________________________________________________________________________________\n");
    }
}
 
// these four functions are declared here and defined at the end
int gameloop();
int display_question(int, struct question);
int display_question_locked(int, struct question,int,int,int, int);
int money_board(int, char[15],char[15]);
char* frame(int, struct question, int, int, int,int,int,int,int);
int read_questions(struct question[], size_t, char[]); //this function takes 3 arguments array of stucts, size of that array, and name of the file where questions are stored
void moneyfield(int, int, char **, char *, char *);            // this is a helper function for moneyboard
int formattext(char *, int);
int formattextq(char *str, int width, int, int, int, int);
void linecount(char *str, int width, int *num_lines);
void formatques(char *str, int width, int);
int formattexto(char *str1, char *str2, int width, int selected, int correct, int wrong);
void formatopt(char *str1, char *str2, int width, int selected, int correct, int wrong);
int lifeline1(struct question,int quesno, int random);
/*int user_input(int);*/
//NOTE - ques.txt currently have 30 questions (even numbered questions are the main ones and odd numbered ones are their alternates for flip the question lifeline)
//main function still needs work
int main()
{
    gameloop();
    //about formatopt last three arguments-> correct and wrong should by default be 0, they are for displaying red and green colors,
    // if you want first option green and second red use correct =1, wrong =2 and vice versa,CORRECT AND WRONG SHOULD NEVER BE SAME
    //more examples if you want second option red and first normal use wrong =2 and correct =0,if you want first option green and second normal use wrong =0 and correct =1.
    //anything below this line in main function isn't doing anything as of now
    return 0;
}

int gameloop()
{
//getting rid of segmentation fault-->allocate memory
//getting rid of segmentation fault-->allocate memory
    for (int i = 0; i < 30; i++)
    {
        questions[i].question = malloc(500);
        questions[i].option1 = malloc(500);
        questions[i].option2 = malloc(500);
        questions[i].option3 = malloc(500);
        questions[i].option4 = malloc(500);
    }
    int not_opened = read_questions(questions, 30, "ques.txt");
    if (not_opened)
        return 0;
    //pass the appropriate number in index of questions keeping in mind the alternates are at odd numbers
    //for reference --> frame(num,questions[2*num],life1,life1_check,life2_check,options_selected)
    int u=0;
    int life1=0, correct=0, wrong=0;
    int life1_check=1, life2_check=1;
    int ques_num=2*u;
    int iterator=-1;//for checking that whether we are on next question or just continuing the loop;
    int random;
    while (u < 15)
    {
        //argument after life1_check is for life2_check for telling frame that user have that lifeline available or not
        //argument after that is for selected?locked
        //just to see how everything looks(testing)
        //printing every possible case
        //NOTE if selected != 0, correct and wrong must be 0 and if correct or wrong != 0 selected must be 0
        //NOTE correct and wrong must not be same , otherwise nothing will be printed
        iterator++;
        if(iterator==u){
            life1=0;
            do
            {
                srand(time(0));
                random=(rand()%(4))+1;
            }while(random==questions[ques_num].answer);
            }
        char *money=frame(u,questions[ques_num],life1,life1_check,life2_check,0,correct,wrong,random);
        //delay(500);
        //clear_screen();
        int locked=0;
        printf("Enter A/a/B/b/C/c/D/d to choose! ");
        if(life1_check){
            printf("Enter [l]/[L] for 50:50 ");}
        if(life2_check){
            printf("Enter [f]/[F] for Flip-The-Question");}
        printf("\n");
        char ans[1024];
        time_t start, end;
        int seconds;
        if(iterator==u)
        {
            start = time (NULL);
        }
        fgets(ans, 1024, stdin);
        switch (ans[0])
        {
        case 97://for small letters also -a
        case 65: //A
            locked = 1;
            break;
        case 98: //b
        case 66: //B
            locked = 2;
            break;
        case 99: //c
        case 67: //C
            locked = 3;
            break;
        case 100: //D
        case 68: //d
            locked = 4;
            break;
        case 76: //l
        case 108: //L
            clear_screen();
            if(life1_check==1)
            {
                life1=1;
                life1_check=0;
                continue;
            }
            else
            {
                printf("You don't have 50-50 lifeline left :/\n");
                delay(500);
                continue;
                break;
            }
        case 70: //f
        case 102: //F
            clear_screen();
            if(life2_check==1)
            {
                ques_num=2*u+1;//gets the odd numbered(alternate question)
                life2_check=0;
                continue;
            }
            else
            {
                printf("You don't have flip the question lifeline left.\n");
                delay(500);
                continue;
                break;
            }
            continue;
            break;
        case 81: //q
        case 113: //Q
            locked=999;
            if(u>1)printf("Congratulations!! ");
            printf("You Won %s\n",money);
            break;
        default:
            printf("INVALID INPUT\n");
            delay(500);
            continue;
        }
        if(life1 && (locked!=random && locked!=questions[ques_num].answer)){
        printf("Please choose only from displayed options\n");
        delay(1000);
        continue;
        }
        clear_screen();
        frame(u,questions[ques_num],life1,life1_check,life2_check,locked,correct,wrong,random);
        printf("Lock kar diya jaye? Are you sure? enter [Y]/[y] to confirm or any other key to choose again.");
        char confirm[1024];
        fgets(confirm, 1024, stdin);//Takes input for locking the answer

        switch(confirm[0])
        {
            case 121: //Y
            case 89:  //y
                clear_screen();
                break;
            default:
                clear_screen();
                continue;
        }
        end = time (NULL);
        seconds = end - start;
        //timer
        if(u<4)
        {
            if (seconds > 30)
            {
                printf ("Sorry, you were too slow.\n");
                if(u+1<3)
                    printf("You won Nothing\n");
                else if(u+1<8)
                    printf("You won Rs. 20,000\n");
                break;
            }
        }
        if(locked==999){
            break;
        }
        if(locked==0)
        {
            continue;
        }
        if (locked == questions[ques_num].answer)
        {
            clear_screen();
            frame(u,questions[ques_num],life1,life1_check,life2_check,0,locked,wrong,random);
            printf("CORRECT answer!!!\n");
            delay(1500);
        }
        else
        {
            clear_screen();
            frame(u,questions[ques_num],life1,life1_check,life2_check,0,questions[ques_num].answer,locked,random);
            printf("Better luck next time , You won ");
            if(u+1<3)
                printf("Nothing\n");
            else if(u+1<8)
                printf("Rs. 20,000\n");
            else if(u+1<12)
                printf("Rs. 3,20,000\n");
            else
                printf("Rs. 1,00,00,000\n");
            delay(1500);
            break;
        }
        u++;
        iterator=u-1;
        ques_num=2*u;
        clear_screen();
    }
    /////////////////////////////////////////////////////////////////////////////////////

    //never forget to free memory
    char again[1024];
    while(1)
    {   
        if(u==15){
        printf("CONGRATULATIONS YOU WON 7 CRORE !!!\n");}
        printf("press [p]/[P] to play again [q]/[Q] to quit\n");
        fgets(again, 1024, stdin);
        if(again[0]==80 || again[0]==112)
        {
            gameloop();
        }
        else if(again[0]==81 || again[0]==113)
        {
            for (int i = 0; i < 30; i++)
            {
                free(questions[i].question);
                free(questions[i].option1);
                free(questions[i].option2);
                free(questions[i].option3);
                free(questions[i].option4);
                questions[i].question=NULL;
                questions[i].option1=NULL;
                questions[i].option2=NULL;
                questions[i].option3=NULL;
                questions[i].option4=NULL;
            }
            return 0;
        }
    }
}

//because main questions are even numbered (see ques.txt ) we multiply index of array of structs by 2
char* frame(int ques_num, struct question questions, int life1,int life1_check, int life2_check, int option_selected, int correct, int wrong, int random)
{
    char *money;
    char *current_money;
    money = (char *)malloc(15 * sizeof(char));
    current_money = (char *)malloc(15 * sizeof(char));
    money_board(ques_num, money, current_money);
    if(life1_check==0||life2_check==0)
    {
        if(life2_check==1)
        {
            printf("\n LIFELINE REMAINING...  /<--\\ \n");//change this for styling
            printf("                        \\-->/ \n");
        }
        if(life1_check==1)
        {
            printf("\n LIFELINE REMAINING...  /50\\\n");//change this for styling
            printf("                        \\50/\n");
        }
    }
    else
    {
        printf("\n LIFELINES REMAINING... /50 \\ /<--\\ \n");//change this for styling
        printf("                        \\ 50/ \\-->/ \n");
    }
    printf("This question is for %s\n", money);
    printf("You currently have %s\n", current_money);
    printf("If you lose you will get ");
    if(ques_num<3)
        printf("Nothing\n");
    else if(ques_num<8)
        printf("Rs. 20,000\n");
    else if(ques_num<12)
        printf("Rs. 3,20,000\n");
    else
        printf("Rs. 1,00,00,000\n");
    if(life1==1)
    {
        if(option_selected==0&&correct==0&&wrong==0){
            lifeline1(questions, ques_num, random);}
        else{
            display_question_locked(ques_num, questions, option_selected, correct, wrong, random);
        }
    }
    else
    {
        if (option_selected||correct||wrong)
        {
            display_question_locked(ques_num, questions, option_selected, correct, wrong, 0);
        }
        else
        {
            display_question(ques_num, questions);
        }
    }
    if(ques_num<4&&correct==0)
    {
        printf("You have 30s to answer this question!!\n");
    }
    return current_money;
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
        }
        while (buf[++i]);
        ques_num++;
    }
    fclose(fp);
    free(buf);
    return 0;
}