#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "features.c"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
// these colors get displayed on console so they can be used like this printf(RED "This text is RED!" COLOR_RESET "\n");
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
#endif
#include <time.h> //for timer and delay
// these functions are declared here and defined at the end or in different files
void clear_screen();
void delay(int trigger);
int count_gameplay(int,int);
int gameloop(int count);
char* frame(int, Question, int, int, int,int,int,int,int, char *);
int msg_output(int timer,int ques_num,int correct,int wrong,int exit,int quit,char *money, char *current_money);
int lifeline1(int *life1, int *life1check);
int lifeline2(int *life2check, int count, int *ques_index, int ques_num);
int read_questions(Question[], size_t, char[]); //this function takes 3 arguments array of stucts, size of that array, and name of the file where questions are stored
//these functions are inside features.c here only for reference
void display_options(Question questions,int space1, int space2, int selected, int green, int red);
int money_board(int, char[15],char[15]);
void moneyfield(int, int, char **, char *, char *);            // this is a helper function for moneyboard
//these functions are inside formatting.c here only for reference
int formattext(char *, int);
int formattextq(char *str, int width, int, int, int, int);
void linecount(char *str, int width, int *num_lines);
void formatques(char *str, int width, int);
int formattexto(char *str1, char *str2, int width, int selected, int correct, int wrong);
void formatopt(char *str1, char *str2, int width, int selected, int correct, int wrong);//about formatopt last three arguments-> correct and wrong should by default be 0, they are for displaying red and green colors,
// if you want first option green and second red use correct =1, wrong =2 and vice versa,CORRECT AND WRONG SHOULD NEVER BE SAME
//NOTE - ques.txt currently have 30 questions (even numbered questions are the main ones and odd numbered ones are their alternates for flip the question lifeline)
//main function still needs work
int main()
{
    int i;
    printf(YELLOW);
    printf("//////////////////////////////////////////////////////////////////////\n");
    printf(COLOR_RESET);
    char *ques_money[15]={"Q1--> Rs. 5,000",
                          "Q2--> Rs. 10,000",
                          "Level-1 <Q3--> Rs. 20,000>",
                          "Q4--> Rs. 40,000",
                          "Q5--> Rs. 80,000",
                          "Q6--> Rs. 1,60,000",
                          "Q7--> Rs. 3,20,000",
                          "Level-2 <Q8--> Rs. 6,40,000>",
                          "Q9--> Rs. 12,50,000",
                          "Q10--> Rs. 25,00,000",
                          "Q11--> Rs. 50,00,000",
                          "Level-3 <Q12--> Rs. 1,00,00,000>",
                          "Q13--> Rs. 3,00,00,000",
                          "Q14--> Rs. 5,00,00,000",
                          "Q15--> Rs. 7,00,00,000",};
    for(i=0;i<15;i++)
    {
        if(i==2)
        {
            printf("         ");
            printf("%s\n",ques_money[i]);
        }
        else if(i==7)
        {
            printf("         ");
            printf("%s\n",ques_money[i]);
        }
        else if(i==11)
        {
            printf("         ");
            printf("%s\n",ques_money[i]);
        }
        else
        {
            printf("                  ");
            printf("%s\n",ques_money[i]);
        }
    }
    printf(GREEN"Life lines: "COLOR_RESET);
    printf(YELLOW);
    printf("            50-50 \n");
    printf("            Flip the question\n"COLOR_RESET);
    printf(CYAN"Press any key then press enter to start the game\n"COLOR_RESET);
    scanf("%d",&i);
    clear_screen();
    int count=count_gameplay(0,0);
    gameloop(count);//main gameloop
    return 0;
}
int gameloop(int count)
{
//allocate memory for preventing segmentation fault
    for (int i = 0; i < 30; i++)
    {
        questions[i].question = malloc(500);
        questions[i].option1 = malloc(500);
        questions[i].option2 = malloc(500);
        questions[i].option3 = malloc(500);
        questions[i].option4 = malloc(500);
    }
    //reading questions
    int not_opened = read_questions(questions, 30, "questions.txt");
    if (not_opened)
    {
        printf(RED"questions.txt not accessible\n"COLOR_RESET);
        return 0;
    }
    //pass the appropriate number in index of questions keeping in mind the alternates are at odd numbers
    //for reference --> frame(num,questions[2*num],life1,life1_check,life2_check,options_selected)
    int ques_num=0;
    int ques_index;
    int *ques_index_ptr=&ques_index;
    //life1 is  50-50 and life2 is flip-the-question
    int life1=0, correct=0, wrong=0;
    int life1_check=1, life2_check=1;
    int *life1_ptr=&life1;
    int *life1check_ptr=&life1_check;
    int *life2check_ptr=&life2_check;
    if(count%2==0)
        ques_index=2*ques_num;
    else
        ques_index=2*ques_num+1;//because there are 30 questions including alternates and we only have to display 15 of them
    int iterator=-1;//for checking that whether we are on next question or just continuing the loop;
    int random;// for choosing which option gets displayed besides the correct one in 50=50
    char* current_money;
    current_money = (char *)malloc(15 * sizeof(char));// for how much the question is for
    while (ques_num < 15)
    {
        //argument after life1_check is for life2_check for telling frame that user have that lifeline available or not
        //argument after that is for selected/locked
        //NOTE if selected != 0, correct and wrong must be 0 and if correct or wrong != 0 selected must be 0
        //NOTE correct and wrong must not be same , otherwise nothing will get be printed
        iterator++;
        //so that this only runs once for a loop (not when loop is continued)
        if(iterator==ques_num)
        {
            life1=0;
            do
            {
                srand(time(0));//this make sure that random number is unique based on current time
                random=(rand()%(4))+1;
            }
            while(random==questions[ques_index].answer);//keep changing the random number if its same as the answer
        }
        clear_screen();
        //if both life lines are used together this makes sure that random is not same as the answer
        if(random==questions[ques_index].answer)
        {
            do
            {
                srand(time(0));
                random=(rand()%(4))+1;
            }
            while(random==questions[ques_index].answer);
        }
        //HERE is the main part - frame prints the question and its return value is money user had already won
        char *money=frame(ques_num,questions[ques_index],life1,life1_check,life2_check,0,correct,wrong,random,current_money);
        int locked=0;
        printf("Enter A/a/B/b/C/c/D/d to choose! ");
        if(life1_check)
        {
            printf("Enter [l]/[L] for 50:50 ");
        }
        if(life2_check)
        {
            printf("Enter [f]/[F] for Flip-The-Question");
        }
        printf(CYAN"\nEnter [q]/[Q] to quit\n"COLOR_RESET);
        char ans[1024];
        time_t start, end;
        int seconds;
        if(iterator==ques_num)
        {
            start = time (NULL);//starting counting seconds
        }
        //taking User Input
        fgets(ans, 1024, stdin);
        if(ans[1]!=10)//ensuring that user presses enter just after inputing one character
        {
            printf("Please enter a single character\n");
            delay(1500);
            continue;
        }
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
            lifeline1(life1_ptr,life1check_ptr);
            continue;
        case 70: //f
        case 102: //F
            lifeline2(life2check_ptr,count,ques_index_ptr,ques_num);
            continue;
        case 81: //q
        case 113: //Q
            locked=999;
            msg_output(0,ques_num,0,0,0,1,money,current_money);//money was the return value of frame
            break;
        default:
            printf(RED"INVALID INPUT\n"COLOR_RESET);
            delay(500);
            continue;
        }
        //if life1 is called then making sure that user doesn't select those options which have disappeared
        if(life1 && (locked!=random && locked!=questions[ques_index].answer &&locked!=999))
        {
            printf(RED"Please choose only from displayed options\n"COLOR_RESET);
            delay(1000);
            continue;
        }
        if(locked==999)//for quitting the game , triggered when q/Q is entered
        {
            break;
        }
        /////////////////////////////////////CONFIRMING THE ANSWER////////////////////////////////////////////
        clear_screen();
        frame(ques_num,questions[ques_index],life1,life1_check,life2_check,locked,correct,wrong,random,current_money);
        printf(CYAN"Lock kar diya jaye? Are you sure? enter [Y]/[y] to confirm or any other key to choose again.\n"COLOR_RESET);
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
        //timer for first four questions
        if(ques_num<4)
        {
            if (seconds > 30)
            {
                msg_output(1,ques_num,0,0,0,0,money,current_money);
                break;
            }
        }
        if(locked==0)
        {
            continue;//basically if locked is not changed then continue
        }
        // correct answer
        if (locked == questions[ques_index].answer)
        {
            clear_screen();
            frame(ques_num,questions[ques_index],life1,life1_check,life2_check,0,locked,wrong,random,current_money);
            msg_output(0,ques_num,1,0,0,0,money,current_money);
            delay(1500);
        }
        else //wrong answer and exiting the game logic
        {
            clear_screen();
            frame(ques_num,questions[ques_index],life1,life1_check,life2_check,0,questions[ques_index].answer,locked,random,current_money);
            msg_output(0,ques_num,0,1,0,0,money,current_money);
            break;
        }
        ques_num++;
        iterator=ques_num-1;//so that when loop starts over then iterator becomes equal to ques_num
        if(count%2==0)
            ques_index=2*ques_num;
        else
            ques_index=2*ques_num+1;
        clear_screen();
    }
    free(current_money);
    current_money=NULL;
    //////////////////////////////// PLAY AGAIN OR EXIT GAME LOGIC/////////////////////////////////////////////////////
    //freeing memory
    char again[1024];
    while(1)//asking again and again
    {
        msg_output(0,ques_num,0,0,1,0,"","");
        count=count_gameplay(1,count);
        fgets(again, 1024, stdin);
        if(again[0]==80 || again[0]==112)
        {
            gameloop(count);
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
char* frame(int ques_num, Question questions, int life1,int life1_check, int life2_check, int option_selected, int correct, int wrong, int random, char *money)
{

    char *won_money;//for how much already has been won
    //allocating memory for both
    won_money = (char *)malloc(15 * sizeof(char));
    //displaying all moneyboard and where user is currently, this function changes money and current_money which are passed by reference
    money_board(ques_num, money, won_money);
    //////////////DISPLAYING REMAINING LIFELINES//////////////////////
    printf(GREEN);
    if(life1_check==0||life2_check==0)
    {
        if(life2_check==1)
        {
            printf("\n LIFELINE REMAINING..."YELLOW"  /<--\\ \n");
            printf("                        \\-->/ \n");
        }
        if(life1_check==1)
        {
            printf("\n LIFELINE REMAINING...  "YELLOW"/50\\\n");
            printf("                        \\50/\n");
        }
    }
    else
    {
        printf("\n LIFELINES REMAINING... "YELLOW"/50 \\ /<--\\ \n");
        printf("                        \\ 50/ \\-->/\n");
    }
    printf(COLOR_RESET);
    printf(CYAN"\nThis question is for %s\n"COLOR_RESET, money);
    printf(GREEN"You currently have %s\n"COLOR_RESET, won_money);
    printf(CYAN"If you lose you will get ");
    if(ques_num<3)
        printf("Nothing\n");
    else if(ques_num<8)
        printf("Rs. 20,000\n");
    else if(ques_num<12)
        printf("Rs. 3,20,000\n");
    else
        printf("Rs. 1,00,00,000\n");
    printf(COLOR_RESET);
    if(life1==0)//i.e. 50-50
    {
        random=0;
    }
    display_question(ques_num, questions, option_selected, correct, wrong, random);
    if(ques_num<4&&correct==0)//telling user about the timer
    {
        printf(RED"You have 30s to answer this question!!\n"COLOR_RESET);
    }
    return won_money;
}
//basically fills the array of structure with the values on questions.txt
int read_questions(Question questions[], size_t len, char ques_file[])
{
    //opening file
    FILE *fp = fopen(ques_file, "r");
    //error handling
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
        //field is somewhat similar to buffer
        char field[1024];
        int field_pos = 0;
        int i = 0;
        do
        {
            field[field_pos++] = buf[i];
            if ((buf[i] == ';' || buf[i] == '\n'))//reading the file until ";" or "\n" is encountered
            {
                field[field_pos - 1] = '\0';//making it a string so that strcpy can be used
                field_pos = 0;
                switch (field_cnt)//filling the struct instances
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
                field_cnt++;//for 6 different fields
            }
        }
        while (buf[++i]);
        ques_num++;
    }
    fclose(fp);//closing file
    free(buf);
    fp=NULL;
    buf=NULL;
    return 0;
}
void delay(int trigger)//provide agrument in miliseconds
{
    int msec = 0; /* 10ms */
    clock_t before = clock();//from time.h library
    do
    {
         //Do something to busy the CPU just here while you drink a coffee
         //Be sure this code will not take more than `trigger` ms
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
//for counting the number of times the program has been run, so that we can give different questions everytime
int count_gameplay (int insidegame, int count)
{
    if(insidegame)
    {
        FILE *fp_counter;
        fp_counter = fopen("count.txt","w+");
        fprintf(fp_counter,"%d",++count);
        fclose(fp_counter);
        fp_counter=NULL;
    }
    else
    {
        count=1;
        FILE *fp_count;
        fp_count = fopen("count.txt","w+");
        if(fp_count == NULL)
        {
            fprintf(fp_count,"%d",count);
            fclose(fp_count);
        }
        else
        {
            fscanf(fp_count,"%d",&count);
            fclose(fp_count);
        }
        fp_count=NULL;
        return count;
    }
}
int lifeline1(int *life1, int *life1check)
{
    clear_screen();
    if(*life1check==1)
    {
        *life1=1;//so that frame knows that lifeline has been called
        *life1check=0;//making sure that it doesn't get used again
    }
    else
    {
        printf("You don't have 50-50 lifeline left :/\n");
        delay(500);
    }
}
int lifeline2(int *life2check, int count, int *ques_index, int ques_num)
{
    clear_screen();
    if(*life2check==1)
    {
        if(count%2==0)//flip the the question will be based on count
            *ques_index=2*ques_num+1;
        else
            *ques_index=2*ques_num;
        *life2check=0;//making sure that it doesn't get used again
    }
    else
    {
        printf("You don't have flip the question lifeline left.\n");
        delay(500);
    }
}
//these arguments are kindof like switches
int msg_output(int timer,int ques_num,int correct,int wrong,int exit,int quit,char *money, char *current_money)
{
    if(timer)
    {
        printf ("Sorry, you were too slow.\n");
        if(ques_num+1<=3)
            printf("You won Nothing\n");
        else if(ques_num+1<=8)
            printf("You won Rs. 20,000\n");
    }
    else if(correct)
    {
        printf(GREEN"CORRECT ANSWER!!! You now have %s\n"COLOR_RESET,current_money);
        delay(1500);
    }
    else if(wrong)
    {
        printf(RED"Better luck next time , You won "YELLOW);
        if(ques_num+1<=3)
            printf("Nothing\n");
        else if(ques_num+1<=8)
            printf("Rs. 20,000\n");
        else if(ques_num+1<=12)
            printf("Rs. 3,20,000\n");
        else
            printf("Rs. 1,00,00,000\n");
        printf(COLOR_RESET);
    }
    else if(quit)
    {
        if(ques_num>1)
            printf("Congratulations!! ");
        printf("You Won %s\n",money);
    }
    else if(exit)
    {
        if(ques_num==15)
        {
            printf(GREEN"CONGRATULATIONS YOU WON 7 CRORE !!! use them well ;)\n"COLOR_RESET);
        }
        printf(CYAN"Enter [p]/[P] to play again or [q]/[Q] to quit\n"COLOR_RESET);
    }
}
